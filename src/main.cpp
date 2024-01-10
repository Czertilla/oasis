#include <iostream>         // ввод-вывод
#include "Herbivores.h"     // класс Травоядные, там же классы Хищники и Животные а так же файл со всеми константами
#include <thread>           // потоки для параллельного выполнения симуляции, расчета координат и вывода на экран точек
#include "timer.h"          // модуль для относительного подсчета ускоренного времени в симуляции
#include <bgi/winbgim.h>    // библиотека для реализации визуализации
#include "Randomizer.h"     // рандомайзер для честного рандома, используется при выставлении начальных особей


void sleep(long long ms){
//    упрощение задействования задержки из библиотеки chrono, в аргументт подается длительнсть задержки в мс
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool flagSim = true; // разрешение симулиовать
bool flagVis = true; // разрешить визуализировать


void draw(const std::vector<int> &data){
//    функция отрисовывает массив точек, в аргумент подается вектор координат, где каждая четная коорд это X а след Y
    for (int i=0; i < data.size(); i+=2){
        circle(data[i], data[i+1], DOT_SCREEN_RADIUS);
//      circle(коорд X, коорд Y, радиус) - функиция из библиотеки winbgim, рисует круг
    }
}

char* getText(long long* lastUpdate){
//    функция подготовки текста для предстоящего отображения на экран
//    (lastUpdate - необходимо для посчета fps, обозначает когда был отрисован предыдущий кадр)
    std::string text; // уфер текста
    text += std::to_string(Predators::getCoords()->size()) + ":";
    text += std::to_string(Herbivores::getCoords()->size());
    auto date = (long) timer::get(); // находим внутренее время в симуляции, далее пошагово раскладываем его на
    text+= "    " + std::to_string((int)(timer::get()/HOUR)) + ":"; // часы
    date %= HOUR;
    text+= std::to_string((int)(date/MINUTE)) + ':';// минуты
    date %= MINUTE;                         // и секунды
    text+=std::to_string((date));
    auto now = timer::getTime(); // находим реальное время, чтобы подсчитать fps
    text+= "    " + std::to_string(1000. / (double)(now - *lastUpdate)); // расчет fps
    *lastUpdate = now; // обновляем время последнего кадра
    return const_cast<char*>(text.c_str());
//    возвращает текст в формате "Х:Т Ч:М:С ФПС", где Х - кол-во хищников, Т - травоядных,
//    Ч:М:C - внутреннее время симуляции, ФПС - кадры в секунду
}

bool swap(bool page){
//    данная функция поочередно меняет две страницы, пока кадр отрисовывается  на одной странице, в окне отображается
//    предыдущий кадр на другой странице
    setactivepage(page); // выставляем активную страницу, на ней рисуем новый кадр
    page = !page; // меняем 1 на 0 или 0 на 1 (местами страницы)
    setvisualpage(page); // теперь другую страницу мы отображаем
    cleardevice(); // очищаем первую страницу (которая активная) от старого кадра
    return page; // возвращаем номер отображаемой страницы страницы
}

void calculate(const std::set<Vectors*>* coords, std::vector<int>* res){
//    функция подсчета координат того или иного множества векторных координат, на вход получает множество векторов,
//    и указатель на вектор, куда записать результат расчетов. Переводит вещественные вектора в одномерный вектор
//    целочисленных координат для дальнейшего отображения в кадре
    res->clear(); // очищаем от не актуальных данных
    for(auto pos: *coords){
        res->push_back((int)pos->x + X_BORDER_Screen); // обязательно не забываем прибавить четверть окна, чтобы
        res->push_back((int)pos->y + Y_BORDER_Screen); // нулевы6е координаты в центр окна
    }
}

void visualize(){
// основная функция визуализации, запускается в отдельном потоке
    auto herbivores = Herbivores::getCoords(); // все позиции травоядных
    auto predators = Predators::getCoords();    // хищников
    auto grass = Herbivores::getGrass();        // травы
//    сначала получаем указатели на множества координатных векторов для травоядных, хищников и травы
    std::vector<int> hcords, pcords, gcords; // те же координаты, только уже на экране и  виде линейного массива чисел
    initwindow(X_BORDER_Screen*2, Y_BORDER_Screen * 2 + TEXT_HEIGHT * STRINGS_COUNT, "Oasis");
    // создаем окно, с заданными размерами и заголовком названием проекта
    bool page; // номер страницы либо 0 либо 1, поочердно их будем менять для плавности анимации, пока рисуется одна, \
    // отображается другая
    long long lastUpdate = timer::getTime(), now; // сразу задаем две переменные реального времени в милисекундах, \
    // чтобы подсчитывать кадры в секунду по разнице между двумя соседними кадрами
    while (flagVis){
        std::thread pcalc(calculate, predators, &pcords); // параллельно расчитываем все координаты на экране
        std::thread hcalc(calculate,  herbivores, &hcords);
        std::thread gcalc(calculate, grass, &gcords);
        page = swap(page); // меняем страницы
        setcolor(RED); // выставляем цвет для хищников
        pcalc.join(); // прежде чем рисовать точки, дожидаемся окончания подсчета координа на экране для хищников
        draw(pcords); // теперь рисуем
        setcolor(BLUE);  // аналогично для травоядных
        hcalc.join();
        draw(hcords);
        setcolor(GREEN); // и травы
        gcalc.join();
        draw(gcords);
        outtextxy(0, Y_BORDER_Screen*2, getText(&lastUpdate)); // выводим информацию о популяции времени
        // и кадрах в секунду
    }
}


void updateGrass(){
    // обновление травы, взамен съеденой траве высаживаем новую
    auto grass = Herbivores::getGrass(); // получаем информацию о траве (их координаты)
    auto herbs = Herbivores::getPopulation();// получаем информацию о популяции травоядных
    auto gap = herbs.size() - grass->size(); // вычисляем разницу между размером двх популяций
    if (gap <= 0) return; // если травы столько же или больше чем травоядных, ничего не делаем
    auto count = (int)(gap * GRASS_RECOVERY); // получаем конкретное количемство сколько нужно высадить травы (влияет
    // константа ВОССТАНАВЛИЕМОСТЬ_ТРАВЫ
    for (int i=0; i < count; i++){
        Herbivores::addGrass(); // заданное количество раз высаживаем траву на рандомные координаты с помощью соотв.
        // статического метода класса Травоядные
    }
}

void simulate() {
    // функция симуляции, запускается как отдельный поток
    // симуляция работает до тех пор, пока не вымрут либо Хищники либо Травоядные
    while (not Predators::getPopulation().empty() and not Herbivores::getPopulation().empty() and flagSim){
        auto population = Animals::getPopulation(); // получаем всю популяцию Животных
        // (и хищники и травоядные)
        for (Animals* indiv : population){
            //  поочередно итерируемся по всем сразу вызывая у каждого специальный метод Обновление
            if (indiv->isDead()) continue; // если кто-то уже успел умертвить особь, пропускаем ее
            // далее идет специальное место для остановки, чтобы пока во время дебага программа стоит на паузе
            // специально написанный модуль Таймер остановил время внутри симуляции, т.е выставил множитель скорости = 0
            timer::pause();
            timer::resume();// место остановки для дебага
            indiv->update();
        }
        Herbivores::updateGrass(); // вызываем обновление травы, трава обновляется каждый тик (цикл) в зависимости
        // от того, как много травы съели и какой множитель восстановления травы проставлен в файле с константами
        sleep(1); // в случае когда популяция очень маленькая, не успевает пройти достатончо времени, чтобы
        // зафиксировать изменения состояний особей (они как бы замирают) поэтому нужная минимальная задержка
    }
    timer::setTimelineSpeed(0); // как только симуляция завершена, замораживаем время, чтобы оставшиеся особи замерли
    // в своем последнемм состояниии
    // выводим итоговую информацию в консоль
    std::cout << Predators::getPopulation().size() << " "
    << Herbivores::getPopulation().size() << " " << timer::get() << std::endl;
}


int main() {
//    проставляем флаги, чтобы оставить возможность прервать процессы
    flagSim = true; // симуляции
    flagVis = true; // визуализации
    timer(); // инициализируем таймер, с этого момента в симуляции пошел отсчет времени
    timer::setTimelineSpeed(timeLineSpeed); // ускоряем время внутри симуляции относительно настоящего времени
    // в зависимости от проставленного в фаайле с константами значения
    // расставляем начальных особей по полю в рандомные места
    for (int i=0; i<START_COUNT_Predators; i++){
        new Predators(Vectors(randDouble(-X_BORDER_World, +X_BORDER_World),
                          randDouble(-Y_BORDER_World, +Y_BORDER_World)));
    }
    for (int i=0; i<START_COUNT_Herbivores; i++){
        new Herbivores(Vectors(randDouble(-X_BORDER_World, +X_BORDER_World),
                          randDouble(-Y_BORDER_World, +Y_BORDER_World)));
    }
    for (int i=0; i<START_COUNT_Grass; i++){
        Herbivores::addGrass(new Vectors(randDouble(-X_BORDER_World, +X_BORDER_World),
                          randDouble(-Y_BORDER_World, +Y_BORDER_World)));
    }
    std::thread vis(visualize); // запускаем парарллельный процесс визуализации
    std::thread sim(simulate);  // запускаем параллельный процесс симуляции
    // именно в таком порядке, чтобы ничего не пропустить
    sim.join(); // ждем, когда процесс симуляции заверщиться
    vis.join(); // ждем когда процесс визуализации завершиться (когда пользователь закроет окно с картинкой)
    return 0;
}

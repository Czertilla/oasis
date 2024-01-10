//
// Created by Redmi on 18.12.2023.
//

#include "Vectors.h"
#include <cmath>

Vectors::Vectors() {
    x = 0;
    y = 0;
}

Vectors::Vectors(double x, double y) {
    this->x = x;
    this->y = y;
}

Vectors::Vectors(Vectors const &copied){
    x = copied.x;
    y = copied.y;
}

void Vectors::add(const Vectors& other) {
    if (isnanf(this->x) or isnanf(other.y) or isnanf(this->y) or isnanf(other.x))
        auto aa = 0;
    this->x += other.x;
    this->y += other.y;
}

Vectors Vectors::getAmount(const Vectors& a, const Vectors& b){
    return {Vectors(a.x + b.x, a.y + b.y)};
}

Vectors Vectors::getAmount(const Vectors& other) const{
    return Vectors::getAmount(*this, other);
}

void Vectors::multiply(double multiplier) {
    x *= multiplier;
    y *= multiplier;
}

Vectors Vectors::getMultiplied(const Vectors& vector, double multiplier) {
    auto v = Vectors(vector);
    v.multiply(multiplier);
    return v;
}

Vectors Vectors::getMultiplied(double multiplier) const {
    return Vectors::getMultiplied(*this, multiplier);
}

double Vectors::length() const {
    return pow(pow(x, 2) + pow(y, 2), 0.5);
}

double Vectors::length(const Vectors& vector) {
    return vector.length();
}

double Vectors::getScalarProduct(const Vectors& a, const Vectors& b) {
    return a.x * b.x + a.y * b.y;
}

double Vectors::getScalarProduct(const Vectors& other) const {
    return Vectors::getScalarProduct(*this, other);
}

Vectors Vectors::getDirection() const {
    auto l = length();
    if (l == 0)
        return getMultiplied(1);
    auto len = 1 / l;
    return getMultiplied(len);
}

Vectors Vectors::getDirection(const Vectors &vect) {
    return vect.getDirection();
}


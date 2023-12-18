//
// Created by Redmi on 18.12.2023.
//

#ifndef OASIS_VECTORS_H
#define OASIS_VECTORS_H


class Vectors {
public:
    double x;
    double y;
    Vectors();
    Vectors(double x, double y);
    Vectors(Vectors const& copied);
    static Vectors getAmount(const Vectors& a, const Vectors& b);
    [[nodiscard]] Vectors getAmount(const Vectors& other) const;
    void add(const Vectors& other);
    void multiply(double multiplier);
    static Vectors getMultiplied(const Vectors &vector, double multiplier);
    [[nodiscard]] Vectors getMultiplied(double multiplier) const;
    [[nodiscard]] double length() const;
    static double length(const Vectors& vector);
    static double getScalarProduct(const Vectors& a, const Vectors& b);
    [[nodiscard]] double getScalarProduct(const Vectors& other) const;
};


#endif //OASIS_VECTORS_H

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <SFML/Graphics.hpp>

namespace NGeometry {

const double PI = 3.14159265358979323846;
const double EPSILON = 1e-9;

struct TPoint {
    TPoint(double x, double y): X(x), Y(y) {}
    TPoint(): TPoint(0.0, 0.0) {}

    TPoint operator+(const TPoint& other) const;
    TPoint operator-(const TPoint& other) const;
    TPoint operator+=(const TPoint& other);
    TPoint operator-=(const TPoint& other);

    TPoint operator*(const double& number) const;
    TPoint operator*=(const double& number);

    bool operator==(const TPoint& other) const;
    bool operator!=(const TPoint& other) const;

    double X;
    double Y;
};

struct TFixedVector {
    TFixedVector(TPoint p1, TPoint p2): P1(p1), P2(p2) {}
    TPoint direction() const;
    double length() const;

    TPoint P1;          // Begin
    TPoint P2;          // End
};

class TBaseFigure {
public:
    virtual ~TBaseFigure() = default;
    virtual void draw(sf::RenderWindow& window) const = 0;
    // virtual void move(double alpha, double distance, bool isRadian=true) = 0;
    // virtual void rotate(TPoint rotationPoint, double alpha, bool clockwise=true) = 0;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};


class TTriangle : public TBaseFigure {
public:
    TTriangle(TPoint p1, TPoint p2, TPoint p3);
    TTriangle(TFixedVector v1, TFixedVector v2);

    void draw(sf::RenderWindow& window) const override;
    double area() const override;
    double perimeter() const override;

private:
    TPoint P1;
    TPoint P2;
    TPoint P3;
};

class TParallelogram : public TBaseFigure {
public:
    TParallelogram(TFixedVector v1, TFixedVector v2);
    void draw(sf::RenderWindow& window) const override;
    double area() const override;
    double perimeter() const override;

private:
    TPoint P1;
    TPoint P2;
    TPoint P3;
    TPoint P4;
};

class TRectangle : public TParallelogram {
public:
    using TParallelogram::TParallelogram;
    TRectangle(TFixedVector v1, TFixedVector v2);
};


class TSquare : public TRectangle {
public:
    using TRectangle::TRectangle;
    TSquare(TFixedVector v1, TFixedVector v2);
};


class TCircle : public TBaseFigure {
public:
    TCircle(TPoint center, double radius);
    TCircle(TPoint center, TPoint circlePoint);
    TCircle(TFixedVector radiusVector);

    void draw(sf::RenderWindow& window) const override;
    double area() const override;
    double perimeter() const override;

private:
    TPoint Center;
    double Radius;
};

} // namespace NGeometry

#endif // GEOMETRY_H

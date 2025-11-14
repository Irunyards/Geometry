#include "geometry.h"
#include <cmath>
#include <stdexcept>

namespace NGeometry {

// TPoint
TPoint TPoint::operator+(const TPoint& other) const {
    return TPoint(X + other.X, Y + other.Y);
}

TPoint TPoint::operator-(const TPoint& other) const {
    return TPoint(X - other.X, Y - other.Y);
}

TPoint TPoint::operator+=(const TPoint& other) {
    X += other.X;
    Y += other.Y;
    return *this;
}

TPoint TPoint::operator-=(const TPoint& other) {
    X -= other.X;
    Y -= other.Y;
    return *this;
}

TPoint TPoint::operator*(const double& number) const {
    return TPoint(X * number, Y * number);
}

TPoint TPoint::operator*=(const double& number) {
    X *= number;
    Y *= number;
    return *this;
}

bool TPoint::operator==(const TPoint& other) const {
    return (std::abs(X - other.X) < EPSILON && std::abs(Y - other.Y) < EPSILON);
}

bool TPoint::operator!=(const TPoint& other) const {
    return !(*this == other);
}


// TFixedVector
TPoint TFixedVector::direction() const {
    return TPoint(P2.X - P1.X, P2.Y - P1.Y);
}

double TFixedVector::length() const {
    TPoint dir = direction();
    return std::sqrt(dir.X * dir.X + dir.Y * dir.Y);
}


// TTriangle
TTriangle::TTriangle(TPoint p1, TPoint p2, TPoint p3) : P1(p1), P2(p2), P3(p3) {}

TTriangle::TTriangle(TFixedVector v1, TFixedVector v2) : P1(v1.P1), P2(v1.P2), P3(v2.P2) {
    if (v1.P1 != v2.P1) {
        throw std::invalid_argument("TTriangle constructor. Fixed vectors have no common points.");
    }
}

void TTriangle::draw(sf::RenderWindow& window) const {
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(static_cast<float>(P1.X), static_cast<float>(P1.Y)));
    triangle.setPoint(1, sf::Vector2f(static_cast<float>(P2.X), static_cast<float>(P2.Y)));
    triangle.setPoint(2, sf::Vector2f(static_cast<float>(P3.X), static_cast<float>(P3.Y)));
    triangle.setFillColor(sf::Color::Yellow);
    triangle.setOutlineColor(sf::Color::White);
    triangle.setOutlineThickness(1);
    window.draw(triangle);
}

double TTriangle::area() const {
    return 0.5 * std::abs(P1.X * (P2.Y - P3.Y) + P2.X * (P3.Y - P1.Y) + P3.X * (P1.Y - P2.Y));
}

double TTriangle::perimeter() const {
    TFixedVector v1(P1, P2);
    TFixedVector v2(P2, P3);
    TFixedVector v3(P3, P1);
    return v1.length() + v2.length() + v3.length();
}


// TParallelogram
TParallelogram::TParallelogram(TFixedVector v1, TFixedVector v2)
    : P1(v1.P1), P2(v1.P2), P4(v2.P2), P3(v1.P2 + v2.direction()) {
    if (v1.P1 != v2.P1) {
        throw std::invalid_argument("Fixed vectors do not share a common starting point.");
    }
}

void TParallelogram::draw(sf::RenderWindow& window) const {
    sf::ConvexShape parallelogram;
    parallelogram.setPointCount(4);
    parallelogram.setPoint(0, sf::Vector2f(static_cast<float>(P1.X), static_cast<float>(P1.Y)));
    parallelogram.setPoint(1, sf::Vector2f(static_cast<float>(P2.X), static_cast<float>(P2.Y)));
    parallelogram.setPoint(2, sf::Vector2f(static_cast<float>(P3.X), static_cast<float>(P3.Y)));
    parallelogram.setPoint(3, sf::Vector2f(static_cast<float>(P4.X), static_cast<float>(P4.Y)));
    parallelogram.setFillColor(sf::Color::Black);
    parallelogram.setOutlineColor(sf::Color::White);
    parallelogram.setOutlineThickness(1);
    window.draw(parallelogram);
}

double TParallelogram::area() const {
    TFixedVector v1(P1, P2);
    TFixedVector v2(P1, P4);
    return std::abs(v1.direction().X * v2.direction().Y - v1.direction().Y * v2.direction().X);
}

double TParallelogram::perimeter() const {
    TFixedVector v1(P1, P2);
    TFixedVector v2(P1, P4);
    return 2 * (v1.length() + v2.length());
}


// TRectangle
TRectangle::TRectangle(TFixedVector v1, TFixedVector v2) : TParallelogram(v1, v2) {
    auto d1 = v1.direction();
    auto d2 = v2.direction();
    if (std::abs(d1.X * d2.X + d1.Y * d2.Y) > EPSILON) {
        throw std::invalid_argument("Fixed vectors are not perpendicular.");
    }
}


// TSquare
TSquare::TSquare(TFixedVector v1, TFixedVector v2) : TRectangle(v1, v2) {
    if (std::abs(v1.length() - v2.length()) > EPSILON) {
        throw std::invalid_argument("Fixed vectors have different lengths.");
    }
}


// TCircle
TCircle::TCircle(TPoint center, double radius) : Center(center), Radius(radius) {}

TCircle::TCircle(TPoint center, TPoint circlePoint) : TCircle(TFixedVector(center, circlePoint)) {}

TCircle::TCircle(TFixedVector radiusVector) : Center(radiusVector.P1), Radius(radiusVector.length()) {}

void TCircle::draw(sf::RenderWindow& window) const {
    sf::CircleShape circle(static_cast<float>(Radius));
    circle.setOrigin(static_cast<float>(Radius), static_cast<float>(Radius));
    circle.setPosition(static_cast<float>(Center.X), static_cast<float>(Center.Y));
    circle.setFillColor(sf::Color::Red);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1);
    window.draw(circle);
}

double TCircle::area() const {
    return PI * Radius * Radius;
}

double TCircle::perimeter() const {
    return 2 * PI * Radius;
}

} // namespace NGeometry

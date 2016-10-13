#include "core/maths/Vector.hpp"
#include <cmath>

using namespace Core::Maths;

Vector::Vector(float x, float y) : x(x), y(y)
{

}

Vector Vector::operator+(const Vector &other) const
{
    float x = this->x + other.x;
    float y = this->y + other.y;
    return Vector(x, y);
}

Vector Vector::operator-(const Vector &other) const
{
    float x = this->x - other.x;
    float y = this->y - other.y;
    return Vector(x, y);
}

Vector Vector::operator*(const Vector &other) const
{
    float x = this->x * other.x;
    float y = this->y * other.y;
    return Vector(x, y);
}

Vector Vector::operator/(const Vector &other) const
{
    float x = this->x / other.x;
    float y = this->y / other.y;
    return Vector(x, y);
}
Vector Vector::operator+(const float other) const
{
    float x = this->x + other;
    float y = this->y + other;
    return Vector(x, y);
}

Vector Vector::operator-(const float other) const
{
    float x = this->x - other;
    float y = this->y - other;
    return Vector(x, y);

}

Vector Vector::operator*(const float other) const
{
    float x = this->x * other;
    float y = this->y * other;
    return Vector(x, y);

}

Vector Vector::operator/(const float other) const
{
    float x = this->x / other;
    float y = this->y / other;
    return Vector(x, y);

}

void Vector::operator+=(const Vector &other)
{
    this->x += other.x;
    this->y += other.y;
}

void Vector::operator-=(const Vector &other)
{
    this->x -= other.x;
    this->y -= other.y;
}

void Vector::operator*=(const Vector &other)
{
    this->x *= other.x;
    this->y *= other.y;
}

void Vector::operator/=(const Vector &other)
{
    this->x /= other.x;
    this->y /= other.y;
}

void Vector::operator+=(const float other)
{
    this->x += other;
    this->y += other;
}

void Vector::operator-=(const float other)
{
    this->x -= other;
    this->y -= other;
}

void Vector::operator*=(const float other)
{
    this->x *= other;
    this->y *= other;
}

void Vector::operator/=(const float other)
{
    this->x /= other;
    this->y /= other;
}

Vector Vector::normalise()
{
    return *this / magnitude();
}

float Vector::magnitude()
{
    return sqrtf(x*x + y*y);
}

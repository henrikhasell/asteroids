#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>

namespace Core
{
    namespace Maths
    {
        struct Vector
        {
            Vector(float x, float y);
            // Data access operator:
            float &operator[](std::size_t index);
            // Arithmetic operators with vectors:
            Vector operator+(const Vector &other) const;
            Vector operator-(const Vector &other) const;
            Vector operator*(const Vector &other) const;
            Vector operator/(const Vector &other) const;
            // Assignment operators with scalars:
            Vector operator+(const float other) const;
            Vector operator-(const float other) const;
            Vector operator*(const float other) const;
            Vector operator/(const float other) const;
            // Arithmetic operators with vectos:
            void operator+=(const Vector &other);
            void operator-=(const Vector &other);
            void operator*=(const Vector &other);
            void operator/=(const Vector &other);
            // Arithmetic operators with scalars:
            void operator+=(const float other);
            void operator-=(const float other);
            void operator*=(const float other);
            void operator/=(const float other);
            // Mathematical operations for vectors:
            Vector normalise();
            float magnitude();
            // Variables:
            float x;
            float y;
        };
    }
}

#endif /* VECTOR_HPP */

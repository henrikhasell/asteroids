#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>

namespace Core
{
    namespace Maths
    {
        class Vector
        {
        public:
            Vector(float x, float y);
            Vector(const Vector &other);
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
            Vector &operator+=(const float other);
            Vector &operator-=(const float other);
            Vector &operator*=(const float other);
            Vector &operator/=(const float other);
            // Mathematical operations for vectors:
            float magnitude();
            float normalise();
        private:
            float data[2];
        };
    }
}

#endif /* VECTOR_HPP */

#include "precision.h"

namespace litex
{
    class Vector3
    {
    public:
        real x;
        real y;
        real z;

    private:
        real pad;

    public:
        Vector3() : x{0}, y{0}, z{0} {}
        Vector3(const real _x, const real _y, const real _z) : x{_x}, y{_y}, z{_z} {}

        Vector3 operator*(const real value) const
        {
            return Vector3(x * value, y * value, z * value);
        }

        Vector3 operator+(const Vector3 &v)
        {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        Vector3 operator-(const Vector3 &v)
        {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }

        void invert()
        {
            x = -x;
            y = -y;
            z = -z;
        }

        real magnitude() const
        {
            return real_sqrt(squareMagnitude());
        }

        real squareMagnitude() const
        {
            return x * x + y * y + z * z;
        }

        void normalize()
        {
            real l = magnitude();
            if (l > 0)
            {
                (*this) = (*this) * (((real)1) / l);
            }
        }

        bool equals(const Vector3 &otherVec)
        {
            return (x == otherVec.x) && (y == otherVec.y) && (z == otherVec.z);
        }
    };
}
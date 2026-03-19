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
        real pad; // this is for padding correctly the object

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

        /** Multiplies this vector by the given value. */
        void operator*=(const real value)
        {
            x *= value;
            y *= value;
            z *= value;
        }

        /** Subtracts the given vector from this. */
        void operator-=(const Vector3 &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        /** Invert the coordinates of this vector. v -> -v */
        void invert()
        {
            x = -x;
            y = -y;
            z = -z;
        }

        /** Gets the magnitude of this vector. */
        real magnitude() const
        {
            return real_sqrt(squareMagnitude());
        }

        /** Gets the squared magnitude of this vector. */
        real squareMagnitude() const
        {
            return x * x + y * y + z * z;
        }

        /** Turns a non-zero vector into a vector of unit length. */
        void normalize()
        {
            real l = magnitude();
            if (l > 0)
            {
                (*this) = (*this) * (((real)1) / l); // -> (this vector3) / (your magnitude)
            }
        }

        bool equals(const Vector3 &otherVec)
        {
            return (x == otherVec.x) && (y == otherVec.y) && (z == otherVec.z);
        }

        /** Verify if the vector is Zero and correct eventually error accumulation */
        bool equalsZero()
        {
            if (x < __DBL_EPSILON__ && y < __DBL_EPSILON__ && z < __DBL_EPSILON__)
            {
                x = 0;
                y = 0;
                z = 0;
                return true;
            }
            return false;
        }
    };
}
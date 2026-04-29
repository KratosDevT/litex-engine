#pragma once

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
		Vector3(const real _x, const real _y, const real _z)
		    : x{_x}, y{_y}, z{_z}
		{
		}

		Vector3 operator*(const real value) const
		{
			return Vector3(x * value, y * value, z * value);
		}

		Vector3 operator+(const Vector3& v) const
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		Vector3 operator-(const Vector3& v) const
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
		void operator-=(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		/** Adds the given vector to this. */
		void operator+=(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		/**
		 * Updates this vector to be the vector product of its current
		 * value and the given vector.
		 */
		void operator%=(const Vector3& vector) { *this = cross(vector); }

		/** Adds to this the vector scaled by the given value. */
		void addScaledVector(const Vector3& vector, real scale)
		{
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}

		/**
		 * Performs a component-wise product with the given vector and
		 * sets this vector to its result.
		 */
		void componentProductUpdate(const Vector3& vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}

		/** Invert the coordinates of this vector. v -> -v */
		void invert()
		{
			x = -x;
			y = -y;
			z = -z;
		}

		/** Gets the magnitude of this vector. */
		real magnitude() const { return real_sqrt(squareMagnitude()); }

		/** Gets the squared magnitude of this vector. */
		real squareMagnitude() const { return x * x + y * y + z * z; }

		/** Turns a non-zero vector into a vector of unit length. */
		void normalize()
		{
			real l = magnitude();
			if (l > 0)
			{
				(*this) = (*this) * (static_cast<real>(1) /
				                     l); // -> (this vector3) / (your magnitude)
			}
		}

		/** Reset this vector into a zero vector. */
		void resetToZero()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		bool checkRealNearEpsilon(real r) const
		{
			return std::abs(r) < REAL_EPSILON;
		}

		bool equals(const Vector3& otherVec) const
		{
			real xDiff = x - otherVec.x;
			real yDiff = y - otherVec.y;
			real zDiff = z - otherVec.z;
			return checkRealNearEpsilon(xDiff) && checkRealNearEpsilon(yDiff) &&
			       checkRealNearEpsilon(zDiff);
		}

		/** Verify if the vector is near Zero, check with REAL_EPSILON */
		bool equalsZero() const
		{
			if (checkRealNearEpsilon(x) && checkRealNearEpsilon(y) &&
			    checkRealNearEpsilon(z))
			{
				return true;
			}
			return false;
		}

		/**
		 * Calculates and returns the dot product of this vector
		 * with the given vector. this * vector
		 */
		real dot(const Vector3& vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z;
		}

		/**
		 * Calculates and returns the cross product of this vector
		 * with the given vector. this x vector
		 */
		Vector3 cross(const Vector3& vector) const
		{
			return Vector3(y * vector.z - z * vector.y,
			               z * vector.x - x * vector.z,
			               x * vector.y - y * vector.x);
		}
	};
} // namespace litex
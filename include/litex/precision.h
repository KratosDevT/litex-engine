#pragma once

#include "math.h"

namespace litex
{

/** Defines the precision of the square root operator. */
#define real_sqrt sqrtf

/** Defines the precision of the power operator. */
#define real_pow powf

    /**
     * Defines a real number precision. litex can be compiled in
     * single or double precision versions. By default single precision
     * is provided.
     */
    typedef float real;

    static constexpr real REAL_EPSILON = static_cast<real>(1e-5);
}
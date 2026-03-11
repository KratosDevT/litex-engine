#include "math.h"

namespace litex
{

/** Defines the precision of the square root operator. */
#define real_sqrt sqrtf

    /**
     * Defines a real number precision. litex can be compiled in
     * single or double precision versions. By default single precision
     * is provided.
     */
    typedef float real;

}
#include <iostream>
#include "litex/core.h"

int main()
{
    litex::Vector3 v = litex::Vector3(1, 2, 3);
    v.normalize();
    std::cout << v.magnitude() << std::endl;
}
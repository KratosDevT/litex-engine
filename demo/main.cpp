#include "sdl/engine.h"
#include <iostream>

int main()
{
    auto result = litex::Engine::create("Litex Engine", 800, 600);
    if (!result)
    {
        std::cerr << "Engine error: " << result.error() << "\n";
        return 1;
    }

    litex::Engine engine = std::move(*result);
    engine.run();

    return 0;
}

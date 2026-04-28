#include "renderer/renderer.h"
#include <iostream>

litex::Renderer::Renderer(const std::string &title, int width, int height, SDL_WindowFlags windowFlag)
    : w(width), h(height)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
        return;
    }

    if (!TTF_Init())
    {
        std::cout << "TTF_Init error: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow(title.c_str(), width, height, windowFlag);
    if (!window)
    {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        return;
    }

    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    if (!font)
    {
        std::cout << "Font error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_StartTextInput(window);
    SDL_SetRenderVSync(renderer, 1);
}

litex::Renderer::~Renderer()
{
    cleanup();
}

void litex::Renderer::cleanup() noexcept
{
    if (window)
    {
        SDL_StopTextInput(window);
    }

    if (font)
    {
        TTF_CloseFont(font);
        TTF_Quit();
    }

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

void litex::Renderer::beginFrame(litex::Color bg)
{
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(renderer);
}

void litex::Renderer::endFrame()
{
    SDL_RenderPresent(renderer);
}

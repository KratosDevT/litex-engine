#pragma once

#include "litex/precision.h"
#include "sdl/renderer.h"
#include <expected>
#include <functional>
#include <string>
#include <SDL3/SDL.h>

namespace litex
{
    class Engine
    {
    public:
        static std::expected<Engine, std::string> create(const std::string &title, int width, int height, SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE);

        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;

        Engine(Engine &&) = default;
        Engine &operator=(Engine &&) = default;

        void run();

        void setOnUpdate(std::function<void(real)> fn)             { onUpdate = std::move(fn); }
        void setOnRender(std::function<void(Renderer &)> fn)       { onRender = std::move(fn); }
        void setOnEvent(std::function<void(const SDL_Event &)> fn) { onEvent  = std::move(fn); }

        Renderer &renderer() { return renderer_; }

    private:
        explicit Engine(Renderer &&r);

        Renderer renderer_;
        bool running_ = false;

        std::function<void(real)>              onUpdate;
        std::function<void(Renderer &)>        onRender;
        std::function<void(const SDL_Event &)> onEvent;
    };
}

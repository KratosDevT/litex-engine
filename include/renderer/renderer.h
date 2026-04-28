#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace litex
{
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        static constexpr Color white() { return {255, 255, 255, 255}; }
        static constexpr Color black() { return {0, 0, 0, 255}; }
        static constexpr Color red() { return {220, 50, 50, 255}; }
        static constexpr Color green() { return {50, 200, 50, 255}; }
        static constexpr Color blue() { return {50, 120, 220, 255}; }
        static constexpr Color yellow() { return {240, 200, 40, 255}; }
    };

    // Gestisce finestra SDL3
    class Renderer
    {
    public:
        Renderer(const std::string &title, int width, int height, SDL_WindowFlags windowFlag);
        ~Renderer();

        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;

        void beginFrame(Color background = Color::black());
        void endFrame();

        int width() const { return w; }
        int height() const { return h; }

    private:
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        TTF_Font *font = nullptr;
        int w, h;

        void cleanup() noexcept;
    };
}
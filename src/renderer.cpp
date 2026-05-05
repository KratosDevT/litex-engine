#include "sdl/renderer.h"
#include <cmath>

namespace litex
{

	std::expected<Renderer, std::string>
	Renderer::create(const std::string& title, int width, int height,
	                 SDL_WindowFlags windowFlag)
	{
		Renderer r;
		r.w = width;
		r.h = height;

		if (!SDL_Init(SDL_INIT_VIDEO))
			return std::unexpected(std::string("SDL_Init error: ") +
			                       SDL_GetError());

		if (!TTF_Init())
			return std::unexpected(std::string("TTF_Init error: ") +
			                       SDL_GetError());

		r.window = SDL_CreateWindow(title.c_str(), width, height, windowFlag);
		if (!r.window)
			return std::unexpected(std::string("SDL_CreateWindow error: ") +
			                       SDL_GetError());

		r.renderer = SDL_CreateRenderer(r.window, nullptr);
		if (!r.renderer)
			return std::unexpected(std::string("SDL_CreateRenderer error: ") +
			                       SDL_GetError());

		std::string fontPath =
		    std::string(SDL_GetBasePath()) + "assets/fonts/DejaVuSans.ttf";
		r.font = TTF_OpenFont(fontPath.c_str(), 24);
		if (!r.font)
			return std::unexpected(std::string("Font error: ") +
			                       SDL_GetError());

		SDL_StartTextInput(r.window);
		SDL_SetRenderVSync(r.renderer, 1);

		return r;
	}

	Renderer::Renderer(Renderer&& other) noexcept
	    : window(other.window), renderer(other.renderer), font(other.font),
	      w(other.w), h(other.h)
	{
		other.window = nullptr;
		other.renderer = nullptr;
		other.font = nullptr;
	}

	Renderer& Renderer::operator=(Renderer&& other) noexcept
	{
		if (this != &other)
		{
			cleanup();
			window = other.window;
			renderer = other.renderer;
			font = other.font;
			w = other.w;
			h = other.h;
			other.window = nullptr;
			other.renderer = nullptr;
			other.font = nullptr;
		}
		return *this;
	}

	Renderer::~Renderer() { cleanup(); }

	void Renderer::cleanup() noexcept
	{
		if (!window && !renderer && !font)
			return;

		if (window)
			SDL_StopTextInput(window);

		if (font)
		{
			TTF_CloseFont(font);
			font = nullptr;
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

	void Renderer::drawFilledCircle(int cx, int cy, int radius, Color color)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		for (int dy = -radius; dy <= radius; dy++)
		{
			int dx = static_cast<int>(std::sqrt(radius * radius - dy * dy));
			SDL_FRect row = { static_cast<float>(cx - dx), static_cast<float>(cy + dy),
			                  static_cast<float>(2 * dx), 1.0f };
			SDL_RenderFillRect(renderer, &row);
		}
	}

	void Renderer::beginFrame(Color bg)
	{
		SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
		SDL_RenderClear(renderer);
	}

	void Renderer::endFrame() { SDL_RenderPresent(renderer); }

} // namespace litex

#include "sdl/engine.h"

namespace litex
{

	Engine::Engine(Renderer&& r) : renderer_(std::move(r)) {}

	std::expected<Engine, std::string> Engine::create(const std::string& title,
	                                                  int width, int height,
	                                                  SDL_WindowFlags flags)
	{
		auto result = Renderer::create(title, width, height, flags);
		if (!result)
			return std::unexpected(result.error());
		return Engine(std::move(*result));
	}

	void Engine::run()
	{
		running_ = true;
		Uint64 last = SDL_GetTicks();

		while (running_)
		{
			Uint64 now = SDL_GetTicks();
			real dt = static_cast<real>(now - last) / 1000.0f;
			last = now;

			if (dt > 0.05f)
				dt = 0.05f;

			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_EVENT_QUIT)
					running_ = false;
				if (onEvent)
					onEvent(event);
			}

			if (onUpdate)
				onUpdate(dt);

			renderer_.beginFrame(Color::darkgray());
			if (onRender)
				onRender(renderer_);
			renderer_.endFrame();
		}
	}

} // namespace litex

#include "litex/particle.h"
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

	const int radius = 12;

	litex::Particle particle;
	particle.position = litex::Vector3(400.0f, 300.0f, 0.0f);
	particle.velocity = litex::Vector3(0.0f, 0.0f, 0.0f);
	particle.acceleration = litex::Vector3(0.0f, 500.0f, 0.0f);
	particle.damping = 1.0f;
	particle.inverseMass = 1.0f;

	engine.setOnUpdate(
	    [&](litex::real dt)
	    {
		    particle.integrate(dt);

		    float bottom =
		        static_cast<float>(engine.renderer().height() - radius);
		    if (particle.position.y >= bottom)
		    {
			    particle.position.y = bottom;
			    particle.velocity.y = -particle.velocity.y;
		    }
	    });

	engine.setOnRender(
	    [&](litex::Renderer& r)
	    {
		    r.drawFilledCircle(static_cast<int>(particle.position.x),
		                       static_cast<int>(particle.position.y), radius,
		                       litex::Color::white());
	    });

	engine.run();
	return 0;
}

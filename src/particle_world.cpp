#include "litex/particle_world.h"

namespace litex
{

void ParticleWorld::add(Particle* p)
{
    particles_.push_back(p);
}

void ParticleWorld::runPhysics(real duration)
{
    for (Particle* p : particles_)
    {
        p->integrate(duration);
    }
}

const ParticleWorld::Particles& ParticleWorld::particles() const
{
    return particles_;
}

} // namespace litex

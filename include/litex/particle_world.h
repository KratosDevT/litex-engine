#pragma once

#include "particle.h"
#include <vector>

namespace litex
{

class ParticleWorld
{
public:
    using Particles = std::vector<Particle*>;

    void add(Particle* p);
    void runPhysics(real duration);

    const Particles& particles() const;

private:
    Particles particles_;
};

} // namespace litex

#ifndef __PARTICLES_PARTICLE_H__
#define __PARTICLES_PARTICLE_H__

#include "config.h"

typedef struct Particle {
    SDL_FRect rect;
    SDL_Color color;
    SDL_Color outline_color;
    float speed_x, speed_y;
} Particle;

Particle *init_particle(Config *config);

void destroy_particle(Particle *particle);

void set_particle_values(Particle *particle, Config *config);

#endif // __PARTICLES_PARTICLE_H__
#include "particle.h"

Particle *init_particle(Config *config)
{
    Particle *part = malloc(sizeof(struct Particle));
    if (!part) return NULL;

    set_particle_values(part, config);
    return part;
}

void destroy_particle(Particle *particle)
{
    if (particle) {
        free(particle);
        particle = NULL;
    }
}

void set_particle_values(Particle *particle, Config *config)
{
    particle->rect.x = get_random_float(config->spawn_x_min, config->spawn_x_max);
    particle->rect.y = get_random_float(config->spawn_y_min, config->spawn_y_max);
    particle->rect.w = particle->rect.h = 10.0;

    particle->color.a = 255;
    particle->color.r = particle->color.g = particle->color.b = 100;

    particle->outline_color.a = 255;
    particle->outline_color.r = particle->outline_color.g = particle->outline_color.b = 175;

    particle->speed_x = get_random_float(config->speed_x_min, config->speed_x_max);
}
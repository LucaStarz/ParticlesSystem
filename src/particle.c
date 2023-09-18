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
    particle->rect.w = get_random_float(config->width_min, config->width_max);
    particle->rect.h = get_random_float(config->height_min, config->height_max);

    particle->speed_x = get_random_float(config->speed_x_min, config->speed_x_max);
    particle->speed_y = get_random_float(config->speed_y_min, config->speed_y_max);

    particle->color.r = get_random_int(config->min_color_r, config->max_color_r);
    particle->color.g = get_random_int(config->min_color_g, config->max_color_g);
    particle->color.b = get_random_int(config->min_color_b, config->max_color_b);
    particle->color.a = get_random_int(config->min_color_a, config->max_color_a);

    particle->outline_color.r = get_random_int(config->min_outline_color_r, config->max_outline_color_r);
    particle->outline_color.g = get_random_int(config->min_outline_color_g, config->max_outline_color_g);
    particle->outline_color.b = get_random_int(config->min_outline_color_b, config->max_outline_color_b);
    particle->outline_color.a = get_random_int(config->min_outline_color_a, config->max_outline_color_a);
}
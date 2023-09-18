#ifndef __PARTICLES_SYSTEM_H__
#define __PARTICLES_SYSTEM_H__

#include "list.h"

typedef struct System {
    ParticleList *list;
    Config *config;
    SDL_Window *window;
    SDL_Renderer *renderer;
    float to_create;
} System;

System *init_system(const char *path);

void destroy_system(System *system);

void update_system(System *system);

#endif // __PARTICLES_SYSTEM_H__
#include "system.h"

System *init_system(const char *path)
{
    System *sys = malloc(sizeof(struct System));
    if (!sys) return NULL;

    sys->config = init_config(path);
    if (!sys->config) {
        free(sys);
        return NULL;
    }

    sys->list = init_list(sys->config);
    if (!sys->list) {
        destroy_config(sys->config);
        free(sys);
        return NULL;
    }

    sys->window = SDL_CreateWindow("particles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sys->config->window_width, sys->config->window_height, SDL_WINDOW_VULKAN);
    if (!sys->window) {
        destroy_system(sys);
        return NULL;
    }

    sys->renderer = SDL_CreateRenderer(sys->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sys->renderer) {
        destroy_system(sys);
        return NULL;
    }

    sys->to_create = 0.f;
    return sys;
}

void destroy_system(System *system)
{
    if (system) {
        if (system->renderer)
            SDL_DestroyRenderer(system->renderer);
        if (system->window)
            SDL_DestroyWindow(system->window);

        destroy_config(system->config);
        destroy_list(system->list);
        free(system);
        system = NULL;
    }
}

void update_system(System *system)
{
    SDL_RenderClear(system->renderer);
    system->to_create += system->config->spawn_rate;
    for (; system->to_create>1; system->to_create--)
        reactive_node(system->list, system->config);

    NodeList *node = system->list->begin;
    size_t pos = 0;
    while (node != NULL) {
        NodeList *next = node->next;
        if (pos >= system->list->last_inactive) {
            node->part->rect.x += node->part->speed_x;
            node->part->rect.y += node->part->speed_y;

            SDL_SetRenderDrawColor(system->renderer, node->part->color.r, node->part->color.g, node->part->color.b, node->part->color.a);
            SDL_RenderFillRectF(system->renderer, &node->part->rect);
            SDL_SetRenderDrawColor(system->renderer, node->part->outline_color.r, node->part->outline_color.g, node->part->outline_color.b, node->part->outline_color.a);
            SDL_RenderDrawRectF(system->renderer, &node->part->rect);

            if (node->part->rect.x > system->config->delete_x_max || node->part->rect.x < system->config->delete_x_min - node->part->rect.w ||
                node->part->rect.y > system->config->delete_y_max || node->part->rect.y < system->config->delete_y_min - node->part->rect.h)
                desactive_node(system->list, node);
        }

        node = next;
        pos += 1;
    }

    SDL_RenderPresent(system->renderer);
    SDL_SetRenderDrawColor(system->renderer, 0, 0, 0, 255);
}
#ifndef __PARTICLES_LIST_H__
#define __PARTICLES_LIST_H__

#include "particle.h"

typedef struct NodeList {
    Particle *part;
    struct NodeList *next, *before;
} NodeList;

NodeList *init_node_list(Config *config);

void destroy_node_list(NodeList *node);

typedef struct ParticleList {
    NodeList *begin, *end;
    size_t last_inactive;
} ParticleList;

ParticleList *init_list(Config *config);

void destroy_list(ParticleList *list);

void add_node_to_list(ParticleList *list, Config *config);

void desactive_node(ParticleList *list, NodeList *node);

void reactive_node(ParticleList *list, Config *config);

inline void show_list(ParticleList *list) {
    NodeList *node = list->begin;
    while (node != NULL) {
        printf("[%p]  ", node);
        node = node->next;
    }

    printf("\n");
}

#endif // __PARTICLES_LIST_H__
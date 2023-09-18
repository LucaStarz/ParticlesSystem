#ifndef __PARTICLES_LIST_H__
#define __PARTICLES_LIST_H__

#include "particle.h"

typedef struct NodeList {
    Particle *part;
    signed char active;
    struct NodeList *next, *before;
} NodeList;

NodeList *init_node_list(Config *config);

void destroy_node_list(NodeList *node);

void reactive_node_list(NodeList *node, Config *config);

typedef struct ParticleList {
    NodeList *begin, *end;
    size_t size, last_inactive;
} ParticleList;

ParticleList *init_list(Config *config);

void destroy_list(ParticleList *list);

void add_node_to_list(ParticleList *list, Config *config);

void desactive_node(ParticleList *list, NodeList *node);

void reactive_node(ParticleList *list, Config *config);

#endif // __PARTICLES_LIST_H__
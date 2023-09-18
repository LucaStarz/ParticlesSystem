#include "list.h"

NodeList *init_node_list(Config *config)
{
    NodeList *node = malloc(sizeof(struct NodeList));
    if (!node) return NULL;

    node->part = init_particle(config);
    if (!node->part) {
        free(node);
        return NULL;
    }

    node->next = node->before = NULL;
    return node;
}

void destroy_node_list(NodeList *node)
{
    if (node) {
        destroy_particle(node->part);
        free(node);
        node = NULL;
    }
}

ParticleList *init_list(Config *config)
{
    ParticleList *list = malloc(sizeof(struct ParticleList));
    if (!list) return NULL;

    list->begin = list->end = NULL;
    list->last_inactive = 0;
    for (uint64_t i=0; i<config->begin_spawn; i++)
        add_node_to_list(list, config);

    return list;
}

void destroy_list(ParticleList *list)
{
    if (list) {
        NodeList *node = list->begin;
        while (node != NULL) {
            NodeList *next = node->next;
            destroy_node_list(node);
            node = next;
        }

        free(list);
        list = NULL;
    }
}

void add_node_to_list(ParticleList *list, Config *config)
{
    if (list->begin == NULL) {
        list->begin = init_node_list(config);
        list->end = list->begin;
        if (!list->begin) return;
    } else {
        NodeList *new_node = init_node_list(config);
        if (!new_node) return;

        list->end->next = new_node;
        new_node->before = list->end;
        list->end = new_node;
    }
}

void desactive_node(ParticleList *list, NodeList *node)
{
    if (list->begin == node) {
        list->last_inactive += 1;
        return;
    }
    else if (list->end == node) {
        list->end = node->before;
        list->end->next = NULL;
        node->before = NULL;
        node->next = list->begin;
        list->begin->before = node;
        list->begin = node;
    } else {
        node->before->next = node->next;
        node->next->before = node->before;
        node->before = NULL;
        node->next = list->begin;
        list->begin->before = node;
        list->begin = node;
    }

    list->last_inactive += 1;
}

void reactive_node(ParticleList *list, Config *config)
{
    if (list->last_inactive > 0) {
        set_particle_values(list->begin->part, config);
        if (list->begin != list->end) {
            NodeList *old = list->begin;
            old->before = list->end;
            list->begin = old->next;
            old->next->before = NULL;
            old->next = NULL;
            list->end->next = old;
            list->end = old;
        }
        
        list->last_inactive -= 1;
    } else add_node_to_list(list, config);
}
#ifndef __PARTICLES_CONFIG_H__
#define __PARTICLES_CONFIG_H__

#include "base.h"

typedef struct Config {
// Read part
    char word1[256], word2[256];
    char current_character;

// Particle configuration
    float spawn_x_min, spawn_x_max;
    float spawn_y_min, spawn_y_max;
    float speed_x_min, speed_x_max;
    float speed_y_min, speed_y_max;
    float width_min, width_max;
    float height_min, height_max;

    uint8_t min_color_r, min_color_g, min_color_b, min_color_a;
    uint8_t max_color_r, max_color_g, max_color_b, max_color_a;
    uint8_t min_outline_color_r, min_outline_color_g, min_outline_color_b, min_outline_color_a;
    uint8_t max_outline_color_r, max_outline_color_g, max_outline_color_b, max_outline_color_a;

// Window configuration
    int window_width, window_height;

// Generation configuration
    uint64_t begin_spawn;
    float spawn_rate;
    double FPS;

// Deletion configuration
    float delete_x_min, delete_x_max;
    float delete_y_min, delete_y_max;
} Config;

Config *init_config(const char *path);

void destroy_config(Config *config);

void load_default_config(Config *config);

void load_extern_config(Config *config, const char *path);

void try_skip_spaces(Config *config, FILE *f);

int read_int(Config *config, FILE *f);
int64_t read_long(Config *config, FILE *f);
float read_float(Config *config, FILE *f);
double read_double(Config *config, FILE *f);

#endif // __PARTICLES_CONFIG_H__
#include "config.h"

Config *init_config(const char *path)
{
    Config *conf = malloc(sizeof(Config));
    if (!conf) return NULL;

    if (path[0] == '+' && path[1] == '\0')
        load_default_config(conf);
    else
        load_extern_config(conf, path);
    return conf;
}

void destroy_config(Config *config)
{
    if (config) {
        free(config);
        config = NULL;
    }
}

void load_default_config(Config *config)
{
    printf("Loading default configuration\n");
    config->delete_x_max = config->spawn_x_max = config->window_width = 1280;
    config->delete_y_max = config->spawn_y_max = config->window_height = 720;
    config->spawn_x_min = config->spawn_y_min = 0.0f;
    config->speed_x_max = config->speed_y_max = 3.0f;
    config->speed_x_min = config->speed_y_min = -3.0f;
    config->delete_x_min = config->delete_y_min = 0.0f;

    config->width_min = config->height_min = 10.0f;
    config->width_max = config->height_max = 10.0f;

    config->min_color_r = config->min_color_g = config->min_color_b = config->min_color_a = 0;
    config->max_color_r = config->max_color_g = config->max_color_b = config->max_color_a = 255;
    config->min_outline_color_r = config->min_outline_color_g = config->min_outline_color_b = config->min_outline_color_a = 0;
    config->max_outline_color_r = config->max_outline_color_g = config->max_outline_color_b = config->max_outline_color_a = 255;

    config->begin_spawn = 50;
    config->spawn_rate = 0.2f;
    config->FPS = 1000 / 60.0;
}

void load_extern_config(Config *config, const char *path)
{
    load_default_config(config);
    printf("Try loading configuration at path '%s'\n", path);

    size_t path_size = strlen(path);
    if (path_size < 7) {
        printf("File '%s' is not a correct '.pconf' file\n", path);
        return;
    }

    if (path[path_size-1] != 'f' || path[path_size-2] != 'n' || path[path_size-3] != 'o' || path[path_size-4] != 'c' ||
        path[path_size-5] != 'p' || path[path_size-6] != '.') {
            printf("Could not open file that is not a '.pconf'\n");
            return;
    }

    FILE *config_file = fopen(path, "rb");
    if (!config_file) {
        printf("Failed to open file '%s'\n", path);
        return;
    }

    config->current_character = 0;
    unsigned char size1;
    while (config->current_character != -1) {
        size1 = 0;
        try_skip_spaces(config, config_file);
        while (config->current_character != ':' && config->current_character != -1) {
            config->word1[size1++] = config->current_character;
            config->current_character = fgetc(config_file);
        }

        fgetc(config_file);
        try_skip_spaces(config, config_file);
        config->word1[size1] = '\0';
        if (string_equals(config->word1, "window_size")) {
            config->window_width = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->window_height = read_int(config, config_file);
        } else if (string_equals(config->word1, "spawn_x")) {
            config->spawn_x_min = read_float(config, config_file);
            try_skip_spaces(config, config_file);
            config->spawn_x_max = read_float(config, config_file);
        } else if (string_equals(config->word1, "spawn_y")) {
            config->spawn_y_min = read_float(config, config_file);
            try_skip_spaces(config, config_file);
            config->spawn_y_max = read_float(config, config_file);
        } else if (string_equals(config->word1, "begin_spawn")) {
            config->begin_spawn = read_long(config, config_file);
        } else if (string_equals(config->word1, "spawn_rate")) {
            config->spawn_rate = read_float(config, config_file);
        } else if (string_equals(config->word1, "fps")) {
            config->FPS = 1000.0 / read_double(config, config_file);
        } else if (string_equals(config->word1, "min_random_color")) {
            config->min_color_r = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->min_color_g = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->min_color_b = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->min_color_a = read_int(config, config_file);
        } else if (string_equals(config->word1, "max_random_color")) {
            config->max_color_r = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->max_color_g = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->max_color_b = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->max_color_a = read_int(config, config_file);
        } else if (string_equals(config->word1, "min_random_outline_color")) {
            config->min_outline_color_r = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->min_outline_color_g = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->min_outline_color_b = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->min_outline_color_a = read_int(config, config_file);
        } else if (string_equals(config->word1, "max_random_outline_color")) {
            config->max_outline_color_r = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->max_outline_color_g = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->max_outline_color_b = read_int(config, config_file);
            try_skip_spaces(config, config_file);
            config->max_outline_color_a = read_int(config, config_file);
        } else if (string_equals(config->word1, "speed_x")) {
            config->speed_x_min = read_float(config, config_file);
            try_skip_spaces(config, config_file);
            config->speed_x_max = read_float(config, config_file);
        } else if (string_equals(config->word1, "speed_y")) {
            config->speed_y_min = read_float(config, config_file);
            try_skip_spaces(config, config_file);
            config->speed_y_max = read_float(config, config_file);
        } else if (string_equals(config->word1, "part_width")) {
            config->width_min = read_float(config, config_file);
            try_skip_spaces(config, config_file);
            config->width_max = read_float(config, config_file);
        } else if (string_equals(config->word1, "part_height")) {
            config->height_min = read_float(config, config_file);
            try_skip_spaces(config, config_file);
            config->height_max = read_float(config, config_file);
        } else if (string_equals(config->word1, "delete_x")) {
            config->delete_x_min = read_float(config, config_file);
            try_skip_spaces(config, config_file);
            config->delete_x_max = read_float(config, config_file);   
        } else if (string_equals(config->word1, "delete_y")) {
            config->delete_y_min = read_float(config, config_file);
            try_skip_spaces(config, config_file);
            config->delete_y_max = read_float(config, config_file);   
        } else if (config->word1[0] != '\0') {
            printf("Unknown pconf command '%s'\n", config->word1);
            while (config->current_character != '\n' && config->current_character != -1)
                config->current_character = fgetc(config_file);
        }
    }

    fclose(config_file);
    printf("Successfully read extern configuration\n");
}

void try_skip_spaces(Config *config, FILE *f)
{
    config->current_character = fgetc(f);
    while ((config->current_character >= '\t' && config->current_character <= '\r') || config->current_character == ' ')
        config->current_character = fgetc(f);
}

int read_int(Config *config, FILE *f)
{
    unsigned char size = 0;
    while (!(config->current_character >= '\t' && config->current_character <= '\r') && config->current_character != ' '  && config->current_character != -1) {
        config->word2[size++] = config->current_character;
        config->current_character = fgetc(f);
    }
    config->word2[size] = '\0';

    return strtol(config->word2, NULL, 10);
}

int64_t read_long(Config *config, FILE *f)
{
    unsigned char size = 0;
    while (!(config->current_character >= '\t' && config->current_character <= '\r') && config->current_character != ' '  && config->current_character != -1) {
        config->word2[size++] = config->current_character;
        config->current_character = fgetc(f);
    }
    config->word2[size] = '\0';

    return strtoll(config->word2, NULL, 10); 
}

float read_float(Config *config, FILE *f)
{
    unsigned char size = 0;
    while (!(config->current_character >= '\t' && config->current_character <= '\r') && config->current_character != ' '  && config->current_character != -1) {
        config->word2[size++] = config->current_character;
        config->current_character = fgetc(f);
    }
    config->word2[size] = '\0';

    return strtof(config->word2, NULL); 
}

double read_double(Config *config, FILE *f)
{
    unsigned char size = 0;
    while (!(config->current_character >= '\t' && config->current_character <= '\r') && config->current_character != ' ' && config->current_character != -1) {
        config->word2[size++] = config->current_character;
        config->current_character = fgetc(f);
    }
    config->word2[size] = '\0';

    return strtod(config->word2, NULL);
}
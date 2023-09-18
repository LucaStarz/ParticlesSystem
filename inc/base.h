#ifndef __PARTICLES_BASE_H__
#define __PARTICLES_BASE_H__

#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>

#define COLOR_ERROR     "\033[31m"
#define COLOR_SUCCESS   "\033[32m"
#define COLOR_NONE      "\033[0m"

inline signed char string_equals(const char *str1, const char *str2) {
    signed char equals = 0;
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        equals += (str1[i] - str2[i]);
        i += 1;
    }

    return !equals;
}

inline const float get_random_float(const float min, const float max) {
    return min + ((float)rand()) / ((float)RAND_MAX / (max - min));
}

inline const int get_random_int(const int min, const int max) {
    return min + rand() % (max - min + 1);
}

#endif // __PARTICLES_BASE_H__
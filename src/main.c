#include "system.h"

int main(int argc, char **argv)
{
    srand((unsigned)time(NULL));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
    System *sys = init_system(argc > 1 ? argv[1] : "+");

    SDL_Event event;
    double delta = 0.;
    uint64_t a, b;
    a = b = SDL_GetTicks64();

    if (sys) {
        signed char running = 1;
        while (running) {
            a = SDL_GetTicks64();
            delta = a - b;

            if (delta > sys->config->FPS) {
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_QUIT: running = 0; break;
                        default: break;
                    }
                }

                update_system(sys);
                b = a;
            }
        }
    }

    destroy_system(sys);
    SDL_Quit();
    return 0;
}
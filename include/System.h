#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


class System {
    public:
        System();
        ~System();

        SDL_Window* window;
        SDL_Renderer* renderer;
        Mix_Chunk* ljud;

};

extern System sys;

#endif 
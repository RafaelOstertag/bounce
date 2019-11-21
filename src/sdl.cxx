#include "sdl.hh"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

bool init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Cannot initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() == -1) {
        std::cerr << "Cannot initialize SDL TTF: " << TTF_GetError()
                  << std::endl;
        return false;
    }

    return true;
}

void quit_sdl() {
    TTF_Quit();
    SDL_Quit();
}

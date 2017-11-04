#ifndef DELETERS
#define DELETERS

#include "SDL.h"
#include <iostream>

struct SDLDeleters
{
    void operator() (SDL_Window* window);

    void operator() (SDL_Renderer* screen_renderer);

    void operator() (SDL_Texture* texture);
};

#endif //DELETERS

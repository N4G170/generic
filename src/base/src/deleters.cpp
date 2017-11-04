#include "deleters.hpp"
#include <iostream>

void SDLDeleters::operator() (SDL_Window* window)
{
    std::cout << "Calling destroy for SDL_window object pointer... \n";
    SDL_DestroyWindow(window);
}

void SDLDeleters::operator() (SDL_Renderer* screen_renderer)
{
    std::cout << "Calling destroy for SDL_Renderer object pointer... \n";
    SDL_DestroyRenderer(screen_renderer);
}

void SDLDeleters::operator() (SDL_Texture* texture)
{
    std::cout << "Calling destroy for SDL_DestroyTexture object pointer... \n";
    SDL_DestroyTexture( texture );
}

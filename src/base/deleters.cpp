#include "deleters.hpp"
#include <iostream>

void DeleteSDLTexture(SDL_Texture* texture)
{
    std::cout << "Calling destroy for SDL_DestroyTexture object pointer... \n";
    SDL_DestroyTexture( texture );
}

#include <string>
#include <SDL2/SDL.h>

namespace sdl_gui
{

#ifndef SDL_GUI_CONSTANTS_HPP
#define SDL_GUI_CONSTANTS_HPP

//<f> Default File Paths

const std::string c_img_white_dot{"data/img/white_dot.png"};
const std::string c_button_base{"data/img/button_base.png"};

const std::string c_default_font{"data/font/DejaVuSansMono.ttf"};

//</f>

//<f> Colours
namespace Colour
{
    const SDL_Colour Black {0,0,0,255};
    const SDL_Colour White {255,255,255,255};
    const SDL_Colour Red {255,0,0,255};
    const SDL_Colour Green {0,255,0,255};
    const SDL_Colour Blue {0,0,255,255};
    const SDL_Colour Light_Blue {173,216,230,255};
    const SDL_Colour Cyan {0,255,255,255};
    const SDL_Colour Yellow {255,255,0,255};
    const SDL_Colour Magenta {255,0,255,255};
    const SDL_Colour Grey {190,190,190,255};

    const SDL_Colour Rain_Drop_Blue {3,74,236,255};
    const SDL_Colour Storm_Petrel {0,24,72,255};

    const SDL_Colour Venus_Yellow {255, 230, 181, 255};//pale yellowish
}
//</f>

#endif //SDL_GUI_CONSTANTS_HPP

}//namespace

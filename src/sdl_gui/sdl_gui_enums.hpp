namespace sdl_gui
{
#ifndef SDL_GUI_ENUMS
#define SDL_GUI_ENUMS

//<f> GuiElements
enum class AnchorType
{
    TOP_LEFT,
    TOP_CENTRE,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_CENTRE,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTRE,
    BOTTOM_RIGHT
};
// </f>

//<f> Button

enum class ButtonState
{
    INACTIVE,
    ACTIVE,
    HOVER,
    DOWN
};

enum class ButtonTransitionType
{
    COLOUR,
    TEXTURE
};

enum MouseFlags
{
    NONE = 0,
    MOUSE_ENTER = 1,
    MOUSE_EXIT = 2,
    MOUSE_HOVER = 4,
    MOUSE_UP = 8,
    MOUSE_DOWN = 16,
    MOUSE_HOLD_DOWN = 32
};

// </f>

//<f> ContainerBox
enum class ContainerWrapMode
{
    NONE,
    CROP,
    WRAP_HEIGHT,
    WRAP_WIDTH
};
//</f>
#endif// SDL_GUI_ENUMS
}//namespace
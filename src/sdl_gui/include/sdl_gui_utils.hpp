#include <type_traits>
#include "SDL.h"
#include "sdl_gui_structs.hpp"
#include <string>

namespace sdl_gui
{

#ifndef SDL_GUI_UTILS
#define SDL_GUI_UTILS

//<f> Enum Casts
/**
 * Cast a enum entry to its inner type (default int)
 */
template<typename T>
// constexpr auto ToInnerType(T enum_entry) noexcept // needs c++14
constexpr typename std::underlying_type<T>::type ToInnerType(T enum_entry) noexcept
{
    return static_cast<typename std::underlying_type<T>::type>(enum_entry);
}

template<typename T>
constexpr bool IsFlagActive(int flag, T enum_entry) noexcept
{
    return flag & ToInnerType(enum_entry);
}
//</f>

//<f> Rect Intersections
//intersect
bool PointInsideRect(const SDL_Rect& rect_1, int x, int y);
bool RectIntersect(const SDL_Rect& rect_1, const SDL_Rect& rect_2);
//</f>

//<f> Simple casts
//rect casts
SDL_Rect RectFromFloats(float x, float y, float w, float h);
SDL_Rect RectFromStructs(Position position, Dimensions size);

//position cast
Position PositionFromInts(int x, int y);
//size cast
Dimensions SizeFromInts(int w, int h);
//</f>

//<f> ToString()
std::string ToString(const SDL_Rect& rect);
std::string ToString(const Position& position);
std::string ToString(const Dimensions& size);
std::string ToString(const Position& position, const Dimensions& size);
//</f>

#endif//SDL_GUI_UTILS

}

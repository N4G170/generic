#include "gui_transform.hpp"
#include <utility>

namespace sdl_gui
{

GuiTransform::GuiTransform()
{

}

GuiTransform::~GuiTransform() noexcept
{

}

GuiTransform::GuiTransform(const GuiTransform& other)
{

}

GuiTransform::GuiTransform(GuiTransform&& other) noexcept
{

}

GuiTransform& GuiTransform::operator=(const GuiTransform& other)
{
    if(this != &other)//not same ref
    {
        GuiTransform tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

GuiTransform& GuiTransform::operator=(GuiTransform&& other) noexcept
{
    return *this;
}

}//namespace

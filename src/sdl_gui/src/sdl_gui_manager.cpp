#include "sdl_gui_manager.hpp"
#include <utility>

GuiManager::GuiManager()
{

}

GuiManager::~GuiManager() noexcept
{

}

GuiManager::GuiManager(const GuiManager& other)
{

}

GuiManager::GuiManager(GuiManager&& other) noexcept
{

}

GuiManager& GuiManager::operator=(const GuiManager& other)
{
    if(this != &other)//not same ref
    {
        GuiManager tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

GuiManager& GuiManager::operator=(GuiManager&& other) noexcept
{
    return *this;
}

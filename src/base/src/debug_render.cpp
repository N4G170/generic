#include "debug_render.hpp"
#include <utility>
#include <iostream>

// void DebugRenderExitError()

//<f> Instance
DebugRender* DebugRender::s_instance{nullptr};

DebugRender* DebugRender::Instance()
{
    if(s_instance == nullptr)
    {
        const int registration_result{ std::atexit( [](){ std::cout<<"DebugRender NEEDS to be initialized before calling its instance."<<std::endl; } )};
        if(registration_result != 0)//failed to register
            exit(EXIT_FAILURE);
        exit(EXIT_FAILURE);
    }
    if(s_instance->m_renderer == nullptr)
    {
        const int registration_result{ std::atexit( [](){ std::cout<<"DebugRender NEEDS a valid SDL_Renderer pointer."<<std::endl; } )};
        if(registration_result != 0)//failed to register
            exit(EXIT_FAILURE);
        exit(EXIT_FAILURE);
    }

    return s_instance;
}

void DebugRender::Init(SDL_Renderer* renderer)
{
    if(s_instance == nullptr)
        s_instance = new DebugRender{renderer};
}
//</f> /Instance

//<f> Constructors & operator=
DebugRender::DebugRender(SDL_Renderer* renderer) : m_renderer{renderer} {}

DebugRender::~DebugRender() noexcept
{
    //de do not own the renderer pointer so we do not destroy it
}
//</f> /Constructors & operator=

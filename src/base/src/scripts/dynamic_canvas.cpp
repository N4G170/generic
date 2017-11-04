#include "dynamic_canvas.hpp"
#include <utility>

//<f> Constructors & operator=
DynamicCanvas::DynamicCanvas(SystemManager* system_manager): RenderScript{}, m_system_manager{system_manager}, m_texture{system_manager->Renderer(), 1, 1}
{

}

DynamicCanvas::~DynamicCanvas() noexcept
{

}

DynamicCanvas::DynamicCanvas(const DynamicCanvas& other)
{

}

DynamicCanvas::DynamicCanvas(DynamicCanvas&& other) noexcept
{

}

DynamicCanvas& DynamicCanvas::operator=(const DynamicCanvas& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

DynamicCanvas& DynamicCanvas::operator=(DynamicCanvas&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* DynamicCanvas::Clone() { return new DynamicCanvas{*this}; }
void DynamicCanvas::Render(float delta_time)
{
    //cler texture
    // m_bg_texture.Clear(m_clear_colour);
    //
    // auto camera{m_system_manager->MainCamera()};
    //
    // if(m_mask_image != nullptr)
    // {
    //     SDL_SetTextureBlendMode(m_bg_texture.TexturePtr(), SDL_BlendMode::SDL_BLENDMODE_ADD);
    //     m_mask_image->GetTexture()->BlendMode(SDL_BlendMode::SDL_BLENDMODE_ADD);
    //     SDL_SetRenderTarget(m_system_manager->Renderer(), m_bg_texture.TexturePtr());
    //     m_mask_image->RenderToMask(delta_time);
    //     SDL_SetRenderTarget(m_system_manager->Renderer(), nullptr);
    //     m_mask_image->GetTexture()->BlendMode(SDL_BlendMode::SDL_BLENDMODE_BLEND);
    // }
    //
    // SDL_SetTextureBlendMode(m_bg_texture.TexturePtr(), SDL_BlendMode::SDL_BLENDMODE_MOD);
    //
    // camera->SetAsTarget();
    // camera->StartRenderMask();
    //
    // auto camera_bounds{camera->CameraBounds()};
    // SDL_Rect dst{BoundsToSDLRect(camera_bounds)};
    // m_bg_texture.Render(nullptr, &dst);
    //
    // camera->StopRenderMask();
    // camera->RemoveAsTarget();
    //
    //
    // SDL_SetTextureBlendMode(m_bg_texture.TexturePtr(), SDL_BlendMode::SDL_BLENDMODE_BLEND);
}
//</f> /Virtual Methods

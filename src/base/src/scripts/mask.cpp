#include "mask.hpp"
#include <utility>
#include "utils.hpp"
#include "constants.hpp"

//<f> Constructors & operator=
Mask::Mask(SystemManager* system_manager): m_system_manager{system_manager},
    m_bg_texture{system_manager->Renderer(), system_manager->MainCamera()->Size()}, m_mask_image{nullptr}, m_clear_colour{Colour::Black}
{
    m_bg_texture.Clear(m_clear_colour);
}

Mask::~Mask() noexcept
{

}

Mask::Mask(const Mask& other): m_system_manager{other.m_system_manager}, m_bg_texture{other.m_bg_texture}, m_mask_image{other.m_mask_image},
    m_clear_colour{other.m_clear_colour}
{

}

Mask::Mask(Mask&& other) noexcept: m_system_manager{std::move(other.m_system_manager)}, m_bg_texture{std::move(other.m_bg_texture)},
    m_mask_image{std::move(other.m_mask_image)}, m_clear_colour{std::move(other.m_clear_colour)}
{

}

Mask& Mask::operator=(const Mask& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Mask& Mask::operator=(Mask&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
        m_system_manager = std::move(other.m_system_manager);
        m_bg_texture = std::move(other.m_bg_texture);
        m_mask_image = std::move(other.m_mask_image);
        m_clear_colour = std::move(other.m_clear_colour);
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* Mask::Clone() { return new Mask{*this}; }

void Mask::Render(float delta_time)
{
    //cler texture
    m_bg_texture.Clear(m_clear_colour);

    auto camera{m_system_manager->MainCamera()};

    if(m_mask_image != nullptr)
    {
        SDL_SetTextureBlendMode(m_bg_texture.TexturePtr(), SDL_BlendMode::SDL_BLENDMODE_ADD);
        m_mask_image->GetTexture()->BlendMode(SDL_BlendMode::SDL_BLENDMODE_ADD);
        SDL_SetRenderTarget(m_system_manager->Renderer(), m_bg_texture.TexturePtr());
        m_mask_image->RenderToMask(delta_time);
        SDL_SetRenderTarget(m_system_manager->Renderer(), nullptr);
        m_mask_image->GetTexture()->BlendMode(SDL_BlendMode::SDL_BLENDMODE_BLEND);
    }

    SDL_SetTextureBlendMode(m_bg_texture.TexturePtr(), SDL_BlendMode::SDL_BLENDMODE_MOD);

    camera->SetAsTarget();
    camera->StartRenderMask();

    auto camera_bounds{camera->CameraBounds()};
    SDL_Rect dst{BoundsToSDLRect(camera_bounds)};
    m_bg_texture.Render(nullptr, &dst);

    camera->StopRenderMask();
    camera->RemoveAsTarget();


    SDL_SetTextureBlendMode(m_bg_texture.TexturePtr(), SDL_BlendMode::SDL_BLENDMODE_BLEND);
}
//</f> /Virtual Methods

//<f> Getters/Setters
void Mask::SetImage(Image* image) { m_mask_image = image; }
Image* Mask::GetImage() const { return m_mask_image; }

SDL_Colour Mask::ClearColour() const { return m_clear_colour; }
void Mask::ClearColour(const SDL_Colour& colour) { m_clear_colour = colour; }
//</f> /Getters/Setters

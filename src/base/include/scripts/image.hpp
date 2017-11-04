#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "render_script.hpp"
#include "texture.hpp"
#include "resource_manager.hpp"
#include "camera.hpp"
#include "system_manager.hpp"

class Image : public RenderScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit Image(SystemManager* system_manager);
        /** brief Default destructor */
        virtual ~Image() noexcept;

        /** brief Copy constructor */
        Image(const Image& other);
        /** brief Move constructor */
        Image(Image&& other) noexcept;

        /** brief Copy operator */
        Image& operator= (const Image& other);
        /** brief Move operator */
        Image& operator= (Image&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;

        void Render(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Methods
        void RenderToMask(float delta_time);
        //</f> /Methods

        //<f> Getters/Setters
        /**
         * \brief Sets the new image to be rendered, also sets m_has_src_rect to false
         */
        void SetImage(const std::string& path);
        Texture* GetTexture();

        void ColourModulation(const SDL_Colour& colour);
        SDL_Colour ColourModulation() const;

        bool HasSrcRect() const;
        void HasSrcRect(bool has_src_rect);

        SDL_Rect SrcRect() const;
        void SrcRect(const SDL_Rect& src_rect);
        //</f> /Getters/Setters

    protected:
        // vars and stuff
        ResourceManager* m_resource_manager;
        Camera* m_camera;
        Texture m_texture;

        bool m_has_src_rect;
        SDL_Rect m_src_rect;

};

#endif //IMAGE_HPP

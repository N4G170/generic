#ifndef STATIC_CANVAS_HPP
#define STATIC_CANVAS_HPP

#include "render_script.hpp"
#include "custom_texture.hpp"
#include "system_manager.hpp"
#include "image.hpp"

class StaticCanvas : public RenderScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit StaticCanvas(SystemManager* system_manager);
        /** brief Default destructor */
        virtual ~StaticCanvas() noexcept;

        /** brief Copy constructor */
        StaticCanvas(const StaticCanvas& other);
        /** brief Move constructor */
        StaticCanvas(StaticCanvas&& other) noexcept;

        /** brief Copy operator */
        StaticCanvas& operator= (const StaticCanvas& other);
        /** brief Move operator */
        StaticCanvas& operator= (StaticCanvas&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;
        void Render(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Content Mangement
        void AddImage(const std::string& path, SDL_Rect* src, SDL_Rect* dst, SDL_Colour colour = {255,255,255,255}, double angle = 0, SDL_Point *rotation_pivot = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void AddImage(Image* source_image);

        void SetAsTarget();
        void RemoveAsTarget();
        //</f> /Content Mangement

        //<f> Getters/Setters
        Vector3<float> CanvasSize() const;
        /**
         * \brief Set the size for the canvas, NOT THE RENDERING SIZE, think of it as size of an image
         * @param size [description]
         */
        void CanvasSize(const Vector3<float>& size);
        //</f> /Getters/Setters

    protected:
        // vars and stuff
        SystemManager* m_system_manager;
        CustomTexture m_texture;

        Vector3<float> m_canvas_size;
    private:
};

#endif //STATIC_CANVAS_HPP

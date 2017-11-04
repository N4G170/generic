#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "script.hpp"
#include "vector3.hpp"
#include "custom_texture.hpp"
#include "SDL.h"
#include "structs.hpp"

class Camera : public Script
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit Camera(SDL_Renderer* renderer);
        /** brief Default destructor */
        virtual ~Camera() noexcept;

        /** brief Copy constructor */
        Camera(const Camera& other);
        /** brief Move constructor */
        Camera(Camera&& other) noexcept;

        /** brief Copy operator */
        Camera& operator= (const Camera& other);
        /** brief Move operator */
        Camera& operator= (Camera&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;
        //</f> /Virtual Methods

        //<f> Getters/Setters
        Vector3<float> Size() const;
        void Size(const Vector3<float>& size);

        float CameraWidth() const;
        void CameraWidth(float width);

        float CameraHeight() const;
        void CameraHeight(float height);

        float CameraDepth() const;
        void CameraDepth(float depth);
        //</f> /Getters/Setters

        //<f> Render Control
        void Render(float delta_time);
        /**
         * \brief Clears the content from the internal texture
         */
        void ClearCamera();
        /**
         * \brief Set the internal camera texture as render target
         */
        void SetAsTarget();
        /**
         * \brief Remove the internal camera texture as render target
         */
        void RemoveAsTarget();

        void StartRenderMask();
        void StopRenderMask();

        Bounds<float> CameraBounds() const;
        bool InsideCamera(Bounds<float> element_bounds);
        //</f> /Render Control

        //<f> Position Control
        Vector3<float> ToWorldSpace(const Vector3<float>& position);
        Vector3<float> ToScreenSpace(const Vector3<float>& position);
        //</f> /Position Control

    private:
        Vector3<float> m_position;
        SDL_Renderer* m_renderer;
        Vector3<float> m_size;
        CustomTexture m_texture;
        SDL_Colour m_clear_colour;

        //<f> Private Methods
        void ResizeTexture();
        //</f> /Private Methods
};

#endif //CAMERA_HPP

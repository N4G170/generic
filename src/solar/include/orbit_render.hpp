#ifndef ORBIT_RENDER_HPP
#define ORBIT_RENDER_HPP

#include "render_script.hpp"
#include "custom_texture.hpp"
#include "system_manager.hpp"

class OrbitRender : public RenderScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit OrbitRender(SystemManager* system_manager);
        /** brief Default destructor */
        virtual ~OrbitRender() noexcept;

        /** brief Copy constructor */
        OrbitRender(const OrbitRender& other);
        /** brief Move constructor */
        OrbitRender(OrbitRender&& other) noexcept;

        /** brief Copy operator */
        OrbitRender& operator= (const OrbitRender& other);
        /** brief Move operator */
        OrbitRender& operator= (OrbitRender&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;
        void Render(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Getters/Setters
        void OrbitColour(const SDL_Colour& orbit_colour);
        SDL_Colour OrbitColour() const;

        void RotationAngle(float angle);
        void PositionOffset(const Vector3<float>& position_offset);
        //</f> /Getters/Setters

        //<f> Methods
        void RebuildOrbit(float perihelion, float aphelion, const std::vector<Vector3<float>>& points);
        //</f> /Methods

    protected:
        // vars and stuff
        SystemManager* m_system_manager;
        CustomTexture m_texture;
        SDL_Colour m_orbit_colour;
        Vector3<float> m_position_offset;
    private:
};

#endif //ORBIT_RENDER_HPP

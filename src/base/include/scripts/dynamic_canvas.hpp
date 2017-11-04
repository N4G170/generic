#ifndef DYNAMIC_CANVAS_HPP
#define DYNAMIC_CANVAS_HPP

#include "render_script.hpp"
#include "custom_texture.hpp"
#include "system_manager.hpp"

class DynamicCanvas : RenderScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit DynamicCanvas(SystemManager* system_manager);
        /** brief Default destructor */
        virtual ~DynamicCanvas() noexcept;

        /** brief Copy constructor */
        DynamicCanvas(const DynamicCanvas& other);
        /** brief Move constructor */
        DynamicCanvas(DynamicCanvas&& other) noexcept;

        /** brief Copy operator */
        DynamicCanvas& operator= (const DynamicCanvas& other);
        /** brief Move operator */
        DynamicCanvas& operator= (DynamicCanvas&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;
        void Render(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Getters/Setters

        //</f> /Getters/Setters

    protected:
        // vars and stuff
        SystemManager* m_system_manager;
        CustomTexture m_texture;
    private:
};

#endif //DYNAMIC_CANVAS_HPP

#ifndef RENDER_SCRIPT_HPP
#define RENDER_SCRIPT_HPP

#include "script.hpp"

class RenderScript : public Script
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        RenderScript():Script{} {}
        /** brief Default destructor */
        virtual ~RenderScript() noexcept {}

        /** brief Copy constructor */
        RenderScript(const RenderScript& other): Script{other} {}
        /** brief Move constructor */
        RenderScript(RenderScript&& other) noexcept: Script{std::move(other)} {}

        /** brief Copy operator */
        RenderScript& operator= (const RenderScript& other)
        {
            if(this != &other)
            {
                Script::operator=(other);
            }
            return *this;
        }
        /** brief Move operator */
        RenderScript& operator= (RenderScript&& other) noexcept
        {
            if(this != &other)
            {
                Script::operator=(std::move(other));
            }
            return *this;
        }
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        virtual Script* Clone() = 0;
        virtual void Render(float delta_time) {}
        //</f> /Virtual Methods

        //<f> Getters/Setters

        //</f> /Getters/Setters

    protected:
        // vars and stuff

    private:
};

#endif //RENDER_SCRIPT_HPP

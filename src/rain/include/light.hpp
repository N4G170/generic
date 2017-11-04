#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "behaviour_script.hpp"

class Light: public BehaviourScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        Light();
        /** brief Default destructor */
        virtual ~Light() noexcept;

        /** brief Copy constructor */
        Light(const Light& other);
        /** brief Move constructor */
        Light(Light&& other) noexcept;

        /** brief Copy operator */
        Light& operator= (const Light& other);
        /** brief Move operator */
        Light& operator= (Light&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;

        void Update(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Getters/Setters

        //</f> /Getters/Setters

    protected:
        // vars and stuff

    private:
};

#endif //LIGHT_HPP

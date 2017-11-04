#ifndef BEHAVIOUR_SCRIPT_HPP
#define BEHAVIOUR_SCRIPT_HPP

#include "script.hpp"

class BehaviourScript : public Script
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        BehaviourScript() : Script{}, m_input_event{} {}
        /** brief Default destructor */
        virtual ~BehaviourScript() noexcept {}

        /** brief Copy constructor */
        BehaviourScript(const BehaviourScript& other): Script{other}, m_input_event{other.m_input_event} {}
        /** brief Move constructor */
        BehaviourScript(BehaviourScript&& other) noexcept : Script{std::move(other)}, m_input_event{std::move(other.m_input_event)} {}

        /** brief Copy operator */
        BehaviourScript& operator= (const BehaviourScript& other)
        {
            if(this != &other)
            {
                Script::operator=(other);
                m_input_event = other.m_input_event;
            }
            return *this;
        }
        /** brief Move operator */
        BehaviourScript& operator= (BehaviourScript&& other) noexcept
        {
            if(this != &other)
            {
                Script::operator=(std::move(other));
                m_input_event = std::move(other.m_input_event);
            }
            return *this;
        }
        //</f> /Constructors & operator=

        //<f> Methods
        void Input(const SDL_Event& event) { m_input_event = event; }
        //</f> /Methods

        //<f> Virtual Methods
        virtual Script* Clone() = 0;
        virtual void FixedUpdate(float fixed_delta_time){};
        virtual void Update(float delta_time){};
        //</f> /Virtual Methods

        //<f> Getters/Setters

        //</f> /Getters/Setters

    protected:
        // vars and stuff
        SDL_Event m_input_event;
    private:
};

#endif //BEHAVIOUR_SCRIPT_HPP

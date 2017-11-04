#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include "SDL.h"
#include "uid.hpp"

class Object;

class Script
{
    public:
        //<f> Constructors & operator=
        Script(): m_instance_id{GenerateUID()}, m_owner{nullptr}, m_enabled{true} {}
        ~Script() noexcept{};

        Script(const Script& other): m_instance_id{GenerateUID()}, m_owner{other.m_owner}, m_enabled{other.m_enabled} {}
        Script(Script&& other) noexcept: m_instance_id{std::move(other.m_instance_id)}, m_owner{std::move(other.m_owner)}, m_enabled{std::move(other.m_enabled)} {}

        Script& operator=(const Script& other)
        {
            if(this != &other)
            {
                m_instance_id = GenerateUID();
                m_owner = other.m_owner;
                m_enabled = other.m_enabled;
            }
            return *this;
        }
        Script& operator=(Script&& other) noexcept
        {
            if(this != &other)
            {
                m_instance_id = std::move(other.m_instance_id);
                m_owner = std::move(other.m_owner);
                m_enabled = std::move(other.m_enabled);
            }
            return *this;
        }
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        virtual Script* Clone() = 0;
        //</f> /Virtual Methods

        //<f> Ownership & UID
        UID InstanceID() const { return m_instance_id; }

        Object* Owner() const { return m_owner; }
        void Owner(Object* owner) { m_owner = owner; }
        //</f> /Ownership

        //<f> Enable
        bool Enabled() const { return m_enabled; }
        void Enabled(bool enabled) { m_enabled = enabled; }
        void Enable() { m_enabled = true; }
        void Disable() { m_enabled = false; }
        //</f> /Enable

    protected:
        UID m_instance_id;
        Object* m_owner;
        bool m_enabled;
};

#endif//SCRIPT_HPP

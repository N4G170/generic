#include "emitter.hpp"
#include <algorithm>
#include "random.hpp"

Emitter::Emitter() : m_charge{0}, m_cooldown{1}
{

}

Emitter::~Emitter() noexcept
{

}

Emitter::Emitter(const Emitter& other)
{
    m_charge = other.m_charge;
    m_cooldown = other.m_cooldown;
}

Emitter::Emitter(Emitter&& other) noexcept
{
    m_charge = std::move(other.m_charge);
    m_cooldown = std::move(other.m_cooldown);
}

Emitter& Emitter::operator= (const Emitter& other)
{
    Emitter tmp(other);
    *this = std::move(tmp);

    return *this;
}

Emitter& Emitter::operator= (Emitter &&other) noexcept
{
    return *this;
}

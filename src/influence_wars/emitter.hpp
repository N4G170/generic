#ifndef EMITTER_HPP
#define EMITTER_HPP

#include <vector>
#include "influence_cell.hpp"

class Emitter
{
    public:
        Emitter();
        virtual ~Emitter() noexcept;
        Emitter(const Emitter& other);
        Emitter(Emitter&& other) noexcept;

        Emitter& operator= (const Emitter& other);
        Emitter& operator= (Emitter&& other) noexcept;

    private:
        float m_charge;
        float m_cooldown;

        float m_charge_bonus;
        float m_cooldown_bonus;
};

#endif //EMITTER_HPP

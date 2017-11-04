#ifndef UID_HPP
#define UID_HPP

#include <bitset>

using UID = size_t;

enum class IDType
{
    GLOBAL = 0,
    GUI = 1
};

//allows the use of static_assert to check bitset size
template< typename >
struct BitSetSize;
//specialization for bitset
template< std::size_t S >
struct BitSetSize< std::bitset< S > > : std::integral_constant< std::size_t, S > {};

/**
 * \brief Generates a new UID (custom algorithm). Thread safe
 */
UID GenerateUID();

#endif//UID_HPP

#ifndef UID_HPP
#define UID_HPP

#include <bitset>

using UID = std::bitset<16>;
//set of bit that will be incremented. the bit missing will be flags to mark the type of id
using UID_COUNT = std::bitset<12>;
using UID_CONTEXT = std::bitset<4>;

enum UIDType
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

UID GenerateUID(UIDType type = UIDType::GLOBAL);

#endif//UID_HPP

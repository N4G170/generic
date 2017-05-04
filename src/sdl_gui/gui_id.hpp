#ifndef GUI_ID_HPP
#define GUI_ID_HPP

#include <bitset>

using UUID = std::bitset<16>;
//set of bit that will be incremented. the bit missing will be flags to mark the type of id
using UUID_COUNT = std::bitset<12>;
using UUID_CONTEXT = std::bitset<4>;

enum UUIDType
{
    GLOBAL = 2,
    GUI = 1
};

//allows the use of static_assert to check bitset size
template< typename >
struct BitSetSize;
//specialization for bitset
template< std::size_t S >
struct BitSetSize< std::bitset< S > > : std::integral_constant< std::size_t, S > {};


UUID GenerateUUID(UUIDType type = UUIDType::GLOBAL)
{
    static_assert(BitSetSize<UUID>::value == (BitSetSize<UUID_COUNT>::value + BitSetSize<UUID_CONTEXT>::value), "ERROR! Invalid UUID sizes.");
    static unsigned int s_uuid_count{0};
    // x bits reserved for context
    UUID_CONTEXT context_id = type;
    // y bits for counting
    UUID_COUNT count_id = s_uuid_count;
    //final uuid
    UUID final_id;

    for(int i{0}; i < context_id.size(); ++i)
        final_id[final_id.size() - 1 - i] = context_id[ context_id.size() - 1 - i];

    for(int i{0}; i < count_id.size(); ++i)
        final_id[i] = count_id[i];

    ++s_uuid_count;

    return final_id;
}

#endif//GUI_ID_HPP

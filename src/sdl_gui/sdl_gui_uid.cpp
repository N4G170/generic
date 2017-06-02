#include "sdl_gui_uid.hpp"

namespace sdl_gui
{
UID GenerateUID(UIDType type)
{
    static_assert(BitSetSize<UID>::value == (BitSetSize<UID_COUNT>::value + BitSetSize<UID_CONTEXT>::value), "ERROR! Invalid UUID sizes.");
    static unsigned int s_uuid_count{0};
    // x bits reserved for context
    UID_CONTEXT context_id = type;
    // y bits for counting
    UID_COUNT count_id = s_uuid_count;
    //final uuid
    UID final_id;

    for(unsigned int i{0}; i < context_id.size(); ++i)
        final_id[final_id.size() - 1 - i] = context_id[ context_id.size() - 1 - i];

    for(unsigned int i{0}; i < count_id.size(); ++i)
        final_id[i] = count_id[i];

    ++s_uuid_count;

    return final_id;
}
}//namespace

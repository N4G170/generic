###########################
#          RAIN           #
###########################

set(INCLUDE_DIRECTORIES src/particles/include)

set(SOURCE_FILES "")
set(FILES_PATH "src/particles/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}particle.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}particle_emitter.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}particles_manager.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}particles_state.cpp")

#headers
set(HEADER_FILES "")
set(FILES_PATH "src/particles/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}particle.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}particle_emitter.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}particles_manager.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}particles_state.hpp")

###########################
#          RAIN           #
###########################

set(INCLUDE_DIRECTORIES src/paticle/include)

set(SOURCE_FILES "")
set(FILES_PATH "src/particles/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}paticle.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}paticle_manager.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}paticle_state.cpp")

#headers
set(HEADER_FILES "")
set(FILES_PATH "src/paticle/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}paticle.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}paticle_manager.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}paticle_state.hpp")

######################################
#                SNAKE               #
######################################

set(INCLUDE_DIRECTORIES src/snake/include)

set(SOURCE_FILES "")
set(FILES_PATH "src/snake/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}snake_game.cpp")

set(HEADER_FILES "")
set(FILES_PATH "src/snake/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}snake_game.hpp")

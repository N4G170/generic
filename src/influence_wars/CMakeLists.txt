###########################
#     INFLUENCE WARS      #
###########################

set(INCLUDE_DIRECTORIES src/influence_wars/include)

set(SOURCE_FILES "")
set(FILES_PATH "src/influence_wars/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}emitter.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}influence_wars.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}voronoi.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}influence_cell.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}PerlinNoise.cpp")#not mine

#headers
set(HEADER_FILES "")
set(FILES_PATH "src/influence_wars/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}emitter.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}influence_wars.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}influence_cell.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}noise.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}voronoi.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}PerlinNoise.h")#not mine

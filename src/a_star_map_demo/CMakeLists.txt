###########################
#       A* MAP DEMO       #
###########################

set(INCLUDE_DIRECTORIES src/a_star_map_demo/include)

set(SOURCE_FILES "")
set(FILES_PATH "src/a_star_map_demo/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}army.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}infobox.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}map_demo.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}map.cpp")

#headers
set(HEADER_FILES "")
set(FILES_PATH "src/a_star_map_demo/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}army.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}infobox.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}map_demo.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}map.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}pathfind.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}pathfind_utils.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}map_structs.hpp")

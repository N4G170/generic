###########################
#          SOLAR          #
###########################

set(INCLUDE_DIRECTORIES src/solar/include)

set(SOURCE_FILES "")
set(FILES_PATH "src/solar/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}planet.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}solar_system.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}comet.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}xeno.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}background_stars.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}orbit_render.cpp")

#headers
set(HEADER_FILES "")
set(FILES_PATH "src/solar/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}planet.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}solar_system.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}comet.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}xeno.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}background_stars.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}orbit_render.hpp")

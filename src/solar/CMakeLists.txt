###########################
#          SOLAR          #
###########################

set(INCLUDE_DIRECTORIES src/solar/include)

set(SOURCE_FILES "")
set(FILES_PATH "src/solar/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}celestial_body.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}orbits.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}solar_system.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}space_rock.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}xeno.cpp")

#headers
set(HEADER_FILES "")
set(FILES_PATH "src/solar/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}celestial_body.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}orbits.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}solar_system.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}space_rock.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}xeno.hpp")


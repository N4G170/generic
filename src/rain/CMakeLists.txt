###########################
#          RAIN           #
###########################

set(INCLUDE_DIRECTORIES src/rain/include)

set(SOURCE_FILES "")
set(FILES_PATH "src/rain/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}drop.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}rain.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}light.cpp")

#headers
set(HEADER_FILES "")
set(FILES_PATH "src/rain/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}drop.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}rain.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}light.hpp")

###########################
#          BASE           #
###########################

set(INCLUDE_DIRECTORIES src/base/include)

set(SOURCE_FILES "")
set(FILES_PATH "src/base/src/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}deleters.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}graph.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}graph_node.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}main.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}menu.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}message_writer.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}object.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}perlin_noise.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}random.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}resource_manager.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}shapes.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}state_machine.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}texture.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}transform.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}uid.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}utils.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}vector2.cpp")

#headers
set(HEADER_FILES "")
set(FILES_PATH "src/base/include/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}constants.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}deleters.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}enums.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}graph.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}graph_node.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}menu.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}message_writer.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}object.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}perlin_noise.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}random.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}resource_manager.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}shapes.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}state_interface.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}state_machine.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}texture.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}transform.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}uid.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}utils.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}vector2.hpp")
###########################
#          BASE           #
###########################

set(SOURCE_FILES "")
set(HEADER_FILES "")

# <f> Base
set(INCLUDE_DIRECTORIES src/base/include)

#headers
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
list(APPEND HEADER_FILES "${FILES_PATH}shapes.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}state_interface.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}state_machine.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}texture.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}texture_utils.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}transform.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}uid.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}utils.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}vector3.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}vector3_utils.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}debug_render.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}custom_texture.hpp")

#source
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
list(APPEND SOURCE_FILES "${FILES_PATH}shapes.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}state_machine.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}texture.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}texture_utils.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}transform.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}uid.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}utils.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}debug_render.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}custom_texture.cpp")

# </f> /Base

# <f> Managers
list(APPEND INCLUDE_DIRECTORIES src/base/include/managers)

set(FILES_PATH "src/base/include/managers/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}resource_manager.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}object_manager.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}collision_manager.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}system_manager.hpp")

set(FILES_PATH "src/base/src/managers/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}resource_manager.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}object_manager.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}collision_manager.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}system_manager.cpp")
# </f> /Managers

# <f> Scripts
list(APPEND INCLUDE_DIRECTORIES src/base/include/scripts)

set(FILES_PATH "src/base/include/scripts/")#file path from root
list(APPEND HEADER_FILES "${FILES_PATH}script.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}render_script.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}behaviour_script.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}camera.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}collider.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}image.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}mask.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}basic_frame_animation.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}static_canvas.hpp")
list(APPEND HEADER_FILES "${FILES_PATH}dynamic_canvas.hpp")

set(FILES_PATH "src/base/src/scripts/")#file path from root
list(APPEND SOURCE_FILES "${FILES_PATH}camera.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}collider.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}image.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}mask.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}basic_frame_animation.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}static_canvas.cpp")
list(APPEND SOURCE_FILES "${FILES_PATH}dynamic_canvas.cpp")
# </f> /Scripts

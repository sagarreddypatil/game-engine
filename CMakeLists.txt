cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} 
    src/main.cc
    src/renderer.cc
    src/renderer.hh
)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    Vulkan::Vulkan 
    glfw
    glm::glm
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${Vulkan_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

# compile shaders
# file(GLOB_RECURSE GLSL_SOURCE_FILES
#     "src/shaders/*.vert"
#     "src/shaders/*.frag"
# )

# foreach(GLSL ${GLSL_SOURCE_FILES})
#     get_filename_component(FILE_NAME ${GLSL} NAME)
#     set(SPIRV "${CMAKE_BINARY_DIR}/shaders/${FILE_NAME}.spv")
#     add_custom_command(
#         OUTPUT ${SPIRV}
#         COMMAND glslangValidator -V ${GLSL} -o ${SPIRV}
#         DEPENDS ${GLSL}
#     )
#     list(APPEND SPIRV_BINARY_FILES ${SPIRV})
# endforeach(GLSL)

# add_custom_target(
#     shaders 
#     DEPENDS ${SPIRV_BINARY_FILES}
# )

# add_dependencies(${PROJECT_NAME} shaders)

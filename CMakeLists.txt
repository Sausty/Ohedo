project("Ohedo")

cmake_minimum_required (VERSION 3.8)

set(GLFW_VULKAN_STATIC OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(OHEDO_INCLUDE_DIRS "Ohedo")

include_directories("ext/glfw/include")
include_directories("ext/glad/include")
include_directories("ext/freetype/include")
include_directories("Ohedo")

add_subdirectory (examples)
add_subdirectory (Ohedo)
add_subdirectory (ext/glfw)
add_subdirectory (ext/glad)
add_subdirectory (ext/freetype)

link_libraries(Ohedo glfw)
link_libraries(Ohedo glad)
link_libraries(Ohedo freetype)
link_libraries(examples Ohedo)

target_include_directories(Ohedo PUBLIC "ext/glfw/include")
target_include_directories(Ohedo PUBLIC "ext/glad/include")
target_include_directories(Ohedo PUBLIC "ext/freetype/include")
target_include_directories(Ohedo PUBLIC "ext/cgltf")
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE OHEDO_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/Ohedo/*.h)
file(GLOB_RECURSE OHEDO_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Ohedo/*.c)

add_definitions(-DGLFW_INCLUDE_NONE)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_library(Ohedo ${OHEDO_HEADER} ${OHEDO_SOURCE})
target_link_libraries(Ohedo PUBLIC glfw)
target_link_libraries(Ohedo PUBLIC glad)
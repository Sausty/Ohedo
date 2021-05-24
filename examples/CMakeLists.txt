cmake_minimum_required (VERSION 3.8)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable (examples "triangle.c")

target_include_directories(examples PUBLIC "Ohedo")
target_link_directories(examples PUBLIC Ohedo)
target_link_libraries(examples PUBLIC Ohedo)
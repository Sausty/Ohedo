cmake_minimum_required (VERSION 3.8)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(BatchRendering "BatchRendering.c")
target_link_libraries(BatchRendering PUBLIC Ohedo)
target_link_directories(BatchRendering PUBLIC Ohedo)
target_include_directories(BatchRendering PUBLIC "Ohedo")

add_executable(Triangle "Triangle.c")
target_link_libraries(Triangle PUBLIC Ohedo)
target_link_directories(Triangle PUBLIC Ohedo)
target_include_directories(Triangle PUBLIC "Ohedo")

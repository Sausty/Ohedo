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

add_executable(ECS "ECS.c")
target_link_libraries(ECS PUBLIC Ohedo)
target_link_directories(ECS PUBLIC Ohedo)
target_include_directories(ECS PUBLIC "Ohedo")

add_executable(TextRendering "TextRendering.c")
target_link_libraries(TextRendering PUBLIC Ohedo)
target_link_directories(TextRendering PUBLIC Ohedo)
target_include_directories(TextRendering PUBLIC "Ohedo")

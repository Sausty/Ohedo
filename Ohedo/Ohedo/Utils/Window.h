#ifndef OHEDO_WINDOW_H
#define OHEDO_WINDOW_H

#include <Ohedo/Utils/Types.h>

typedef void(*Ohedo_ResizeCallback)(int, int);
typedef void(*Ohedo_CloseCallback)();

struct GLFWwindow;

Ohedo_Define_Struct(Ohedo_Window)
struct Ohedo_Window
{
    struct GLFWwindow* pointer;
    i32 width;
    i32 height;
    char* title;
};

Ohedo_Window* Ohedo_CreateWindow(i32 width, i32 height, char* title);
void Ohedo_FreeWindow(Ohedo_Window* window);

i32 Ohedo_WindowShouldClose(Ohedo_Window* window);
void Ohedo_UpdateWindow(Ohedo_Window* window);

void Ohedo_SetWindowSizeCallback(Ohedo_ResizeCallback fun);
void Ohedo_SetWindowCloseCallback(Ohedo_CloseCallback fun);
void Ohedo_WindowInstallCallbacks(Ohedo_Window* window);

#endif
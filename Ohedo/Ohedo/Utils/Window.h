#ifndef OHEDO_WINDOW_H
#define OHEDO_WINDOW_H

#include <Ohedo/Utils/Types.h>

typedef void(*Ohedo_ResizeCallback)(int, int);
typedef void(*Ohedo_CloseCallback)();

struct GLFWwindow;

typedef struct OhedoWindow OhedoWindow;
struct OhedoWindow
{
    struct GLFWwindow* pointer;
    i32 width;
    i32 height;
    char* title;
};

OhedoWindow* Ohedo_CreateWindow(i32 width, i32 height, char* title);
void Ohedo_FreeWindow(OhedoWindow* window);

i32 Ohedo_WindowShouldClose(OhedoWindow* window);
void Ohedo_UpdateWindow(OhedoWindow* window);

void Ohedo_SetWindowSizeCallback(Ohedo_ResizeCallback fun);
void Ohedo_SetWindowCloseCallback(Ohedo_CloseCallback fun);
void Ohedo_WindowInstallCallbacks(OhedoWindow* window);

#endif
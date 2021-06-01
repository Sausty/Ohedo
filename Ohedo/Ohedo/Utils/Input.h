#ifndef OHEDO_INPUT_H
#define OHEDO_INPUT_H

#include <Ohedo/Utils/Types.h>
#include <Ohedo/Utils/Window.h>
#include <Ohedo/Maths/Vec2.h>

#define Ohedo_CreateInputHandler(handler_name, window) Ohedo_InputHandler handler_name; handler_name.window = window;

Ohedo_Define_Struct(Ohedo_InputHandler)
struct Ohedo_InputHandler
{
    Ohedo_Window* window;
};

i32 Ohedo_IsKeyPressed(Ohedo_InputHandler handler, i32 key);
i32 Ohedo_IsKeyReleased(Ohedo_InputHandler handler, i32 key);
i32 Ohedo_IsMouseButtonPressed(Ohedo_InputHandler handler, i32 btn);
i32 Ohedo_IsMouseButtonReleased(Ohedo_InputHandler handler, i32 btn);
Ohedo_Vec2 Ohedo_GetMousePosition(Ohedo_InputHandler handler);

#endif
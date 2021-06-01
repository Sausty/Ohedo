#include "Input.h"

#include <GLFW/glfw3.h>

i32 Ohedo_IsKeyPressed(Ohedo_InputHandler handler, i32 key)
{
    return glfwGetKey(handler.window->pointer, key) == GLFW_PRESS;
}

i32 Ohedo_IsKeyReleased(Ohedo_InputHandler handler, i32 key)
{
    return glfwGetKey(handler.window->pointer, key) == GLFW_RELEASE;
}

i32 Ohedo_IsMouseButtonPressed(Ohedo_InputHandler handler, i32 btn)
{
    return glfwGetMouseButton(handler.window->pointer, btn) == GLFW_PRESS;
}

i32 Ohedo_IsMouseButtonReleased(Ohedo_InputHandler handler, i32 btn)
{
    return glfwGetMouseButton(handler.window->pointer, btn) == GLFW_RELEASE;
}

Ohedo_Vec2 Ohedo_GetMousePosition(Ohedo_InputHandler handler)
{
    Ohedo_Vec2 vec;
    glfwGetCursorPos(handler.window->pointer, &vec.x, &vec.y);
    return vec;
}
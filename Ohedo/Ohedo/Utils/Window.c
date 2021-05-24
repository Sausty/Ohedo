#include "Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>

static Ohedo_CloseCallback s_CloseCallback;
static Ohedo_ResizeCallback s_ResizeCallback;

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

void Ohedo_GLFWCloseCallback(GLFWwindow* window)
{
    s_CloseCallback();
}

void Ohedo_GLFWResizeCallback(GLFWwindow* window, i32 width, i32 height)
{
    s_ResizeCallback(width, height);
}

OhedoWindow* Ohedo_CreateWindow(i32 width, i32 height, char* title)
{
    OhedoWindow* result = malloc(sizeof(OhedoWindow));

    result->width = width;
    result->height = height;    
    result->title = title;
    result->pointer = glfwCreateWindow(width, height, title, NULL, NULL);
    
    glfwMakeContextCurrent(result->pointer);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(MessageCallback, 0);

    return result;
}

void Ohedo_FreeWindow(OhedoWindow* window)
{
    glfwDestroyWindow(window->pointer);
}

i32 Ohedo_WindowShouldClose(OhedoWindow* window)
{
    return glfwWindowShouldClose(window->pointer);
}

void Ohedo_UpdateWindow(OhedoWindow* window)
{
    glfwPollEvents();
    glfwSwapBuffers(window->pointer);
}

void Ohedo_SetWindowSizeCallback(Ohedo_ResizeCallback fun)
{
    s_ResizeCallback = fun;
}

void Ohedo_SetWindowCloseCallback(Ohedo_CloseCallback fun)
{
    s_CloseCallback = fun;
}

void Ohedo_WindowInstallCallbacks(OhedoWindow* window)
{
    if (s_ResizeCallback)   glfwSetWindowSizeCallback(window->pointer, Ohedo_GLFWResizeCallback);
    if (s_CloseCallback)    glfwSetWindowCloseCallback(window->pointer, Ohedo_GLFWCloseCallback);
}
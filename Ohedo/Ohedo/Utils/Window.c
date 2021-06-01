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

Ohedo_Window* Ohedo_CreateWindow(i32 width, i32 height, char* title)
{
    Ohedo_Window* result = malloc(sizeof(Ohedo_Window));

    result->width = width;
    result->height = height;    
    result->title = title;
    result->pointer = glfwCreateWindow(width, height, title, NULL, NULL);
    
    glfwMakeContextCurrent(result->pointer);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glfwSwapInterval(0);

    return result;
}

void Ohedo_FreeWindow(Ohedo_Window* window)
{
    glfwDestroyWindow(window->pointer);
}

i32 Ohedo_WindowShouldClose(Ohedo_Window* window)
{
    return glfwWindowShouldClose(window->pointer);
}

void Ohedo_UpdateWindow(Ohedo_Window* window)
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

void Ohedo_WindowInstallCallbacks(Ohedo_Window* window)
{
    if (s_ResizeCallback)   glfwSetWindowSizeCallback(window->pointer, Ohedo_GLFWResizeCallback);
    if (s_CloseCallback)    glfwSetWindowCloseCallback(window->pointer, Ohedo_GLFWCloseCallback);
}
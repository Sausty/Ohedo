#include "Ohedo.h"

#include <GLFW/glfw3.h>

static Ohedo_InitFlags s_InitFlags;

i32 Ohedo_Init(Ohedo_InitFlags flags)
{
    s_InitFlags = flags;

    if (flags & Ohedo_InitFlags_Video)
    {
        return glfwInit();
    }
    if (flags & Ohedo_InitFlags_All)
    {
        return glfwInit();
    }

    return 0;
}

void Ohedo_Shutdown()
{
    if (s_InitFlags & Ohedo_InitFlags_Video)
    {
        glfwTerminate();
    }
    if (s_InitFlags & Ohedo_InitFlags_All)
    {
        glfwTerminate();
    }
}
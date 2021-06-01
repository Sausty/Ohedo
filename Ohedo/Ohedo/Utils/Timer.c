#include "Timer.h"

#include <GLFW/glfw3.h>

Ohedo_Timer Ohedo_CreateTimer()
{
    Ohedo_Timer time;
    time.current = 0;
    time.dt = 1;
    time.last = 0;
    return time;
}

void Ohedo_UpdateTimer(Ohedo_Timer* timer)
{
    timer->current = glfwGetTime();
    timer->dt = timer->current - timer->last;
    timer->last = timer->current;
}
#ifndef OHEDO_TIMER_H
#define OHEDO_TIMER_H

#include <Ohedo/Utils/Types.h>

Ohedo_Define_Struct(Ohedo_Timer)
struct Ohedo_Timer
{
    u32 last;
    u32 dt;
    u32 current;
};

Ohedo_Timer Ohedo_CreateTimer();
void Ohedo_UpdateTimer(Ohedo_Timer* timer);

#endif

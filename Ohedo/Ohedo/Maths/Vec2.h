#ifndef OHEDO_VEC2_H
#define OHEDO_VEC2_H

#include <Ohedo/Utils/Types.h>

typedef struct Ohedo_Vec2 Ohedo_Vec2;
struct Ohedo_Vec2
{
    f32 x;
    f32 y;
};

Ohedo_Vec2 Ohedo_Vec2_New(f32 x, f32 y);
Ohedo_Vec2 Ohedo_Vec2_Identity();
Ohedo_Vec2 Ohedo_Vec2_Scalar(f32 scalar);

Ohedo_Vec2 Ohedo_Vec2_Add(Ohedo_Vec2 left, Ohedo_Vec2 right);
Ohedo_Vec2 Ohedo_Vec2_Sub(Ohedo_Vec2 left, Ohedo_Vec2 right);
Ohedo_Vec2 Ohedo_Vec2_Mul(Ohedo_Vec2 left, Ohedo_Vec2 right);
Ohedo_Vec2 Ohedo_Vec2_Div(Ohedo_Vec2 left, Ohedo_Vec2 right);

Ohedo_Vec2 Ohedo_Vec2_Add_Scalar(Ohedo_Vec2 left, f32 right);
Ohedo_Vec2 Ohedo_Vec2_Sub_Scalar(Ohedo_Vec2 left, f32 right);
Ohedo_Vec2 Ohedo_Vec2_Mul_Scalar(Ohedo_Vec2 left, f32 right);
Ohedo_Vec2 Ohedo_Vec2_Div_Scalar(Ohedo_Vec2 left, f32 right);

f32 Ohedo_Vec2_Magnitude(Ohedo_Vec2 vec);
Ohedo_Vec2 Ohedo_Vec2_Normalise(Ohedo_Vec2 vec);
f32 Ohedo_Vec2_Distance(Ohedo_Vec2 left, Ohedo_Vec2 right);
f32 Ohedo_Vec2_Dot(Ohedo_Vec2 left, Ohedo_Vec2 right);

i32 Ohedo_Vec2_Eq(Ohedo_Vec2 left, Ohedo_Vec2 right);
i32 Ohedo_Vec2_Not_Eq(Ohedo_Vec2 left, Ohedo_Vec2 right);
i32 Ohedo_Vec2_Greater(Ohedo_Vec2 left, Ohedo_Vec2 right);
i32 Ohedo_Vec2_Greater_Equal(Ohedo_Vec2 left, Ohedo_Vec2 right);
i32 Ohedo_Vec2_Less(Ohedo_Vec2 left, Ohedo_Vec2 right);
i32 Ohedo_Vec2_Less_Equal(Ohedo_Vec2 left, Ohedo_Vec2 right);


#endif
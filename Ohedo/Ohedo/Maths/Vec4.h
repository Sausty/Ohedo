#ifndef OHEDO_VEC4_H
#define OHEDO_VEC4_H

#include <Ohedo/Utils/Types.h>

typedef struct Ohedo_Vec4 Ohedo_Vec4;
struct Ohedo_Vec4
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

Ohedo_Vec4 Ohedo_Vec4_New(f32 x, f32 y, f32 z, f32 w);
Ohedo_Vec4 Ohedo_Vec4_Identity();
Ohedo_Vec4 Ohedo_Vec4_Scalar(f32 scalar);

Ohedo_Vec4 Ohedo_Vec4_Add(Ohedo_Vec4 left, Ohedo_Vec4 right);
Ohedo_Vec4 Ohedo_Vec4_Sub(Ohedo_Vec4 left, Ohedo_Vec4 right);
Ohedo_Vec4 Ohedo_Vec4_Mul(Ohedo_Vec4 left, Ohedo_Vec4 right);
Ohedo_Vec4 Ohedo_Vec4_Div(Ohedo_Vec4 left, Ohedo_Vec4 right);

Ohedo_Vec4 Ohedo_Vec4_Add_Scalar(Ohedo_Vec4 left, f32 right);
Ohedo_Vec4 Ohedo_Vec4_Sub_Scalar(Ohedo_Vec4 left, f32 right);
Ohedo_Vec4 Ohedo_Vec4_Mul_Scalar(Ohedo_Vec4 left, f32 right);
Ohedo_Vec4 Ohedo_Vec4_Div_Scalar(Ohedo_Vec4 left, f32 right);

f32 Ohedo_Vec4_Dot(Ohedo_Vec4 left, Ohedo_Vec4 right);

i32 Ohedo_Vec4_Eq(Ohedo_Vec4 left, Ohedo_Vec4 right);
i32 Ohedo_Vec4_Not_Eq(Ohedo_Vec4 left, Ohedo_Vec4 right);
i32 Ohedo_Vec4_Greater(Ohedo_Vec4 left, Ohedo_Vec4 right);
i32 Ohedo_Vec4_Greater_Equal(Ohedo_Vec4 left, Ohedo_Vec4 right);
i32 Ohedo_Vec4_Less(Ohedo_Vec4 left, Ohedo_Vec4 right);
i32 Ohedo_Vec4_Less_Equal(Ohedo_Vec4 left, Ohedo_Vec4 right);


#endif
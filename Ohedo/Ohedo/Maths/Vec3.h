#ifndef OHEDO_VEC3_H
#define OHEDO_VEC3_H

#include <Ohedo/Utils/Types.h>

typedef struct Ohedo_Vec3 Ohedo_Vec3;
struct Ohedo_Vec3
{
    f32 x;
    f32 y;
    f32 z;
};

Ohedo_Vec3 Ohedo_Vec3_New(f32 x, f32 y, f32 z);
Ohedo_Vec3 Ohedo_Vec3_Identity();
Ohedo_Vec3 Ohedo_Vec3_Scalar(f32 scalar);

Ohedo_Vec3 Ohedo_Vec3_Add(Ohedo_Vec3 left, Ohedo_Vec3 right);
Ohedo_Vec3 Ohedo_Vec3_Sub(Ohedo_Vec3 left, Ohedo_Vec3 right);
Ohedo_Vec3 Ohedo_Vec3_Mul(Ohedo_Vec3 left, Ohedo_Vec3 right);
Ohedo_Vec3 Ohedo_Vec3_Div(Ohedo_Vec3 left, Ohedo_Vec3 right);

Ohedo_Vec3 Ohedo_Vec3_Add_Scalar(Ohedo_Vec3 left, f32 right);
Ohedo_Vec3 Ohedo_Vec3_Sub_Scalar(Ohedo_Vec3 left, f32 right);
Ohedo_Vec3 Ohedo_Vec3_Mul_Scalar(Ohedo_Vec3 left, f32 right);
Ohedo_Vec3 Ohedo_Vec3_Div_Scalar(Ohedo_Vec3 left, f32 right);

f32 Ohedo_Vec3_Magnitude(Ohedo_Vec3 vec);
Ohedo_Vec3 Ohedo_Vec3_Normalise(Ohedo_Vec3 vec);
f32 Ohedo_Vec3_Distance(Ohedo_Vec3 left, Ohedo_Vec3 right);
f32 Ohedo_Vec3_Dot(Ohedo_Vec3 left, Ohedo_Vec3 right);
Ohedo_Vec3 Ohedo_Vec3_Cross(Ohedo_Vec3 left, Ohedo_Vec3 right);

i32 Ohedo_Vec3_Eq(Ohedo_Vec3 left, Ohedo_Vec3 right);
i32 Ohedo_Vec3_Not_Eq(Ohedo_Vec3 left, Ohedo_Vec3 right);
i32 Ohedo_Vec3_Greater(Ohedo_Vec3 left, Ohedo_Vec3 right);
i32 Ohedo_Vec3_Greater_Equal(Ohedo_Vec3 left, Ohedo_Vec3 right);
i32 Ohedo_Vec3_Less(Ohedo_Vec3 left, Ohedo_Vec3 right);
i32 Ohedo_Vec3_Less_Equal(Ohedo_Vec3 left, Ohedo_Vec3 right);


#endif
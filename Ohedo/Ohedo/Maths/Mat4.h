#ifndef OHEDO_MAT4_H
#define OHEDO_MAT4_H

#include <Ohedo/Utils/Types.h>
#include <Ohedo/Maths/Vec3.h>

typedef struct Ohedo_Mat4 Ohedo_Mat4;
struct Ohedo_Mat4
{
    f32 data[16];
};

Ohedo_Mat4 Ohedo_Mat4_New();
Ohedo_Mat4 Ohedo_Mat4_Identity();
Ohedo_Mat4 Ohedo_Mat4_Diagonal(f32 diagonal);

Ohedo_Mat4 Ohedo_Mat4_Multiply(Ohedo_Mat4 left, Ohedo_Mat4 right);
Ohedo_Vec3 Ohedo_Mat4_Multiply_V3(Ohedo_Mat4 left, Ohedo_Vec3 right);

// Transform stuff
Ohedo_Mat4 Ohedo_Mat4_Translate(Ohedo_Vec3 vector);
Ohedo_Mat4 Ohedo_Mat4_Scale(Ohedo_Vec3 vector);
Ohedo_Mat4 Ohedo_Mat4_Rotate(Ohedo_Vec3 vector, f32 angle);

// Camera stuff
Ohedo_Mat4 Ohedo_Mat4_Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
Ohedo_Mat4 Ohedo_Mat4_Perspective(f32 fov, f32 aspectRatio, f32 near, f32 far);
Ohedo_Mat4 Ohedo_Mat4_LookAt(Ohedo_Vec3 cam, Ohedo_Vec3 obj, Ohedo_Vec3 up);

#endif
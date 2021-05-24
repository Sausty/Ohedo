#include "Vec4.h"

#include <math.h>

Ohedo_Vec4 Ohedo_Vec4_New(f32 x, f32 y, f32 z, f32 w)
{
    Ohedo_Vec4 res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return res;
}

Ohedo_Vec4 Ohedo_Vec4_Identity() 
{ 
    return Ohedo_Vec4_New(0, 0, 0, 0); 
}

Ohedo_Vec4 Ohedo_Vec4_Scalar(f32 scalar) 
{ 
    return Ohedo_Vec4_New(scalar, scalar, scalar, scalar); 
}

Ohedo_Vec4 Ohedo_Vec4_Add(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return Ohedo_Vec4_New(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

Ohedo_Vec4 Ohedo_Vec4_Sub(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return Ohedo_Vec4_New(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

Ohedo_Vec4 Ohedo_Vec4_Mul(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return Ohedo_Vec4_New(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
}

Ohedo_Vec4 Ohedo_Vec4_Div(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return Ohedo_Vec4_New(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
}

Ohedo_Vec4 Ohedo_Vec4_Add_Scalar(Ohedo_Vec4 left, f32 right)
{
    return Ohedo_Vec4_New(left.x + right, left.y + right, left.z + right, left.w + right);
}

Ohedo_Vec4 Ohedo_Vec4_Sub_Scalar(Ohedo_Vec4 left, f32 right)
{
    return Ohedo_Vec4_New(left.x - right, left.y - right, left.z - right, left.w - right);
}

Ohedo_Vec4 Ohedo_Vec4_Mul_Scalar(Ohedo_Vec4 left, f32 right)
{
    return Ohedo_Vec4_New(left.x * right, left.y * right, left.z * right, left.w * right);
}

Ohedo_Vec4 Ohedo_Vec4_Div_Scalar(Ohedo_Vec4 left, f32 right)
{
    return Ohedo_Vec4_New(left.x / right, left.y / right, left.z / right, left.w / right);
}

f32 Ohedo_Vec4_Dot(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return (left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w);
}

// BOOLEAN SHIT

i32 Ohedo_Vec4_Eq(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}

i32 Ohedo_Vec4_Not_Eq(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return !Ohedo_Vec4_Eq(left, right);
}

i32 Ohedo_Vec4_Greater(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return left.x > right.x && left.y > right.y && left.z > right.z && left.w > right.w;
}

i32 Ohedo_Vec4_Greater_Equal(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return left.x >= right.x && left.y >= right.y && left.z >= right.z && left.w >= right.w;
}

i32 Ohedo_Vec4_Less(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return left.x < right.x && left.y < right.y && left.z < right.z && left.w < right.w;
}

i32 Ohedo_Vec4_Less_Equal(Ohedo_Vec4 left, Ohedo_Vec4 right)
{
    return left.x <= right.x && left.y <= right.y && left.z <= right.z && left.w <= right.w;
}

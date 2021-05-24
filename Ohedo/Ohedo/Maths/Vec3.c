#include "Vec3.h"

#include <math.h>

Ohedo_Vec3 Ohedo_Vec3_New(f32 x, f32 y, f32 z)
{
    Ohedo_Vec3 res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

Ohedo_Vec3 Ohedo_Vec3_Identity() 
{ 
    return Ohedo_Vec3_New(0, 0, 0); 
}

Ohedo_Vec3 Ohedo_Vec3_Scalar(f32 scalar) 
{ 
    return Ohedo_Vec3_New(scalar, scalar, scalar); 
}

Ohedo_Vec3 Ohedo_Vec3_Add(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return Ohedo_Vec3_New(left.x + right.x, left.y + right.y, left.z + right.z);
}

Ohedo_Vec3 Ohedo_Vec3_Sub(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return Ohedo_Vec3_New(left.x - right.x, left.y - right.y, left.z - right.z);
}

Ohedo_Vec3 Ohedo_Vec3_Mul(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return Ohedo_Vec3_New(left.x * right.x, left.y * right.y, left.z / right.z);
}

Ohedo_Vec3 Ohedo_Vec3_Div(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return Ohedo_Vec3_New(left.x / right.x, left.y / right.y, left.z / right.z);
}

Ohedo_Vec3 Ohedo_Vec3_Add_Scalar(Ohedo_Vec3 left, f32 right)
{
    return Ohedo_Vec3_New(left.x + right, left.y + right, left.z + right);
}

Ohedo_Vec3 Ohedo_Vec3_Sub_Scalar(Ohedo_Vec3 left, f32 right)
{
    return Ohedo_Vec3_New(left.x - right, left.y - right, left.z - right);
}

Ohedo_Vec3 Ohedo_Vec3_Mul_Scalar(Ohedo_Vec3 left, f32 right)
{
    return Ohedo_Vec3_New(left.x * right, left.y * right, left.z * right);
}

Ohedo_Vec3 Ohedo_Vec3_Div_Scalar(Ohedo_Vec3 left, f32 right)
{
    return Ohedo_Vec3_New(left.x / right, left.y / right, left.z / right);
}


f32 Ohedo_Vec3_Magnitude(Ohedo_Vec3 vec)
{
    return (f32)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}  

Ohedo_Vec3 Ohedo_Vec3_Normalise(Ohedo_Vec3 vec)
{
    f32 length = Ohedo_Vec3_Magnitude(vec);
    return Ohedo_Vec3_New(vec.x / length, vec.y / length, vec.z / length);
}

f32 Ohedo_Vec3_Distance(Ohedo_Vec3 left, Ohedo_Vec3 right)
{   
    f32 a = left.x - right.x;
    f32 b = left.y - right.y;
    f32 c = left.z - right.z;

    return (f32)sqrt(a * a + b * b + c * c);
}

f32 Ohedo_Vec3_Dot(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return (left.x * right.x + left.y * right.y + left.z * right.z);
}

Ohedo_Vec3 Ohedo_Vec3_Cross(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return Ohedo_Vec3_New(left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x);
}

// BOOLEAN SHIT

i32 Ohedo_Vec3_Eq(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return left.x == right.x && left.y == right.y && left.z == right.z;
}

i32 Ohedo_Vec3_Not_Eq(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return !Ohedo_Vec3_Eq(left, right);
}

i32 Ohedo_Vec3_Greater(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return left.x > right.x && left.y > right.y && left.z > right.z;
}

i32 Ohedo_Vec3_Greater_Equal(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return left.x >= right.x && left.y >= right.y && left.z >= right.z;
}

i32 Ohedo_Vec3_Less(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return left.x < right.x && left.y < right.y && left.z < right.z;
}

i32 Ohedo_Vec3_Less_Equal(Ohedo_Vec3 left, Ohedo_Vec3 right)
{
    return left.x <= right.x && left.y <= right.y && left.z <= right.z;
}

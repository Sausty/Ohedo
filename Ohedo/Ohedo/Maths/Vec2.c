#include "Vec2.h"

#include <math.h>

Ohedo_Vec2 Ohedo_Vec2_New(f32 x, f32 y)
{
    Ohedo_Vec2 res;
    res.x = x;
    res.y = y;
    return res;
}

Ohedo_Vec2 Ohedo_Vec2_Identity() 
{ 
    return Ohedo_Vec2_New(0, 0); 
}

Ohedo_Vec2 Ohedo_Vec2_Scalar(f32 scalar) 
{ 
    return Ohedo_Vec2_New(scalar, scalar); 
}

Ohedo_Vec2 Ohedo_Vec2_Add(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return Ohedo_Vec2_New(left.x + right.x, left.y + right.y);
}

Ohedo_Vec2 Ohedo_Vec2_Sub(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return Ohedo_Vec2_New(left.x - right.x, left.y - right.y);
}

Ohedo_Vec2 Ohedo_Vec2_Mul(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return Ohedo_Vec2_New(left.x * right.x, left.y * right.y);
}

Ohedo_Vec2 Ohedo_Vec2_Div(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return Ohedo_Vec2_New(left.x / right.x, left.y / right.y);
}

Ohedo_Vec2 Ohedo_Vec2_Add_Scalar(Ohedo_Vec2 left, f32 right)
{
    return Ohedo_Vec2_New(left.x + right, left.y + right);
}

Ohedo_Vec2 Ohedo_Vec2_Sub_Scalar(Ohedo_Vec2 left, f32 right)
{
    return Ohedo_Vec2_New(left.x - right, left.y - right);
}

Ohedo_Vec2 Ohedo_Vec2_Mul_Scalar(Ohedo_Vec2 left, f32 right)
{
    return Ohedo_Vec2_New(left.x * right, left.y * right);
}

Ohedo_Vec2 Ohedo_Vec2_Div_Scalar(Ohedo_Vec2 left, f32 right)
{
    return Ohedo_Vec2_New(left.x / right, left.y / right);
}


f32 Ohedo_Vec2_Magnitude(Ohedo_Vec2 vec)
{
    return (f32)sqrt(vec.x * vec.x + vec.y * vec.y);
}  

Ohedo_Vec2 Ohedo_Vec2_Normalise(Ohedo_Vec2 vec)
{
    f32 length = Ohedo_Vec2_Magnitude(vec);
    return Ohedo_Vec2_New(vec.x / length, vec.y / length);
}

f32 Ohedo_Vec2_Distance(Ohedo_Vec2 left, Ohedo_Vec2 right)
{   
    f32 a = left.x - right.x;
    f32 b = left.y - right.y;

    return (f32)sqrt(a * a + b * b);
}

f32 Ohedo_Vec2_Dot(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return (left.x * right.x + left.y * right.y);
}

// BOOLEAN SHIT

i32 Ohedo_Vec2_Eq(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return left.x == right.x && left.y == right.y;
}

i32 Ohedo_Vec2_Not_Eq(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return !Ohedo_Vec2_Eq(left, right);
}

i32 Ohedo_Vec2_Greater(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return left.x > right.x && left.y > right.y;
}

i32 Ohedo_Vec2_Greater_Equal(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return left.x >= right.x && left.y >= right.y;
}

i32 Ohedo_Vec2_Less(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return left.x < right.x && left.y < right.y;
}

i32 Ohedo_Vec2_Less_Equal(Ohedo_Vec2 left, Ohedo_Vec2 right)
{
    return left.x <= right.x && left.y <= right.y;
}

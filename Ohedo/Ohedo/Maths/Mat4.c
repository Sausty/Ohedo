#include "Mat4.h"

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

static f32 toRadians(f32 angle)
{
    return (f32)(angle * M_PI / 180);
}

Ohedo_Mat4 Ohedo_Mat4_New()
{
    Ohedo_Mat4 mat;
    memset(&mat, 0, sizeof(Ohedo_Mat4));
    
    for (i32 i = 0; i < 16; i++)
        mat.data[i] = 0.0f;

    return mat;
}

Ohedo_Mat4 Ohedo_Mat4_Identity()
{
    Ohedo_Mat4 mat = Ohedo_Mat4_New();
    
    mat.data[0 + 0 * 4] = 1.0f;
    mat.data[1 + 1 * 4] = 1.0f;
    mat.data[2 + 2 * 4] = 1.0f;
    mat.data[3 + 3 * 4] = 1.0f;
    
    return mat;
}

Ohedo_Mat4 Ohedo_Mat4_Diagonal(f32 diagonal)
{
    Ohedo_Mat4 mat = Ohedo_Mat4_New();
    
    mat.data[0 + 0 * 4] = diagonal;
    mat.data[1 + 1 * 4] = diagonal;
    mat.data[2 + 2 * 4] = diagonal;
    mat.data[3 + 3 * 4] = diagonal;
    
    return mat;
}

Ohedo_Mat4 Ohedo_Mat4_Multiply(Ohedo_Mat4 left, Ohedo_Mat4 right)
{
    float data[16];
	for (i32 row = 0; row < 4; row++)
	{
		for (i32 col = 0; col < 4; col++)
		{
			float sum = 0.0f;
			for (i32 e = 0; e < 4; e++)
			{
				sum += left.data[e + row * 4] * right.data[col + e * 4];
			}
			data[col + row * 4] = sum;
		}
	}
	memcpy(left.data, data, 4 * 4 * sizeof(float));
	return left;
}

Ohedo_Vec3 Ohedo_Mat4_Multiply_V3(Ohedo_Mat4 left, Ohedo_Vec3 right)
{
    f32 x = left.data[0 + 0 * 4] * right.x + left.data[0 + 1 * 4] * right.y + left.data[0 + 2 * 4] * right.z + left.data[0 + 3 * 4];
    f32 y = left.data[1 + 0 * 4] * right.x + left.data[1 + 1 * 4] * right.y + left.data[1 + 2 * 4] * right.z + left.data[1 + 3 * 4];
    f32 z = left.data[2 + 0 * 4] * right.x + left.data[2 + 1 * 4] * right.y + left.data[2 + 2 * 4] * right.z + left.data[2 + 3 * 4];

    return Ohedo_Vec3_New(x, y, z);
}

Ohedo_Mat4 Ohedo_Mat4_Translate(Ohedo_Vec3 vector)
{
    Ohedo_Mat4 result = Ohedo_Mat4_Identity();
    
    result.data[0 + 3 * 4] = vector.x;
    result.data[1 + 3 * 4] = vector.y;
    result.data[2 + 3 * 4] = vector.z;
    
    return result;
}

Ohedo_Mat4 Ohedo_Mat4_Scale(Ohedo_Vec3 vector)
{
    Ohedo_Mat4 result = Ohedo_Mat4_Identity();
    
    result.data[0 + 0 * 4] = vector.x;
    result.data[1 + 1 * 4] = vector.y;
    result.data[2 + 2 * 4] = vector.z;
    
    return result;
}

Ohedo_Mat4 Ohedo_Mat4_Rotate(Ohedo_Vec3 vector, f32 angle)
{
    Ohedo_Mat4 result = Ohedo_Mat4_Identity();
    
    f32 r = toRadians(angle);
    f32 c = (f32)cos(r);
    f32 s = (f32)sin(r);
    f32 omc = 1.0f - c;

    f32 x = vector.x;
    f32 y = vector.y;
    f32 z = vector.z;
    
    // X
    result.data[0 + 0 * 4] = x * x * omc + c;
    result.data[0 + 1 * 4] = y * x * omc + z * s;
    result.data[0 + 2 * 4] = x * z * omc - y * s;

    // Y
    result.data[1 + 0 * 4] = x * y * omc - z * s;
    result.data[1 + 1 * 4] = y * y * omc + c;
    result.data[1 + 2 * 4] = y * z * omc + x * s;

    // Z
    result.data[2 + 0 * 4] = x * z * omc + y * s;
    result.data[2 + 1 * 4] = y * z * omc - x * s;
    result.data[2 + 2 * 4] = z * z * omc + c;
    
    return result;
}

Ohedo_Mat4 Ohedo_Mat4_Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
{
    Ohedo_Mat4 result = Ohedo_Mat4_Identity();
    
    result.data[0 + 0 * 4] = 2.0f / (right - left);
    result.data[1 + 1 * 4] = 2.0f / (top - bottom);
    result.data[2 + 2 * 4] = 2.0f / (near - far);
    
    result.data[3 + 0 * 4] = (left + right) / (left - right);
    result.data[3 + 1 * 4] = (bottom + top) / (bottom - top);
    result.data[3 + 2 * 4] = (far + near) / (far - near);
    
    return result;
}

Ohedo_Mat4 Ohedo_Mat4_Perspective(f32 fov, f32 aspectRatio, f32 near, f32 far)
{
    Ohedo_Mat4 result = Ohedo_Mat4_Identity();
    
    f32 q = 1.0f / (f32)tan(toRadians(0.5f * fov));
    f32 a = q / aspectRatio;
    
    f32 b = (near + far) / (near - far);
    f32 c = (2.0f * near * far) / (near - far);
    
    result.data[0 + 0 * 4] = a;
    result.data[1 + 1 * 4] = q;
    result.data[2 + 2 * 4] = b;
    result.data[2 + 3 * 4] = -1.0f;
    result.data[3 + 2 * 4] = c;
    
    return result;
}
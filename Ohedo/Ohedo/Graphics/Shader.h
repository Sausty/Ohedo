#ifndef OHEDO_SHADER_H
#define OHEDO_SHADER_H

#include <Ohedo/Utils/Types.h>

#include <Ohedo/Maths/Vec2.h>
#include <Ohedo/Maths/Vec3.h>
#include <Ohedo/Maths/Vec4.h>
#include <Ohedo/Maths/Mat4.h>

typedef struct Ohedo_Shader Ohedo_Shader;
struct Ohedo_Shader
{
    RenderID id;
};

Ohedo_Shader Ohedo_CreateShaderFromSource(char* vertexSource, char* fragmentSource);
Ohedo_Shader Ohedo_CreateShaderFromFile(char* vertexPath, char* fragmentPath);
void Ohedo_DeleteShader(Ohedo_Shader shader);
void Ohedo_BindShader(Ohedo_Shader shader);
void Ohedo_UnbindShader();

// Uniforms
void Ohedo_ShaderUniformFloat(Ohedo_Shader shader, char* name, float value);
void Ohedo_ShaderUniformFloat2(Ohedo_Shader shader, char* name, Ohedo_Vec2 value);
void Ohedo_ShaderUniformFloat3(Ohedo_Shader shader, char* name, Ohedo_Vec3 value);
void Ohedo_ShaderUniformFloat4(Ohedo_Shader shader, char* name, Ohedo_Vec4 value);

void Ohedo_ShaderUniformInt(Ohedo_Shader shader, char* name, int value);
void Ohedo_ShaderUniformInt2(Ohedo_Shader shader, char* name, Ohedo_Vec2 value);
void Ohedo_ShaderUniformInt3(Ohedo_Shader shader, char* name, Ohedo_Vec3 value);
void Ohedo_ShaderUniformInt4(Ohedo_Shader shader, char* name, Ohedo_Vec4 value);

void Ohedo_ShaderUniformMat4(Ohedo_Shader shader, char* name, Ohedo_Mat4 value);

#endif

#ifndef OHEDO_SHADER_H
#define OHEDO_SHADER_H

#include <Ohedo/Utils/Types.h>

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

// TODO : Uniforms

#endif

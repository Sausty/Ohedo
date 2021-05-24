#include "Shader.h"

#include <glad/glad.h>
#include <stdio.h>

Ohedo_Shader Ohedo_CreateShaderFromSource(char* vertexSource, char* fragmentSource)
{
    Ohedo_Shader shader;
    shader.id = glCreateProgram();

    RenderID vertexShader = glCreateShader(GL_VERTEX_SHADER);
    RenderID fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Vertex Shader
    {        
        glShaderSource(vertexShader, 1, (const GLchar* const*)&vertexSource, 0);
        glCompileShader(vertexShader);
        
        i32 isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
		{
            i32 maxLength = 512;

			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			printf("Ohedo Vertex Shader Compile Error: %s\n", infoLog);
		}

        glAttachShader(shader.id, vertexShader);
    }

    // Fragment Shader
    {
        glShaderSource(fragmentShader, 1, (const GLchar* const*)&fragmentSource, 0);
        glCompileShader(fragmentShader);
        
        i32 isCompiled = 0;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
		{
            i32 maxLength = 512;

			char infoLog[512];
			glGetShaderInfoLog(fragmentShader, 512, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);

			printf("Ohedo Fragment Shader Compile Error: %s\n", infoLog);
		}

        glAttachShader(shader.id, fragmentShader);
    }

    // Compile / Link program
    glLinkProgram(shader.id);
    glValidateProgram(shader.id);

    i32 isLinked = 0;
    glGetProgramiv(shader.id, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        i32 maxLength = 512;

		char infoLog[512];
		glGetProgramInfoLog(shader.id, 512, &maxLength, &infoLog[0]);

		glDeleteProgram(shader.id);

		printf("Ohedo Shader Program Linking Error: %s\n", infoLog);
    }

    glDetachShader(shader.id, vertexShader);
    glDetachShader(shader.id, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

Ohedo_Shader Ohedo_CreateShaderFromFile(char* vertexPath, char* fragmentPath)
{
    Ohedo_Shader shader;
    shader.id = 0;

    // TODO : From file

    return shader;
}

void Ohedo_DeleteShader(Ohedo_Shader shader)
{
    glDeleteProgram(shader.id);
}

void Ohedo_BindShader(Ohedo_Shader shader)
{
    glUseProgram(shader.id);
}

void Ohedo_UnbindShader()
{
    glUseProgram(0);
}
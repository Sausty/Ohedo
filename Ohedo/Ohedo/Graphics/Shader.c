#include "Shader.h"

#include <glad/glad.h>
#include <stdio.h>

char* read_file(char* path)
{
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen(path, "r");
    if (!fp)
        return NULL;
    
    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    buffer = calloc(1, lSize + 1);
    if (!buffer)
    {
        fclose(fp);
        return NULL;
    }

    fread(buffer, lSize, 1, fp);

    fclose(fp);
    return buffer;
}

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
    shader.id = glCreateProgram();

    RenderID vertexShader = glCreateShader(GL_VERTEX_SHADER);
    RenderID fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    char* vertexSource = read_file(vertexPath);
    char* fragmentSource = read_file(fragmentPath);

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

    free(vertexSource);
    free(fragmentSource);

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

void Ohedo_ShaderUniformFloat(Ohedo_Shader shader, char* name, float value)
{
    i32 loc = glGetUniformLocation(shader.id, name);
    glUniform1f(loc, value);
}

void Ohedo_ShaderUniformFloat2(Ohedo_Shader shader, char* name, Ohedo_Vec2 value)
{
    i32 loc = glGetUniformLocation(shader.id, name);
    glUniform2f(loc, value.x, value.y);
}

void Ohedo_ShaderUniformFloat3(Ohedo_Shader shader, char* name, Ohedo_Vec3 value)
{
    i32 loc = glGetUniformLocation(shader.id, name);
    glUniform3f(loc, value.x, value.y, value.z);
}

void Ohedo_ShaderUniformFloat4(Ohedo_Shader shader, char* name, Ohedo_Vec4 value)
{
    i32 loc = glGetUniformLocation(shader.id, name);
    glUniform4f(loc, value.x, value.y, value.z, value.w);
}


void Ohedo_ShaderUniformInt(Ohedo_Shader shader, char* name, int value)
{
    i32 loc = glGetUniformLocation(shader.id, name);
    glUniform1i(loc, value);
}

void Ohedo_ShaderUniformInt2(Ohedo_Shader shader, char* name, Ohedo_Vec2 value)
{
    i32 loc = glGetUniformLocation(shader.id, name);
    glUniform2i(loc, value.x, value.y);
}

void Ohedo_ShaderUniformInt3(Ohedo_Shader shader, char* name, Ohedo_Vec3 value)
{
    i32 loc = glGetUniformLocation(shader.id, name);
    glUniform3i(loc, value.x, value.y, value.z);
}

void Ohedo_ShaderUniformInt4(Ohedo_Shader shader, char* name, Ohedo_Vec4 value)
{
    i32 loc = glGetUniformLocation(shader.id, name);
    glUniform4i(loc, value.x, value.y, value.z, value.w);
}

void Ohedo_ShaderUniformMat4(Ohedo_Shader shader, char* name, Ohedo_Mat4 value)
{
    i32 loc = glGetUniformLocation(shader.id, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, value.data);
}

void Ohedo_ShaderUniformIntArray(Ohedo_Shader shader, char* name, i32* array, u32 count)
{
    i32 loc = glGetUniformLocation(shader.id, name);
    glUniform1iv(loc, count, array);
}
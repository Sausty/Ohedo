#include "RenderCommand.h"

#include <glad/glad.h>

void Ohedo_RendererClear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Ohedo_RendererClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Ohedo_RendererViewport(int scissorX, int scisoorY, int width, int height)
{
    glViewport(scissorX, scisoorY, width, height);
}

void Ohedo_RendererDraw(int start, int vertexCount)
{
    glDrawArrays(GL_TRIANGLES, start, vertexCount);
}
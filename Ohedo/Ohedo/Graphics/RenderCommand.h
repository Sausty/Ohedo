#ifndef OHEDO_RENDERCOMMAND_H
#define OHEDO_RENDERCOMMAND_H

void Ohedo_RendererClear();
void Ohedo_RendererClearColor(float r, float g, float b, float a);
void Ohedo_RendererViewport(int scissorX, int scisoorY, int width, int height);
void Ohedo_RendererDraw(int start, int vertexCount);

#endif
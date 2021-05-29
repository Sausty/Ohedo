#include "BatchRenderer.h"

#include <Ohedo/Graphics/VertexArray.h>
#include <Ohedo/Graphics/VertexBuffer.h>
#include <Ohedo/Graphics/Shader.h>
#include <Ohedo/Graphics/IndexBuffer.h>
#include <Ohedo/Graphics/RenderCommand.h>

#include <stdio.h>
#include <math.h>
#include <glad/glad.h>

#define MaxQuads 20000
#define MaxVertices MaxQuads * 4
#define MaxIndices MaxQuads * 6
#define MaxTextureSlots 32

Ohedo_Define_Struct(OhedoBatchVertex)
struct OhedoBatchVertex
{
    Ohedo_Vec3 Position;
    Ohedo_Vec3 Color;
    Ohedo_Vec2 TexCoord;
    f32 TexIndex;
};

Ohedo_Define_Struct(OhedoBatchData)
struct OhedoBatchData
{
    Ohedo_VertexArray QuadVertexArray;
    Ohedo_VertexBuffer QuadVertexBuffer;
    Ohedo_IndexBuffer QuadIndexBuffer;
    Ohedo_Shader TextureShader;
    Ohedo_Texture2D WhiteTexture;

    u32 QuadIndexCount;
    OhedoBatchVertex* QuadVertexBufferBase;
    OhedoBatchVertex* QuadVertexBufferPtr;

    i32 TextureSlots[MaxTextureSlots];
    i32 Samplers[MaxTextureSlots];
    u32 TextureSlotIndex;

    Ohedo_Vec3 QuadVertexPositions[4];
};

static OhedoBatchData s_Data;

void PrivFlush()
{
    if (s_Data.QuadIndexCount == 0)
		return; // Nothing to draw

	u32 dataSize = (u32)((u8*)s_Data.QuadVertexBufferPtr - (u8*)s_Data.QuadVertexBufferBase);
    Ohedo_SetVertexBufferData(s_Data.QuadVertexBuffer, s_Data.QuadVertexBufferBase, dataSize);

    for (u32 i = 0; i < s_Data.TextureSlotIndex; i++)
	{
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, s_Data.TextureSlots[i]);
    }

    Ohedo_BindShader(s_Data.TextureShader);
    Ohedo_ShaderUniformIntArray(s_Data.TextureShader, "u_Textures", s_Data.Samplers, 32);
    Ohedo_BindVertexArray(s_Data.QuadVertexArray);
    Ohedo_BindIndexBuffer(s_Data.QuadIndexBuffer);
    Ohedo_RendererDrawIndexed(0, s_Data.QuadIndexCount);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void PrivStartBatch()
{
    s_Data.QuadIndexCount = 0;
	s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

	s_Data.TextureSlotIndex = 1;
}

void PrivNextBatch()
{
    PrivFlush();
    PrivStartBatch();
}

void Ohedo_Batch_Init()
{
    s_Data.QuadVertexArray = Ohedo_CreateVertexArray();
    Ohedo_BindVertexArray(s_Data.QuadVertexArray);

    s_Data.QuadVertexBuffer = Ohedo_CreateVertexBufferEmpty(MaxVertices * sizeof(OhedoBatchVertex));
    Ohedo_BindVertexBuffer(s_Data.QuadVertexBuffer);

    Ohedo_AddVertexAttribute(0, 3, sizeof(OhedoBatchVertex), 0, Ohedo_VertexAttributeType_Float);
    Ohedo_AddVertexAttribute(1, 3, sizeof(OhedoBatchVertex), sizeof(float) * 3, Ohedo_VertexAttributeType_Float);
    Ohedo_AddVertexAttribute(2, 2, sizeof(OhedoBatchVertex), sizeof(float) * 6, Ohedo_VertexAttributeType_Float);
    Ohedo_AddVertexAttribute(3, 1, sizeof(OhedoBatchVertex), sizeof(float) * 8, Ohedo_VertexAttributeType_Float);

    s_Data.QuadVertexBufferBase = malloc(sizeof(OhedoBatchVertex) * MaxVertices);
    u32* quadIndices = malloc(sizeof(u32) * MaxIndices);

    u32 offset = 0;
    for (u32 i = 0; i < MaxIndices; i += 6)
    {
        quadIndices[i + 0] = offset + 0;
		quadIndices[i + 1] = offset + 1;
		quadIndices[i + 2] = offset + 2;

		quadIndices[i + 3] = offset + 2;
		quadIndices[i + 4] = offset + 3;
		quadIndices[i + 5] = offset + 0;

		offset += 4;
    }

    s_Data.QuadIndexBuffer = Ohedo_CreateIndexBuffer(quadIndices, MaxIndices * sizeof(u32));
    free(quadIndices);

    u32 whiteTextureData = 0xffffffff;
    s_Data.WhiteTexture = Ohedo_CreateTextureFromMemory(&whiteTextureData, 1, 1, 0);
    s_Data.TextureSlots[0] = s_Data.WhiteTexture.id;

    // Shader
    char* vertexShader = "#version 430 core\n\nlayout(location = 0) in vec3 v_Position;\nlayout(location = 1) in vec3 v_Color;\nlayout(location = 2) in vec2 v_TexCoords;\nlayout(location = 3) in float v_TexIndex;\n\nout vec3 f_Position;\nout vec3 f_Color;\nout vec2 f_TexCoords;\nout flat float f_TexIndex;\n\nuniform mat4 u_ViewProjection;\n\nvoid main() {\n\tf_Position = v_Position;\n\tf_Color = v_Color;\n\tf_TexCoords = v_TexCoords;\n\tf_TexIndex = v_TexIndex;\n\tgl_Position = u_ViewProjection * vec4(v_Position, 1.0);\n}\n";
    char* fragmentShader = "#version 430 core\n\nlayout(location = 0) out vec4 FragColor;\n\nin vec3 f_Position;\nin vec3 f_Color;\nin vec2 f_TexCoords;\nin flat float f_TexIndex;\n\nuniform sampler2D u_Textures[32];\n\nvoid main() {\n\tvec4 color = vec4(f_Color, 1.0);\ncolor *= texture(u_Textures[int(f_TexIndex)], f_TexCoords);\nif (color.a < 0.2)\n\t\tdiscard;\n\nFragColor = color;\n}";

    s_Data.TextureShader = Ohedo_CreateShaderFromSource(vertexShader, fragmentShader);

    s_Data.QuadVertexPositions[0] = Ohedo_Vec3_New(-0.5f, -0.5f, 0.0f);
	s_Data.QuadVertexPositions[1] = Ohedo_Vec3_New( 0.5f, -0.5f, 0.0f);
	s_Data.QuadVertexPositions[2] = Ohedo_Vec3_New( 0.5f,  0.5f, 0.0f);
	s_Data.QuadVertexPositions[3] = Ohedo_Vec3_New(-0.5f,  0.5f, 0.0f);

    for (i32 i = 0; i < 32; i++)
        s_Data.Samplers[i] = i;
}

void Ohedo_Batch_Shutdown()
{
    Ohedo_DeleteVertexBuffer(s_Data.QuadVertexBuffer);
    Ohedo_DeleteVertexArray(s_Data.QuadVertexArray);
    Ohedo_DeleteShader(s_Data.TextureShader);
    free(s_Data.QuadVertexBufferBase);
}

void Ohedo_Batch_Begin(Ohedo_Mat4 viewProjection)
{
    Ohedo_BindShader(s_Data.TextureShader);
    Ohedo_ShaderUniformMat4(s_Data.TextureShader, "u_ViewProjection", viewProjection);

    PrivStartBatch();
}

void Ohedo_Batch_End()
{
    PrivFlush();
}

void Ohedo_Batch_Draw_Quad(Ohedo_Vec3 pos, Ohedo_Vec2 scale, Ohedo_Vec3 rotation, f32 angle, Ohedo_Vec3 color)
{
    Ohedo_Mat4 transform = Ohedo_Mat4_Translate(pos);
    Ohedo_Mat4 scale_mat = Ohedo_Mat4_Scale(Ohedo_Vec3_New(scale.x, scale.y, 1.0f));
    Ohedo_Mat4 rot_mat = Ohedo_Mat4_Rotate(rotation, angle);

    transform = Ohedo_Mat4_Multiply(transform, rot_mat);
    transform = Ohedo_Mat4_Multiply(transform, scale_mat);

    Ohedo_Batch_Draw_Quad_Mat4(transform, color);
}

void Ohedo_Batch_Draw_Quad_Mat4(Ohedo_Mat4 transform, Ohedo_Vec3 color)
{
    size_t quadVertexCount = 4;
    const Ohedo_Vec2 textureCoords[] = {
        Ohedo_Vec2_New(0.0f, 0.0f),
        Ohedo_Vec2_New(1.0f, 0.0f),
        Ohedo_Vec2_New(1.0f, 1.0f),
        Ohedo_Vec2_New(0.0f, 1.0f)
    };
    
    if (s_Data.QuadIndexCount >= MaxIndices)
        PrivNextBatch();
    
    for (size_t i = 0; i < quadVertexCount; i++)
    {
        s_Data.QuadVertexBufferPtr->Position = Ohedo_Mat4_Multiply_V3(transform, s_Data.QuadVertexPositions[i]);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
		s_Data.QuadVertexBufferPtr->TexIndex = 0.0f;
		s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;
}

void Ohedo_Batch_Draw_Textured_Quad(Ohedo_Vec3 pos, Ohedo_Vec2 scale, Ohedo_Vec3 rotation, f32 angle, Ohedo_Vec3 color, Ohedo_Texture2D texture)
{
    Ohedo_Mat4 transform = Ohedo_Mat4_Translate(pos);
    Ohedo_Mat4 scale_mat = Ohedo_Mat4_Scale(Ohedo_Vec3_New(scale.x, scale.y, 1.0f));
    Ohedo_Mat4 rot_mat = Ohedo_Mat4_Rotate(rotation, angle);

    transform = Ohedo_Mat4_Multiply(transform, rot_mat);
    transform = Ohedo_Mat4_Multiply(transform, scale_mat);

    Ohedo_Batch_Draw_Textured_Quad_Mat4(transform, color, texture);
}

void Ohedo_Batch_Draw_Textured_Quad_Mat4(Ohedo_Mat4 transform, Ohedo_Vec3 color, Ohedo_Texture2D texture)
{
    size_t quadVertexCount = 4;
    const Ohedo_Vec2 textureCoords[] = {
        Ohedo_Vec2_New(0.0f, 0.0f),
        Ohedo_Vec2_New(1.0f, 0.0f),
        Ohedo_Vec2_New(1.0f, 1.0f),
        Ohedo_Vec2_New(0.0f, 1.0f)
    };
    
    if (s_Data.QuadIndexCount >= MaxIndices)
        PrivNextBatch();

    float textureIndex = 0.0f;
    for (u32 i = 1; i < s_Data.TextureSlotIndex; i++)
    {
        if (s_Data.TextureSlots[i] == texture.id)
        {
            textureIndex = (float)i;
            break;
        }
    }

    if (textureIndex == 0.0f)
    {
        if (s_Data.TextureSlotIndex >= MaxTextureSlots)
			PrivNextBatch();

		textureIndex = (float)s_Data.TextureSlotIndex;
		s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture.id;
		s_Data.TextureSlotIndex++;
    }
    
    for (size_t i = 0; i < quadVertexCount; i++)
    {
        s_Data.QuadVertexBufferPtr->Position = Ohedo_Mat4_Multiply_V3(transform, s_Data.QuadVertexPositions[i]);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += 6;
}
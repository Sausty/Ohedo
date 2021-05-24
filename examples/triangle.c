#include <Ohedo/Ohedo.h>
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

void resize_callback(int width, int height)
{
    printf("%d, %d\n", width, height);
    Ohedo_RendererViewport(0, 0, width, height);
}

int main()
{
    Ohedo_Init(Ohedo_InitFlags_All);

    OhedoWindow* window = Ohedo_CreateWindow(1280, 720, "Hello Ohedo!");
    Ohedo_SetWindowSizeCallback(resize_callback);
    Ohedo_WindowInstallCallbacks(window);

    // Shader
    char* vertexSource = read_file("shaders/vertex.vert");
    char* fragmentSource = read_file("shaders/fragment.frag");

    Ohedo_Shader shader = Ohedo_CreateShaderFromSource(vertexSource, fragmentSource);
    free(vertexSource);
    free(fragmentSource);

    // VAO
    Ohedo_VertexArray vao = Ohedo_CreateVertexArray();
    Ohedo_BindVertexArray(vao);

    // VBO
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    }; 

    u32 indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    Ohedo_VertexBuffer vbo = Ohedo_CreateVertexBuffer(vertices, sizeof(vertices));
    Ohedo_BindVertexBuffer(vbo);

    Ohedo_IndexBuffer ebo = Ohedo_CreateIndexBuffer(indices, sizeof(indices));
    Ohedo_BindIndexBuffer(ebo);

    // Attributes
    Ohedo_AddVertexAttribute(0, 3, sizeof(float) * 3, 0, Ohedo_VertexAttributeType_Float);

    Ohedo_UnbindVertexBuffer();
    Ohedo_UnbindVertexArray();

    // Matrix
    Ohedo_Mat4 transform = Ohedo_Mat4_Translate(Ohedo_Vec3_New(0.5f, 0.0f, 0.0f));

    while (!Ohedo_WindowShouldClose(window))
    {
        Ohedo_RendererClear();
        Ohedo_RendererClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        Ohedo_BindShader(shader);
        Ohedo_BindVertexArray(vao);

        Ohedo_ShaderUniformMat4(shader, "u_Transform", transform);

        Ohedo_RendererDrawIndexed(0, 6);

        Ohedo_UpdateWindow(window);
    }

    Ohedo_DeleteIndexBuffer(ebo);
    Ohedo_DeleteVertexBuffer(vbo);
    Ohedo_DeleteVertexArray(vao);
    Ohedo_DeleteShader(shader);

    Ohedo_FreeWindow(window);
    Ohedo_Shutdown();
    return 0;
}
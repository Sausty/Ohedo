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
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    Ohedo_VertexBuffer vbo = Ohedo_CreateVertexBuffer(vertices, sizeof(vertices));
    Ohedo_BindVertexBuffer(vbo);

    // Attributes
    Ohedo_AddVertexAttribute(0, 3, sizeof(float) * 3, 0, Ohedo_VertexAttributeType_Float);

    Ohedo_UnbindVertexBuffer();
    Ohedo_UnbindVertexArray();

    while (!Ohedo_WindowShouldClose(window))
    {
        Ohedo_RendererClear();
        Ohedo_RendererClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        Ohedo_BindShader(shader);
        Ohedo_BindVertexArray(vao);

        Ohedo_RendererDraw(0, 3);

        Ohedo_UpdateWindow(window);
    }

    Ohedo_DeleteVertexBuffer(vbo);
    Ohedo_DeleteVertexArray(vao);
    Ohedo_DeleteShader(shader);

    Ohedo_FreeWindow(window);
    Ohedo_Shutdown();
    return 0;
}
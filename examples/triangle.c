#include <Ohedo/Ohedo.h>
#include <stdio.h>

// Call glViewport when the window is resized
void resize_callback(int width, int height)
{
    printf("%d, %d\n", width, height);
    Ohedo_RendererViewport(0, 0, width, height);
}

int main()
{
    // Init all the subsystems
    Ohedo_Init(Ohedo_InitFlags_All);

    // Create the window and set callbacks
    Ohedo_Window* window = Ohedo_CreateWindow(1280, 720, "Hello Ohedo!");
    Ohedo_SetWindowSizeCallback(resize_callback);
    Ohedo_WindowInstallCallbacks(window);

    // Shader
    Ohedo_Shader shader = Ohedo_CreateShaderFromFile("shaders/triangle/vertex.vert", "shaders/triangle/fragment.frag");

    // VAO
    Ohedo_VertexArray vao = Ohedo_CreateVertexArray();
    Ohedo_BindVertexArray(vao);

    // VBO
    float vertices[] = {
         0.0f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
    }; 

    Ohedo_VertexBuffer vbo = Ohedo_CreateVertexBuffer(vertices, sizeof(vertices));
    Ohedo_BindVertexBuffer(vbo);

    // Attributes
    Ohedo_AddVertexAttribute(0, 3, sizeof(float) * 3, 0, Ohedo_VertexAttributeType_Float);

    Ohedo_UnbindVertexBuffer();
    Ohedo_UnbindVertexArray();

    // Main loop
    while (!Ohedo_WindowShouldClose(window))
    {
        // Clear
        Ohedo_RendererClear();
        Ohedo_RendererClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        // Draw 
        Ohedo_BindShader(shader);
        Ohedo_BindVertexArray(vao);
        Ohedo_RendererDraw(0, 3),
        Ohedo_UnbindShader();
        Ohedo_UnbindVertexArray();

        // Poll events and swap buffers
        Ohedo_UpdateWindow(window);
    }

    // Free all resources and shutdown Ohedo
    Ohedo_DeleteVertexBuffer(vbo);
    Ohedo_DeleteVertexArray(vao);
    Ohedo_DeleteShader(shader);
    Ohedo_FreeWindow(window);
    Ohedo_Shutdown();
    
    return 0;
}
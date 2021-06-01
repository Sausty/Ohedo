#include <Ohedo/Ohedo.h>
#include <stdio.h>

static Ohedo_Mat4 transform;
static Ohedo_Vec3 position;
static Ohedo_InputHandler handler;

// Call glViewport when the window is resized
void resize_callback(int width, int height)
{
    printf("%d, %d\n", width, height);
    Ohedo_RendererViewport(0, 0, width, height);
}

// Custom material update function
void mat_update(Ohedo_Material* mat)
{
    Ohedo_Mat4 cam = Ohedo_Mat4_Perspective(90.0f, 1280.0f / 720.0f, 0.01f, 1000.0f);

    position.z = -3.0f;

    if (Ohedo_IsKeyPressed(handler, OHEDO_KEY_LEFT))
        position.x += 0.001f;
    if (Ohedo_IsKeyPressed(handler, OHEDO_KEY_RIGHT))
        position.x -= 0.001f;
    if (Ohedo_IsKeyPressed(handler, OHEDO_KEY_DOWN))
        position.y += 0.001f;
    if (Ohedo_IsKeyPressed(handler, OHEDO_KEY_UP))
        position.y -= 0.001f;

    transform = Ohedo_Mat4_Translate(position);
    transform = Ohedo_Mat4_Multiply(transform, Ohedo_Mat4_Rotate(Ohedo_Vec3_New(1.0f, 0.0f, 0.0f), 90.0f));

    Ohedo_ShaderUniformMat4(mat->shader, "u_Camera", cam);
    Ohedo_ShaderUniformMat4(mat->shader, "u_Transform", transform);
}

int main()
{
    transform = Ohedo_Mat4_Identity();
    position = Ohedo_Vec3_Identity();

    // Init all the subsystems
    Ohedo_Init(Ohedo_InitFlags_All);

    // Create the window and set callbacks
    Ohedo_Window* window = Ohedo_CreateWindow(1280, 720, "Hello Ohedo!");
    Ohedo_SetWindowSizeCallback(resize_callback);
    Ohedo_WindowInstallCallbacks(window);

    handler.window = window;

    // Shader
    Ohedo_Shader shader = Ohedo_CreateShaderFromFile("shaders/mesh/vertex.vert", "shaders/mesh/fragment.frag");
    Ohedo_Material material = Ohedo_CreateMaterial(shader);
    Ohedo_Mesh mesh = Ohedo_CreateMeshFromGLTF("assets/models/DamagedHelmet.gltf");

    Ohedo_Texture2D baseColor = Ohedo_CreateTextureFromFile("assets/textures/DamagedHelmetAlbedo.jpg", 1);

    Ohedo_SetMaterialUpdateCallback(&material, mat_update);
    Ohedo_AddMaterialTexture(&material, baseColor, "u_AlbedoTexture");

    // Main loop
    while (!Ohedo_WindowShouldClose(window))
    {
        // Clear
        Ohedo_RendererClear();
        Ohedo_RendererClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        // Draw 
        Ohedo_BindMaterial(&material);
        Ohedo_DrawMesh(mesh);
        Ohedo_UnbindMaterial(material);

        // Poll events and swap buffers
        Ohedo_UpdateWindow(window);
    }

    Ohedo_FreeMesh(mesh);
    Ohedo_FreeMaterial(material);
    Ohedo_FreeWindow(window);
    Ohedo_Shutdown();
    
    return 0;
}
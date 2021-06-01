#include <Ohedo/Ohedo.h>
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

static f32 toRadians(f32 angle)
{
    return (f32)(angle * M_PI / 180);
}

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

    if (Ohedo_IsKeyPressed(handler, OHEDO_KEY_A))
        position.x += 0.1f;
    if (Ohedo_IsKeyPressed(handler, OHEDO_KEY_D))
        position.x -= 0.1f;
    if (Ohedo_IsKeyPressed(handler, OHEDO_KEY_S))
        position.z -= 0.1f;
    if (Ohedo_IsKeyPressed(handler, OHEDO_KEY_W))
        position.z += 0.1f;

    transform = Ohedo_Mat4_Translate(position);
    transform = Ohedo_Mat4_Multiply(transform, Ohedo_Mat4_Rotate(Ohedo_Vec3_New(1.0f, 0.0f, 0.0f), 90.0f));
    transform = Ohedo_Mat4_Multiply(transform, Ohedo_Mat4_Rotate(Ohedo_Vec3_New(0.0f, 0.0f, 1.0f), -45.0f));

    Ohedo_ShaderUniformFloat3(mat->shader, "camPos", position);
    Ohedo_ShaderUniformFloat3(mat->shader, "lightPos", Ohedo_Vec3_New(0.0f, -3.0f, -1.0f));
    Ohedo_ShaderUniformFloat3(mat->shader, "lightColor", Ohedo_Vec3_New(100.0f, 100.0f, 100.0f));
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
    Ohedo_Shader shader = Ohedo_CreateShaderFromFile("shaders/pbr/vertex.vert", "shaders/pbr/fragment.frag");
    Ohedo_Material material = Ohedo_CreateMaterial(shader);
    Ohedo_Mesh mesh = Ohedo_CreateMeshFromGLTF("assets/models/DamagedHelmet.gltf");

    Ohedo_Texture2D baseColor = Ohedo_CreateTextureFromFile("assets/textures/DamagedHelmetAlbedo.jpg", 0);
    Ohedo_Texture2D normalMap = Ohedo_CreateTextureFromFile("assets/textures/DamagedHelmetNormal.jpg", 0);
    Ohedo_Texture2D metalRoughness = Ohedo_CreateTextureFromFile("assets/textures/DamagedHelmetMetalRoughness.jpg", 0);
    Ohedo_Texture2D occlusionMap = Ohedo_CreateTextureFromFile("assets/textures/DamagedHelmetAO.jpg", 0);

    Ohedo_SetMaterialUpdateCallback(&material, mat_update);
    Ohedo_AddMaterialTexture(&material, baseColor, "albedoMap");
    Ohedo_AddMaterialTexture(&material, normalMap, "normalMap");
    Ohedo_AddMaterialTexture(&material, metalRoughness, "metallicRoughnessMap");
    Ohedo_AddMaterialTexture(&material, occlusionMap, "aoMap");

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
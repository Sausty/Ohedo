#include <Ohedo/Ohedo.h>
#include <stdio.h>

// Calls glViewport when the window is resized
void resize_callback(int width, int height)
{
    printf("%d, %d\n", width, height);
    Ohedo_RendererViewport(0, 0, width, height);
}

int main()
{
    // Init all of Ohedo's subsystems
    Ohedo_Init(Ohedo_InitFlags_All);

    // Create the window and set callbacks
    Ohedo_Window* window = Ohedo_CreateWindow(1280, 720, "Hello Ohedo!");
    Ohedo_SetWindowSizeCallback(resize_callback);
    Ohedo_WindowInstallCallbacks(window);
    
    // Instantiate the batch renderer
    Ohedo_Batch_Init();

    // Load an image if you wish
    Ohedo_Texture2D image = Ohedo_CreateTextureFromFile("assets/texture.png", 1);

    // Create Scene
    Ohedo_Scene* scene = Ohedo_CreateScene();

    // Create our textured quad
    Ohedo_Entity quad = Ohedo_CreateEntity(scene);
    
    // Modify the components
    Ohedo_AddTransformComponent(&quad);
    quad.transform->position = Ohedo_Vec3_New(0.0f, 0.0f, -0.8f);
    quad.transform->scale = Ohedo_Vec3_New(2.0f, 1.0f, 1.0f);

    Ohedo_AddSpriteRendererComponent(&quad);
    quad.spriteRenderer->texture = image;
    quad.spriteRenderer->color = Ohedo_Vec3_New(1.0f, 1.0f, 1.0f);

    // Make a custom camera entity
    Ohedo_Entity camera = Ohedo_CreateEntity(scene);

    // Add components
    Ohedo_AddCameraComponent(&camera, 1);
    camera.camera->pv_matrix = Ohedo_Mat4_Perspective(90.0f, 1280.0f / 720.0f, 0.01f, 1000.0f);

    // Add the entities to the scene
    Ohedo_AddEntity(scene, &camera);
    Ohedo_AddEntity(scene, &quad);

    // Load font
    Ohedo_Font font = Ohedo_LoadFont("assets/fonts/jetbrains_mono.ttf", 48);
    Ohedo_InitTextRenderer(Ohedo_Vec2_New(1280.0f, 720.0f));

    // Main loop
    while (!Ohedo_WindowShouldClose(window))
    {
        // Clear
        Ohedo_RendererClear();
        Ohedo_RendererClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        // Update the scene
        Ohedo_UpdateScene(scene);

        // Draw the text
        Ohedo_DrawText(font, "Hello, world!", 25.0f, 25.0f, 1.0f, Ohedo_Vec3_New(1.0f, 1.0f, 1.0f));

        // Poll events and swap buffers
        Ohedo_UpdateWindow(window);
    }

    // Cleanup all resources and shutdown Ohedo
    Ohedo_FreeFont(font);
    Ohedo_DestroyScene(scene);
    Ohedo_Batch_Shutdown();
    Ohedo_DeleteTexture(image);
    Ohedo_FreeWindow(window);
    Ohedo_Shutdown();
    
    return 0;
}
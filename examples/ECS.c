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
    quad.transform->position = Ohedo_Vec3_New(0.5f, 0.0f, 0.0f);

    Ohedo_AddSpriteRendererComponent(&quad);
    quad.spriteRenderer->texture = image;
    quad.spriteRenderer->color = Ohedo_Vec3_New(1.0f, 1.0f, 1.0f);

    // Add the entity to the scene
    Ohedo_AddEntity(scene, &quad);

    // Main loop
    while (!Ohedo_WindowShouldClose(window))
    {
        // Clear
        Ohedo_RendererClear();
        Ohedo_RendererClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        // Update the scene
        Ohedo_UpdateScene(scene);

        // Poll events and swap buffers
        Ohedo_UpdateWindow(window);
    }

    // Cleanup all resources and shutdown Ohedo
    Ohedo_DestroyScene(scene);
    Ohedo_Batch_Shutdown();
    Ohedo_DeleteTexture(image);
    Ohedo_FreeWindow(window);
    Ohedo_Shutdown();
    
    return 0;
}
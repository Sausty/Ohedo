#include <Ohedo/Ohedo.h>
#include <stdio.h>

void resize_callback(int width, int height)
{
    printf("%d, %d\n", width, height);
    Ohedo_RendererViewport(0, 0, width, height);
}

int main()
{
    Ohedo_Init(Ohedo_InitFlags_All);

    Ohedo_Window* window = Ohedo_CreateWindow(1280, 720, "Hello Ohedo!");
    Ohedo_SetWindowSizeCallback(resize_callback);
    Ohedo_WindowInstallCallbacks(window);

    Ohedo_Batch_Init();

    Ohedo_Texture2D image = Ohedo_CreateTextureFromFile("assets/texture.png", 1);

    // Matrix
    Ohedo_Mat4 transform = Ohedo_Mat4_Translate(Ohedo_Vec3_New(0.0f, 0.0f, 0.0f));

    while (!Ohedo_WindowShouldClose(window))
    {
        Ohedo_RendererClear();
        Ohedo_RendererClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        Ohedo_Batch_Begin(Ohedo_Mat4_Identity());
        Ohedo_Batch_Draw_Quad(Ohedo_Vec3_New(-0.75f, 0.0f, 0.0f), Ohedo_Vec2_New(0.25f, 0.25f), Ohedo_Vec3_New(1.0f, 1.0f, 1.0f), 0.0f, Ohedo_Vec3_New(1.0f, 1.0f, 1.0f));
        Ohedo_Batch_Draw_Textured_Quad(Ohedo_Vec3_New(0.75f, 0.0f, 0.0f), Ohedo_Vec2_New(0.25f, 0.25f), Ohedo_Vec3_New(1.0f, 1.0f, 1.0f), 0.0f, Ohedo_Vec3_New(1.0f, 1.0f, 1.0f), image);
        Ohedo_Batch_End();

        Ohedo_UpdateWindow(window);
    }

    Ohedo_Batch_Shutdown();
    Ohedo_DeleteTexture(image);
    Ohedo_FreeWindow(window);
    Ohedo_Shutdown();
    return 0;
}
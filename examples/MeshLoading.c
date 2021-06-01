#include <Ohedo/Ohedo.h>
#include <stdio.h>

// Ohedo doesn't provide a filesystem for now
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
    char* vertexSource = read_file("shaders/mesh/vertex.vert");
    char* fragmentSource = read_file("shaders/mesh/fragment.frag");

    Ohedo_Shader shader = Ohedo_CreateShaderFromSource(vertexSource, fragmentSource);
    free(vertexSource); // Don't forget to free the allocated memory
    free(fragmentSource);

    Ohedo_Material material = Ohedo_CreateMaterial(shader);
    Ohedo_Mesh mesh = Ohedo_CreateMeshFromGLTF("assets/models/DamagedHelmet.gltf");

    Ohedo_Texture2D baseColor = Ohedo_CreateTextureFromFile("assets/textures/DamagedHelmetAlbedo.jpg", 1);

    Ohedo_AddMaterialTexture(&material, baseColor, "u_AlbedoTexture");

    Ohedo_Mat4 transform = Ohedo_Mat4_Translate(Ohedo_Vec3_New(0.0f, 0.0f, -1.0f));
    transform = Ohedo_Mat4_Multiply(transform, Ohedo_Mat4_Rotate(Ohedo_Vec3_New(1.0f, 0.0f, 0.0f), 90.0f));
    Ohedo_Mat4 cam = Ohedo_Mat4_Perspective(90.0f, 1280.0f / 720.0f, 0.01f, 1000.0f);

    // Main loop
    while (!Ohedo_WindowShouldClose(window))
    {
        // Clear
        Ohedo_RendererClear();
        Ohedo_RendererClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        // Draw 
        Ohedo_BindMaterial(material);
        Ohedo_ShaderUniformMat4(material.shader, "u_Camera", cam);
        Ohedo_ShaderUniformMat4(material.shader, "u_Transform", transform);

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
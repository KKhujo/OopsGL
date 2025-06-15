

#include "raylib.h"

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "SynthEngine");

    // Define our custom camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 18.0f, 21.0f, 18.0f };     // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };          // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                    // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                 // Camera projection type

    Image image = LoadImage("Heightmap.png");     // Load heightmap image (RAM)
    Texture2D texture = LoadTextureFromImage(image);        // Convert image to texture (VRAM)

    Mesh mesh = GenMeshHeightmap(image, (Vector3){ 16, 8, 16 }); // Generate heightmap mesh (RAM and VRAM)
    Model model = LoadModelFromMesh(mesh);                  // Load model from generated mesh

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set map diffuse texture
    Vector3 mapPosition = { -8.0f, 0.0f, -8.0f };           // Define model position

    UnloadImage(image);             // Unload heightmap image from RAM, already uploaded to VRAM

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_ORBITAL);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);

        DrawModel(model, mapPosition, 1.0f, BLUE);

         //DrawGrid(20, 1.0f);
        // Custom function to draw a purple grid
        for (int i = -10; i <= 10; i++) {
         DrawLine3D((Vector3){ i, 0, -10 }, (Vector3){ i, 0, 10 }, PURPLE); // Vertical lines
        DrawLine3D((Vector3){ -10, 0, i }, (Vector3){ 10, 0, i }, PURPLE); // Horizontal lines
         }


        EndMode3D();

        // DrawTexture(texture, screenWidth - texture.width - 20, 20, WHITE);
        // DrawRectangleLines(screenWidth - texture.width - 20, 20, texture.width, texture.height, GREEN);

        // DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(texture);     // Unload texture
    UnloadModel(model);         // Unload model

    CloseWindow();

    return 0;
}

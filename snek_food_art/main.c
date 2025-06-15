#include "raylib.h"
#include <time.h>

#define MAX_RECTANGLES 230

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Picasso");

    SetRandomSeed(time(NULL));


    Rectangle rectangles[MAX_RECTANGLES];
    Color colors[MAX_RECTANGLES];

    for (int i = 0; i < MAX_RECTANGLES; i++) {
        rectangles[i].x = GetRandomValue(0, screenWidth - 100);
        rectangles[i].y = GetRandomValue(0, screenHeight - 100);
        rectangles[i].width = GetRandomValue(20, 100);
        rectangles[i].height = GetRandomValue(20, 100);
        colors[i] = (Color){
            GetRandomValue(50, 255),
            GetRandomValue(50, 255),
            GetRandomValue(50, 255),
            255
        }; // Random color
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw all rectangles
        for (int i = 0; i < MAX_RECTANGLES; i++) {
            DrawRectangleRec(rectangles[i], colors[i]);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

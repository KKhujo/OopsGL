#include "raylib.h"

#define WIDTH 1100
#define HEIGHT 700
#define CELL_SIZE 10

int grid[WIDTH][HEIGHT];
int nextGrid[WIDTH][HEIGHT];



void DrawGriid() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            Color color = grid[x][y] ? WHITE : BLACK;
            DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
        }
    }
}

void InitializeGrid() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            grid[x][y] = GetRandomValue(0, 1);
        }
    }
}

void UpdateGrid() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            int liveNeighbors = 0;


            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue; // Skip self
                    int nx = (x + dx + WIDTH) % WIDTH;  //edge wrap
                    int ny = (y + dy + HEIGHT) % HEIGHT;
                    liveNeighbors += grid[nx][ny];
                }
            }

            if (grid[x][y] == 1) {
                nextGrid[x][y] = (liveNeighbors == 2 || liveNeighbors == 3) ? 1 : 0;
            } else {
                nextGrid[x][y] = (liveNeighbors == 3) ? 1 : 0;
            }
        }
    }

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            grid[x][y] = nextGrid[x][y];
        }
    }
}
int main(){


    InitWindow(WIDTH, HEIGHT, "Life");

    SetTargetFPS(1);


    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLUE);
        DrawGriid();
        InitializeGrid();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}


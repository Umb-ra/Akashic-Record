#include <raylib.h>
#include "algo/bresenham.h"
#include "Terrain/terrain.h"
#include "Car/car.h"
#include "Physics/physics.h"
#include <time.h>

int main() {
    InitWindow(0, 0, "Project Hill Climb");
    ToggleFullscreen();
    SetTargetFPS(60);
    srand(time(NULL));
    generateTerrain();
    Car car;
    InitCar(&car, 1200, 300);


    while (!WindowShouldClose()) {
        float dt = GetFrameTime();    
        UpdatePhysics(&car, dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawTerrain();
        drawTrees();
        DrawCar(&car);

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
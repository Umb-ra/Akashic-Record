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
    
    float Screen_width = GetScreenWidth();
    float Screen_height = GetScreenHeight();

    //setup camera
    Camera2D camera = {0};
    camera.offset = (Vector2){Screen_width / 2.0f, Screen_height / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();    
        UpdatePhysics(&car, dt);
        updateSmoke(dt);

        camera.target.x = car.position.x;
        camera.target.y = car.position.y;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        float panjang_max = (TERRAIN_COUNT - 1) * 10.0f;
        float batas_kanan = panjang_max - (Screen_width / 2.0f);
        float batas_kiri = Screen_width / 2.0f;
        if (camera.target.x > batas_kanan) {
            camera.target.x = batas_kanan;
        } else if (camera.target.x < batas_kiri) {
            camera.target.x = batas_kiri;
        }
        BeginMode2D(camera);

        drawTerrain();
        drawTrees();
        drawSmoke();
        DrawCar(&car);

        EndMode2D();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
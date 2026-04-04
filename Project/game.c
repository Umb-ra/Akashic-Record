#include <raylib.h>
#include "algo/bresenham.h"
#include "Terrain/terrain.h"
#include "Car/car.h"
#include "Physics/physics.h"
#include <time.h>
#include "UI/visuals.h"

int main() {
    InitWindow(0, 0, "Project Hill Climb");
    ToggleFullscreen();
    SetTargetFPS(60);
    srand(time(NULL));
    InitAudioDevice();

    generateTerrain();
    float spawn_x = 300.0f;
    float tinggi_tanah_asli = getTerrainHeight(spawn_x);
    float spawn_y = tinggi_tanah_asli;
    Car car;
    InitCar(&car, spawn_x, spawn_y);
    // Setup camera
    Camera2D camera = {0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Texture2D tex_bg = LoadTexture("assets/back2.jpg");
    Texture2D tex_body = LoadTexture("assets/body2.png");
    Texture2D tex_wheel = LoadTexture("assets/wheels.png");

    // Setup music and sound effect
    Music bg_music = LoadMusicStream("assets/bgm.mp3"); 
    Sound gas_sound = LoadSound("assets/gas.wav");
    Sound brake_sound = LoadSound("assets/brake.wav");
    PlayMusicStream(bg_music);

    SetMusicVolume(bg_music, 0.4f); 
    SetSoundVolume(gas_sound, 1.0f);
    SetSoundVolume(brake_sound, 1.0f);

    bool debug_mode = true;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        // --- AMBIL UKURAN LAYAR TIAP FRAME ---
        float Screen_width = GetScreenWidth();
        float Screen_height = GetScreenHeight();
        camera.offset = (Vector2){Screen_width / 2.0f, Screen_height / 2.0f};

        UpdateMusicStream(bg_music);

        if (IsKeyPressed(KEY_TAB)) {
            debug_mode = !debug_mode;
        }

        UpdatePhysics(&car, dt);
        updateSmoke(dt);

        /*if (IsKeyDown(KEY_RIGHT)) {
            if (!IsSoundPlaying(gas_sound)) {
                PlaySound(gas_sound);
            }
        }
        if (IsKeyReleased(KEY_RIGHT)) {
            StopSound(gas_sound);
        }

        if (IsKeyDown(KEY_LEFT)) {
            if (!IsSoundPlaying(brake_sound)) {
                PlaySound(brake_sound);
            }
        }
        if (IsKeyReleased(KEY_LEFT)) {
            StopSound(brake_sound);
        }
        */
        camera.target.x = car.position.x;
        camera.target.y = car.position.y;
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (debug_mode == false) {
            DrawTexturePro(tex_bg, 
                (Rectangle){ 0, 0, (float)tex_bg.width, (float)tex_bg.height }, 
                (Rectangle){ 0, 0, Screen_width, Screen_height }, 
                (Vector2){ 0, 0 }, 0.0f, WHITE);
        }
        
        float panjang_max = (TERRAIN_COUNT - 1) * 10.0f;
        float batas_kanan = panjang_max - (Screen_width / 2.0f);
        float batas_kiri = Screen_width / 2.0f;
        if (camera.target.x > batas_kanan) {
            camera.target.x = batas_kanan;
        } else if (camera.target.x < batas_kiri) {
            camera.target.x = batas_kiri;
        }
        
        BeginMode2D(camera);

        if (debug_mode == true) {
            drawTerrain(true);
            drawTrees(true);
            DrawCar(&car);
        } else {
            // Urutan sangat penting: Tanah -> Pohon -> Mobil
            drawTerrain(false); 
            drawTrees(false);
            DrawGameVisuals(&car, tex_body, tex_wheel); 
        }

        drawSmoke();
        EndMode2D();
        
        DrawText("Tekan TAB untuk ganti mode grafik", 20, 20, 20, DARKGRAY);

        EndDrawing();
    }
    
    // UNLOAD ASSETS
    UnloadTexture(tex_bg);
    UnloadTexture(tex_body);
    UnloadTexture(tex_wheel);

    UnloadMusicStream(bg_music);
    UnloadSound(gas_sound);
    UnloadSound(brake_sound); 
    
    CloseAudioDevice(); 
    CloseWindow();
    return 0;
}
#include "visuals.h"

void DrawGameVisuals(Car *car, Vector2 *terrain, int terrain_count, Texture2D bg, Texture2D body, Texture2D wheel){
    
    //gambar background
    float posisi_bg_x = (car->position.x * 0.8f) - 1000.0f;

    Rectangle sourceBg = { 0, 0, (float)bg.width, (float)bg.height };
    Rectangle destBg = { posisi_bg_x, -800.0f, bg.width *3.0f, bg.height * 3.0f };
    Vector2 originBg = {0.0f, 0.0f};

    DrawTexturePro(bg, sourceBg, destBg, originBg, 0.0f, WHITE);
    
    // gambar background tanah
    for (int i = 0; i < terrain_count - 1; i++) {
        Vector2 p1 = terrain[i];
        Vector2 p2 = terrain[i + 1];

        int x1 = (int)p1.x;
        int y1 = (int)p1.y;
        int x2 = (int)p2.x;
        int y2 = (int)p2.y;
        int jarak_x = x2 - x1;

        if (jarak_x > 0){
            for (int x = x1; x <= x2; x++) {
                float rasio = (float)(x - x1) / jarak_x;
                int y_permukaan = (int)(y1 + rasio * (y2 - y1));

                BresenhamLine(x, y_permukaan + 4, x, 2000, BROWN);
            }
        }

        for (int tebal = 0; tebal < 5; tebal++) {
            BresenhamLine(x1, y1 + tebal, x2, y2 + tebal, GREEN);
        }
    }

}
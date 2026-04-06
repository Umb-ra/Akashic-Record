#include "terrain.h"

tree trees[TERRAIN_COUNT];
Vector2 terrain[TERRAIN_COUNT];
int obstacles[TERRAIN_COUNT];
int rock_radius[TERRAIN_COUNT];

static void CosineInterpolation(float t, float* out) {
    float ft = t * 3.14159265f; 
    float f = (1.0f - cosf(ft)) * 0.5f; 
    out[0] = f; 
}

void generateTerrain(void) {
   //panjang per segmen bukit
    int segmentLength = 20;
    int numPoints = (TERRAIN_COUNT / segmentLength) + 1;
    float keyHeights[numPoints];

    //loop untuk buat titik kunci bukit
    for (int i = 0; i < numPoints; i++) {
    keyHeights[i] = GetRandomValue(500, 800); 
    }

    int mud_counter = 0;
    int skip_counter = 0;

    //loop untuk interpolasi antar titik kunci
    for (int i = 0; i < TERRAIN_COUNT; i++) {
        int currentSeg = i / segmentLength;
        float startHeight = keyHeights[currentSeg];
        float endHeight = keyHeights[currentSeg + 1];
        float local_t = (float)(i % segmentLength) / segmentLength;
        float f;
        CosineInterpolation(local_t, &f);
        float endPointY = (int)(startHeight * (1 - f) + endHeight * f);
        terrain[i].x = i * 10.0f;
        terrain[i].y = endPointY;

        trees[i].x = terrain[i].x;
        trees[i].y = terrain[i].y;

        if (i > 10 && (rand() % 100) < 15) {
            trees[i].active = true;
        } else {
            trees[i].active = false;
        }

        obstacles[i] = OBS_NONE;
        
        if (i > 50) {
            // Jika sedang menggambar batu, lewati beberapa blok agar rintangan tidak menumpuk
            if (skip_counter > 0) {
                skip_counter--;
                continue;
            }
            // Jika sedang membuat kubangan lumpur, teruskan sampai counternya habis!
            if (mud_counter > 0) {
                obstacles[i] = OBS_MUD;
                mud_counter--;
                continue;
            }

            int rand_obs = GetRandomValue(0, 100);
            if (rand_obs < 3) {
                obstacles[i] = OBS_ROCK;
                rock_radius[i] = GetRandomValue(20, 50); // Radius batu acak (besar!)
                skip_counter = (rock_radius[i] / 10) + 1; 
            } else if (rand_obs < 8) {
                obstacles[i] = OBS_MUD;
                mud_counter = GetRandomValue(4, 10); // Panjang lumpur 40 - 100 piksel!
            }
        }

    }
}

void drawTerrain(bool is_debug, float cam_x, float screen_w) {
    float batas_kiri = cam_x - (screen_w / 2.0f) - 200.0f;
    float batas_kanan = cam_x + (screen_w / 2.0f) + 200.0f;

    for (int i = 0; i < TERRAIN_COUNT - 1; i++) {
        // CULLING: Skip yang di luar layar agar TIDAK LAG!
        if (terrain[i].x < batas_kiri || terrain[i].x > batas_kanan) continue; 

        if (is_debug == true) {
            Bres_ThickLine((int)terrain[i].x, (int)terrain[i].y, 
                           (int)terrain[i + 1].x, (int)terrain[i + 1].y, 
                           3, DARKGREEN);
        } else {
            // MODE GAME: MURNI BRESENHAM SOLID FILL!
            int x1 = (int)terrain[i].x;
            int y1 = (int)terrain[i].y;
            int x2 = (int)terrain[i + 1].x;
            int y2 = (int)terrain[i + 1].y;
            int jarak_x = x2 - x1;

            // Cari titik terendah dari segmen tanah ini
            int max_y = (y1 > y2) ? y1 : y2;

            // 1. FILL DAGING TANAH (Bresenham Vertikal Dinamis!)
            if (jarak_x > 0){
                for (int x = x1; x <= x2; x++) {
                    float rasio = (float)(x - x1) / jarak_x;
                    int y_permukaan = (int)(y1 + rasio * (y2 - y1));
                    BresenhamLine(x, y_permukaan + 4, x, max_y + 10, BROWN); 
                }
            }
            
            // 2. INTI BUMI (Tutup pakai kotak agar FPS stabil di 60)
            DrawRectangle(x1, max_y + 10, jarak_x + 2, 1000, BROWN);

            // 3. RUMPUT ATAS (Bresenham Horizontal Bertumpuk)
            for (int tebal = 0; tebal < 5; tebal++) {
                BresenhamLine(x1, y1 + tebal, x2, y2 + tebal, GREEN);
            }

            // --- GAMBAR RINTANGAN (BRESENHAM CACHE) ---
            if (obstacles[i] == OBS_MUD) {
                for (int m = 0; m < 8; m++) {
                    BresenhamLine(x1, (y1 - 2) + m, x2, (y2 - 2) + m, DARKBROWN);
                }
            } else if (obstacles[i] == OBS_ROCK) {
                int cx = (x1 + x2) / 2; 
                int cy = (y1 + y2) / 2; 
                int radius = rock_radius[i];
                float sudut_tanah = atan2f((float)(y2 - y1), (float)(x2 - x1));
                
                // OPTIMASI TRIGONOMETRI
                float cos_tanah = cosf(sudut_tanah);
                float sin_tanah = sinf(sudut_tanah);
                int langkah_maks = radius * 3; 
                
                // Isi daging batu
                for (int m = 0; m <= langkah_maks; m++) {
                    float sudut_lokal = (PI * m) / langkah_maks; 
                    float px = radius * cosf(sudut_lokal);
                    float py = -radius * sinf(sudut_lokal); 
                    
                    float rx = px * cos_tanah - py * sin_tanah;
                    float ry = px * sin_tanah + py * cos_tanah;
                    BresenhamLine(cx, cy, cx + (int)rx, cy + (int)ry, GRAY);
                }
                
                // Outline batu
                for (int m = 0; m < langkah_maks; m++) {
                    float a1 = (PI * m) / langkah_maks;
                    float a2 = (PI * (m + 1)) / langkah_maks;

                    float px1 = radius * cosf(a1); float py1 = -radius * sinf(a1);
                    float rx1 = px1 * cos_tanah - py1 * sin_tanah;
                    float ry1 = px1 * sin_tanah + py1 * cos_tanah;

                    float px2 = radius * cosf(a2); float py2 = -radius * sinf(a2);
                    float rx2 = px2 * cos_tanah - py2 * sin_tanah;
                    float ry2 = px2 * sin_tanah + py2 * cos_tanah;

                    BresenhamLine(cx + (int)rx1, cy + (int)ry1, cx + (int)rx2, cy + (int)ry2, BLACK);
                }
            }
        }
    }
}

float getTerrainHeight(float x_pos){
    float jarak_x = 10.0f;
    int index_kiri =  (int)(x_pos / jarak_x);
    if (index_kiri < 0) return terrain[0].y;
    if (index_kiri >= TERRAIN_COUNT - 1) return terrain[TERRAIN_COUNT - 1].y;

    float yKiri = terrain[index_kiri].y;
    float yKanan = terrain[index_kiri + 1].y;
    float xKiri = terrain[index_kiri].x;

    float t = (x_pos - xKiri) / jarak_x;
    float base_y = yKiri + (t * (yKanan - yKiri));
    float final_y = base_y;
    for (int j = -6; j <= 6; j++) {
        int check_idx = index_kiri + j;
        if (check_idx >= 0 && check_idx < TERRAIN_COUNT && obstacles[check_idx] == OBS_ROCK) {
            float cx = terrain[check_idx].x + (jarak_x / 2.0f); // Titik tengah batu
            float dist = fabs(x_pos - cx);
            
            // Jika ban menyentuh area batu, naikkan tinggi tanah menggunakan Rumus Pythagoras!
            if (dist < rock_radius[check_idx]) {
                float dy = sqrt((rock_radius[check_idx] * rock_radius[check_idx]) - (dist * dist));
                float rock_y = terrain[check_idx].y - dy;
                if (rock_y < final_y) {
                    final_y = rock_y; 
                }
            }
        }
}
    return final_y;
}

void drawTrees(bool is_debug, float cam_x, float screen_w){
    float batas_kiri = cam_x - (screen_w / 2.0f) - 200.0f;
    float batas_kanan = cam_x + (screen_w / 2.0f) + 200.0f;

    for (int i = 0; i < TERRAIN_COUNT; i++) {
        if (trees[i].x < batas_kiri || trees[i].x > batas_kanan) continue;

        if (trees[i].active) {
            int tinggi_pohon = 35;
            float dasar_y = trees[i].y - tinggi_pohon + 5;

            // ================= BATANG POHON =================
            if (is_debug == true) {
                Bres_ThickLine(trees[i].x, trees[i].y, trees[i].x, trees[i].y - tinggi_pohon, 4, BROWN);
            } else {
                // Tumpukan Bresenham Vertikal
                for (int w = 0; w < 4; w++) {
                    BresenhamLine(trees[i].x - 2 + w, trees[i].y, trees[i].x - 2 + w, trees[i].y - tinggi_pohon, DARKBROWN);
                }
            }
            
            // ================= DAUN POHON =================
            int jumlah_layer_daun = 3;
            int daun_size_awal = 18;
            int tinggi_daun = 25;
            int jarak_overlap = 17;

            for (int j = 0; j < jumlah_layer_daun; j++) {
                int ukuran_daun = daun_size_awal - (j * 4);
                float layer_y = dasar_y - (j * jarak_overlap);

                int puncak_x = trees[i].x;
                int puncak_y = (int)(layer_y - tinggi_daun);
                int kiri_x = (int)(trees[i].x - ukuran_daun);
                int kanan_x = (int)(trees[i].x + ukuran_daun);
                int dasar_daun_y = (int)layer_y;

                if (is_debug == true) {
                    BresenhamLine(kiri_x, dasar_daun_y, kanan_x, dasar_daun_y, DARKGREEN);
                    BresenhamLine(kiri_x, dasar_daun_y, puncak_x, puncak_y, DARKGREEN);
                    BresenhamLine(kanan_x, dasar_daun_y, puncak_x, puncak_y, DARKGREEN);
                } else {
                    // Isi Segitiga Daun MURNI menggunakan tumpukan Bresenham Horizontal (Scanline)
                    for (int y = puncak_y; y <= dasar_daun_y; y++) {
                        float t = (float)(y - puncak_y) / (dasar_daun_y - puncak_y);
                        int lx = puncak_x - (int)(t * (puncak_x - kiri_x));
                        int rx = puncak_x + (int)(t * (kanan_x - puncak_x));
                        BresenhamLine(lx, y, rx, y, DARKGREEN);
                    }
                }
            }
        }
    }
}

int getObstacleAt(float x_pos){
    float jarak_x = 10.0f;
    int index = (int)(x_pos / jarak_x);
    if (index < 0 || index >= TERRAIN_COUNT) return OBS_NONE;
    return obstacles[index];
}
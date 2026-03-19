#include "terrain.h"

tree trees[TERRAIN_COUNT];
Vector2 terrain[TERRAIN_COUNT];

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
    }
}

void drawTerrain(void) {
    for (int i = 0; i < TERRAIN_COUNT - 1; i++) {
        Bres_ThickLine((int)terrain[i].x, (int)terrain[i].y, 
                       (int)terrain[i + 1].x, (int)terrain[i + 1].y, 
                       3, DARKGREEN);
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
    return yKiri + (t * (yKanan - yKiri));

}

void drawTrees(){
    for (int i = 0; i < TERRAIN_COUNT; i++) {
        if (trees[i].active) {
            int tinggi_pohon = 30;
            BresenhamLine(trees[i].x, trees[i].y, trees[i].x, trees[i].y - tinggi_pohon, BROWN);

            int daun_size = 15;
            tree Titik_puncak = {trees[i].x, trees[i].y - tinggi_pohon - 20};
            tree Titik_kiri = {trees[i].x - daun_size, trees[i].y - tinggi_pohon};
            tree Titik_kanan = {trees[i].x + daun_size, trees[i].y - tinggi_pohon};

            BresenhamLine(Titik_kiri.x, Titik_kiri.y, Titik_kanan.x, Titik_kanan.y, GREEN);
            BresenhamLine(Titik_kiri.x, Titik_kiri.y, Titik_puncak.x, Titik_puncak.y, GREEN);
            BresenhamLine(Titik_kanan.x, Titik_kanan.y, Titik_puncak.x, Titik_puncak.y, GREEN);      
        }
    }
}
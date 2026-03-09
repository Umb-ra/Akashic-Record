#include "src/ui/cartesian.h"
#include "coords.h"
#include "screen_type.h"
#include <stdio.h>

void DrawCartesianGrid(void (*lineFunc)(int,int,int,int,Color)) {
    for (int i = -7; i <= 7; i++) {
        lineFunc(CS_X(i), CS_Y(-8), CS_X(i), CS_Y(8), (Color){40,40,70,255});
        lineFunc(CS_X(-8), CS_Y(i), CS_X(8), CS_Y(i), (Color){40,40,70,255});
    }

    lineFunc(CS_X(-8), CS_Y(0), CS_X(8), CS_Y(0), RAYWHITE);
    lineFunc(CS_X(0), CS_Y(-8), CS_X(0), CS_Y(8), RAYWHITE);

    lineFunc(CS_X(8), CS_Y(0), CS_X(8)-10, CS_Y(0)-6, RAYWHITE);
    lineFunc(CS_X(8), CS_Y(0), CS_X(8)-10, CS_Y(0)+6, RAYWHITE);
    lineFunc(CS_X(0), CS_Y(8), CS_X(0)-6, CS_Y(8)+10, RAYWHITE);
    lineFunc(CS_X(0), CS_Y(8), CS_X(0)+6, CS_Y(8)+10, RAYWHITE);

    DrawText("X",  CS_X(8)+8,  CS_Y(0)-9, 18, RAYWHITE);
    DrawText("Y",  CS_X(0)+8,  CS_Y(8)-22, 18, RAYWHITE);
    DrawText("(0,0)", CS_X(0)+5, CS_Y(0)+5, 11, (Color){160,160,160,255});

    for (int i = -7; i <= 7; i++) {
        if (i == 0) continue;
        lineFunc(CS_X(i), CS_Y(0)-4, CS_X(i), CS_Y(0)+4, RAYWHITE);
        lineFunc(CS_X(0)-4, CS_Y(i), CS_X(0)+4, CS_Y(i), RAYWHITE);

        char lbl[8];
        sprintf(lbl, "%d", i);
        DrawText(lbl, CS_X(i)-5, CS_Y(0)+8, 11, LIGHTGRAY);
        sprintf(lbl, "%d", i);
        DrawText(lbl, CS_X(0)+6, CS_Y(i)-6, 11, LIGHTGRAY);
    }
}

void DrawCoordInfo(const char *algoName) {
    int px = SCREEN_W - 270, py = SCREEN_H - 148;
    DrawRectangle(px-8, py-8, 262, 138, (Color){0,0,0,190});
    DrawRectangle(px-8, py-8, 262, 18, (Color){30,30,70,220});
    DrawText("Penyesuaian Sistem Koordinat", px, py-5, 11, (Color){180,200,255,255});
    DrawText("Layar (screen):", px, py+16, 11, (Color){255,180,80,255});
    DrawText("  (0,0) = pojok KIRI ATAS", px, py+30, 11, LIGHTGRAY);
    DrawText("  Y layar bertambah ke BAWAH", px, py+44, 11, LIGHTGRAY);
    DrawText("Kartesian:", px, py+62, 11, (Color){80,220,120,255});
    DrawText("  (0,0) = TENGAH diagram", px, py+76, 11, LIGHTGRAY);
    DrawText("  Y kartesian bertambah ke ATAS", px, py+90, 11, LIGHTGRAY);
    DrawText("Rumus konversi:", px, py+108, 11, (Color){255,220,80,255});
    DrawText("  sx = originX + cx * tick", px, py+120, 11, (Color){255,255,120,255});
    DrawText("  sy = originY - cy * tick", px, py+132, 11, (Color){255,120,120,255});
    (void)algoName;
}

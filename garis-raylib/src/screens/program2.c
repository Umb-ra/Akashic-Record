#include "src/screens/program2.h"
#include "src/algo/dda.h"
#include "src/ui/back_button.h"
#include "src/ui/primitives.h"
#include "screen_type.h"
#include "raylib.h"

void DrawProgram2(void) {
    ClearBackground((Color){12,12,28,255});
    DrawRectangle(0, 0, SCREEN_W, 56, (Color){0,0,0,210});
    DrawBackButton();
    DrawText("PROGRAM 2 - Macam-macam Style Garis (DDA)", 135, 10, 18, WHITE);
    DrawText("Semua segmen dibangun dari DDA: normal, putus-putus, tebal, dash-dot, diagonal", 135, 33, 12, LIGHTGRAY);

    int startX = 70, endX = SCREEN_W-70;
    int y = 100, sp = 76;

    DrawText("1. Garis Normal", startX, y-22, 14, LIGHTGRAY);
    DDALine(startX, y, endX, y, GREEN);
    DrawDot(startX,y,3,GREEN); DrawDot(endX,y,3,GREEN);
    DrawText("steps=max(|dx|,|dy|),  xInc=dx/steps,  yInc=dy/steps", startX, y+8, 11, (Color){100,200,100,255});

    y += sp;
    DrawText("2. Putus-putus Panjang  (dash 20px, gap 12px)", startX, y-22, 14, LIGHTGRAY);
    DDA_DashedLine(startX, y, endX, y, 20, 12, ORANGE);
    DrawText("Segmen DDA aktif 20px, jeda 12px, bergantian", startX, y+8, 11, (Color){200,140,60,255});

    y += sp;
    DrawText("3. Putus-putus Rapat  (dash 6px, gap 6px)", startX, y-22, 14, LIGHTGRAY);
    DDA_DashedLine(startX, y, endX, y, 6, 6, YELLOW);
    DrawText("Segmen DDA aktif 6px, jeda 6px", startX, y+8, 11, (Color){200,200,60,255});

    y += sp;
    DrawText("4. Garis Tebal  (ketebalan 8px)", startX, y-22, 14, LIGHTGRAY);
    DDA_ThickLine(startX, y, endX, y, 8, RED);
    DrawText("DDA berlapis: offset vektor tegak lurus ±4px", startX, y+8, 11, (Color){220,80,80,255});

    y += sp;
    DrawText("5. Garis Sangat Tebal  (ketebalan 14px)", startX, y-22, 14, LIGHTGRAY);
    DDA_ThickLine(startX, y, endX, y, 14, SKYBLUE);
    DrawText("DDA berlapis: offset vektor tegak lurus ±7px", startX, y+8, 11, (Color){80,160,220,255});

    y += sp;
    DrawText("6. Garis Dash-Dot", startX, y-22, 14, LIGHTGRAY);
    DDA_DashDotLine(startX, y, endX, y, VIOLET);
    DrawText("Pola: garis(18) - gap(5) - titik(5) - gap(5)", startX, y+8, 11, (Color){160,80,220,255});

    y += sp;
    DrawText("7. Garis Diagonal Tebal  (ketebalan 6px)", startX, y-22, 14, LIGHTGRAY);
    DDA_ThickLine(startX, y+25, endX, y-25, 6, PINK);
    DrawText("Diagonal: DDA berlapis, arah serong", startX, y+10, 11, (Color){220,100,160,255});

    DrawText("[ESC/BACKSPACE] Kembali  |  Klik BACK", 12, SCREEN_H-22, 13, DARKGRAY);
}

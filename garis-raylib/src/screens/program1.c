#include "src/screens/program1.h"
#include "src/algo/dda.h"
#include "src/ui/back_button.h"
#include "src/ui/cartesian.h"
#include "src/ui/primitives.h"
#include "coords.h"
#include "screen_type.h"
#include "raylib.h"

void DrawProgram1(void) {
    G_OriginX  = SCREEN_W / 2;
    G_OriginY  = SCREEN_H / 2 + 30;
    G_TickStep = 38;

    ClearBackground((Color){12,12,28,255});
    DrawCartesianGrid(DDALine);

    struct { int cx1,cy1,cx2,cy2; Color c; const char *lbl; } lines[] = {
        {-6,-4,  6, 5, RED,     "Garis 1: (-6,-4)->(6,5)"},
        {-5, 5,  5,-4, SKYBLUE, "Garis 2: (-5,5)->(5,-4)"},
        {-7, 0,  7, 3, YELLOW,  "Garis 3: (-7,0)->(7,3)"},
        { 3,-6,  3, 6, MAGENTA, "Garis 4: (3,-6)->(3,6)"},
    };
    for (int i = 0; i < 4; i++) {
        int sx1 = CS_X(lines[i].cx1);
        int sy1 = CS_Y(lines[i].cy1);
        int sx2 = CS_X(lines[i].cx2);
        int sy2 = CS_Y(lines[i].cy2);
        DDALine(sx1, sy1, sx2, sy2, lines[i].c);
        DrawDot(sx1, sy1, 3, lines[i].c);
        DrawDot(sx2, sy2, 3, lines[i].c);
    }

    DrawRectangle(0, 0, SCREEN_W, 56, (Color){0,0,0,210});
    DrawBackButton();
    DrawText("PROGRAM 1 - Diagram Kartesian (Algoritma DDA)", 135, 10, 18, WHITE);
    DrawText("steps=max(|dx|,|dy|)  xInc=dx/steps  yInc=dy/steps  plot(round(x),round(y))", 135, 33, 12, LIGHTGRAY);

    DrawRectangle(SCREEN_W-232, 60, 225, 115, (Color){0,0,0,185});
    DrawText("LEGENDA (koordinat Kartesian):", SCREEN_W-225, 66, 12, WHITE);
    for (int i = 0; i < 4; i++) {
        int ly = 84 + i*22;
        DDALine(SCREEN_W-222, ly, SCREEN_W-188, ly, lines[i].c);
        DrawText(lines[i].lbl, SCREEN_W-184, ly-6, 11, lines[i].c);
    }

    DrawCoordInfo("DDA");
    DrawText("[ESC/BACKSPACE] Kembali  |  Klik BACK", 12, SCREEN_H-22, 13, DARKGRAY);
}

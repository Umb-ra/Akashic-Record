#include "src/screens/program3.h"
#include "src/algo/bresenham.h"
#include "src/ui/back_button.h"
#include "src/ui/cartesian.h"
#include "src/ui/primitives.h"
#include "coords.h"
#include "screen_type.h"
#include "raylib.h"

void DrawProgram3(void) {
    G_OriginX  = SCREEN_W / 2;
    G_OriginY  = SCREEN_H / 2 + 30;
    G_TickStep = 38;

    ClearBackground((Color){12,18,12,255});
    DrawCartesianGrid(BresenhamLine);

    struct { int cx1,cy1,cx2,cy2; Color c; const char *lbl; } lines[] = {
        {-7,-2,  7, 5, (Color){255,120, 80,255}, "Garis 1: (-7,-2)->(7,5)"},
        {-6, 6,  6,-5, (Color){ 80,220,255,255}, "Garis 2: (-6,6)->(6,-5)"},
        {-5, 1,  5, 1, (Color){255,230, 60,255}, "Garis 3: (-5,1)->(5,1) horizontal"},
        { 2,-7,  2, 7, (Color){180,255,100,255}, "Garis 4: (2,-7)->(2,7) vertikal"},
        {-6,-5,  5, 5, (Color){255,120,255,255}, "Garis 5: (-6,-5)->(5,5) diagonal"},
    };
    for (int i = 0; i < 5; i++) {
        int sx1 = CS_X(lines[i].cx1);
        int sy1 = CS_Y(lines[i].cy1);
        int sx2 = CS_X(lines[i].cx2);
        int sy2 = CS_Y(lines[i].cy2);
        BresenhamLine(sx1, sy1, sx2, sy2, lines[i].c);
        DrawDot(sx1, sy1, 3, lines[i].c);
        DrawDot(sx2, sy2, 3, lines[i].c);
    }

    DrawRectangle(0, 0, SCREEN_W, 56, (Color){0,0,0,210});
    DrawBackButton();
    DrawText("PROGRAM 3 - Diagram Kartesian (Algoritma Bresenham)", 135, 10, 18, WHITE);
    DrawText("err=dx-dy  e2=2*err  if(e2>-dy):err-=dy,x+=sx  if(e2<dx):err+=dx,y+=sy", 135, 33, 12, LIGHTGRAY);

    DrawRectangle(SCREEN_W-252, 60, 244, 138, (Color){0,0,0,185});
    DrawText("LEGENDA (koordinat Kartesian):", SCREEN_W-245, 66, 12, WHITE);
    for (int i = 0; i < 5; i++) {
        int ly = 84 + i*22;
        BresenhamLine(SCREEN_W-242, ly, SCREEN_W-208, ly, lines[i].c);
        DrawText(lines[i].lbl, SCREEN_W-204, ly-6, 11, lines[i].c);
    }

    DrawCoordInfo("Bresenham");
    DrawText("[ESC/BACKSPACE] Kembali  |  Klik BACK", 12, SCREEN_H-22, 13, DARKGRAY);
}

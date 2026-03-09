#include "src/screens/menu.h"
#include "src/algo/dda.h"
#include "src/algo/bresenham.h"
#include "coords.h"
#include "screen_type.h"
#include "raylib.h"

void DrawMenu(void) {
    G_OriginX = 0; G_OriginY = 0; G_TickStep = 1;

    ClearBackground((Color){8,8,20,255});
    DrawRectangle(0, 0, SCREEN_W, 80, (Color){20,20,50,255});
    DrawText("Aplikasi Grafika Komputer", SCREEN_W/2-210, 12, 30, WHITE);
    DrawText("Algoritma DDA & Bresenham  |  Raylib + C", SCREEN_W/2-200, 48, 18, LIGHTGRAY);
    DDALine(0, 80, SCREEN_W, 80, (Color){60,80,160,255});

    int cW = 450, cH = 155;
    int c1 = SCREEN_W/2 - cW - 15;
    int c2 = SCREEN_W/2 + 15;
    int r1 = 100, r2 = 268;

    DrawRectangleRounded((Rectangle){c1,r1,cW,cH}, 0.1f, 8, (Color){15,40,70,255});
    DrawRectangleRoundedLines((Rectangle){c1,r1,cW,cH}, 0.1f, 8, SKYBLUE);
    DrawText("PROGRAM 1", c1+18, r1+14, 22, SKYBLUE);
    DrawText("Diagram Kartesian - DDA", c1+18, r1+42, 16, WHITE);
    DDALine(c1+18, r1+66, c1+200, r1+66, RED);
    DDALine(c1+18, r1+80, c1+200, r1+80, YELLOW);
    DDALine(c1+18, r1+94, c1+180, r1+74, SKYBLUE);
    DrawText("Garis DDA pada bidang kartesian", c1+18, r1+112, 13, LIGHTGRAY);
    DrawText("[Tekan 1]", c1+cW-100, r1+cH-28, 16, SKYBLUE);

    DrawRectangleRounded((Rectangle){c2,r1,cW,cH}, 0.1f, 8, (Color){50,15,60,255});
    DrawRectangleRoundedLines((Rectangle){c2,r1,cW,cH}, 0.1f, 8, VIOLET);
    DrawText("PROGRAM 2", c2+18, r1+14, 22, VIOLET);
    DrawText("Style Garis - DDA", c2+18, r1+42, 16, WHITE);
    DDA_DashedLine(c2+18, r1+66, c2+200, r1+66, 12, 8, ORANGE);
    DDA_ThickLine(c2+18, r1+84, c2+200, r1+84, 5, PINK);
    DDA_DashDotLine(c2+18, r1+102, c2+200, r1+102, YELLOW);
    DrawText("Normal, dash, tebal, dash-dot  [DDA]", c2+18, r1+120, 13, LIGHTGRAY);
    DrawText("[Tekan 2]", c2+cW-100, r1+cH-28, 16, VIOLET);

    DrawRectangleRounded((Rectangle){c1,r2,cW,cH}, 0.1f, 8, (Color){15,50,25,255});
    DrawRectangleRoundedLines((Rectangle){c1,r2,cW,cH}, 0.1f, 8, GREEN);
    DrawText("PROGRAM 3", c1+18, r2+14, 22, GREEN);
    DrawText("Diagram Kartesian - Bresenham", c1+18, r2+42, 16, WHITE);
    BresenhamLine(c1+18, r2+80, c1+200, r2+64, (Color){255,120,80,255});
    BresenhamLine(c1+18, r2+64, c1+200, r2+80, (Color){80,220,255,255});
    BresenhamLine(c1+18, r2+93, c1+200, r2+93, (Color){180,255,100,255});
    DrawText("Garis Bresenham pada bidang kartesian", c1+18, r2+110, 13, LIGHTGRAY);
    DrawText("[Tekan 3]", c1+cW-100, r2+cH-28, 16, GREEN);

    DrawRectangleRounded((Rectangle){c2,r2,cW,cH}, 0.1f, 8, (Color){50,30,10,255});
    DrawRectangleRoundedLines((Rectangle){c2,r2,cW,cH}, 0.1f, 8, ORANGE);
    DrawText("PROGRAM 4", c2+18, r2+14, 22, ORANGE);
    DrawText("Style Garis - Bresenham", c2+18, r2+42, 16, WHITE);
    Bres_DashedLine(c2+18, r2+66, c2+200, r2+66, 12, 8, ORANGE);
    Bres_ThickLine(c2+18, r2+84, c2+200, r2+84, 5, RED);
    Bres_DashDotLine(c2+18, r2+102, c2+200, r2+102, YELLOW);
    DrawText("Normal, dash, tebal, dash-dot  [Bresenham]", c2+18, r2+120, 13, LIGHTGRAY);
    DrawText("[Tekan 4]", c2+cW-100, r2+cH-28, 16, ORANGE);

    int btnY = r2 + cH + 14; 
    int umbraBtnX = SCREEN_W/2 - 170; 
    int abBtnX = SCREEN_W/2 + 10;     
    Vector2 mouse = GetMousePosition();

    int umbraHover = CheckCollisionPointRec(mouse, (Rectangle){umbraBtnX, btnY, 160, 36});
    DrawRectangleRounded((Rectangle){umbraBtnX, btnY, 160, 36}, 0.3f, 6,
                         umbraHover ? (Color){100,50,150,230} : (Color){50,20,80,220});
    DrawRectangleRoundedLines((Rectangle){umbraBtnX, btnY, 160, 36}, 0.3f, 6, umbraHover ? WHITE : VIOLET);
    DrawText("[ 5 ] Nick", umbraBtnX + 22, btnY + 10, 16, WHITE);

    int abHover = CheckCollisionPointRec(mouse, (Rectangle){abBtnX, btnY, 160, 36});
    DrawRectangleRounded((Rectangle){abBtnX, btnY, 160, 36}, 0.3f, 6,
                         abHover ? (Color){60,100,180,230} : (Color){25,35,70,220});
    DrawRectangleRoundedLines((Rectangle){abBtnX, btnY, 160, 36}, 0.3f, 6, abHover ? WHITE : (Color){80,110,200,255});
    DrawText("[ A ] About", abBtnX + 22, btnY + 10, 16, WHITE);

    DrawRectangle(0, SCREEN_H-50, SCREEN_W, 50, (Color){15,15,35,255});
    DDALine(0, SCREEN_H-50, SCREEN_W, SCREEN_H-50, (Color){60,80,160,255});
    DrawText("[1] P1  [2] P2  [3] P3  [4] P4  [5] Nick  [A] About  |  [ESC] Keluar",
        SCREEN_W/2-280, SCREEN_H-33, 16, GRAY);
}

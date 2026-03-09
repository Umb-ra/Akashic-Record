#include "src/screens/about.h"
#include "src/algo/dda.h"
#include "src/algo/bresenham.h"
#include "src/ui/back_button.h"
#include "screen_type.h"
#include "raylib.h"
#include <math.h>

void DrawAbout(void) {
    ClearBackground((Color){8, 8, 20, 255});

    DrawRectangle(0, 0, SCREEN_W, 56, (Color){0, 0, 0, 210});
    DrawBackButton();
    DrawText("ABOUT - Informasi Pembuat", 135, 10, 20, WHITE);
    DDALine(0, 56, SCREEN_W, 56, (Color){60, 80, 160, 255});

    int cardX = SCREEN_W/2 - 280, cardY = 90, cardW = 560, cardH = 340;
    DrawRectangleRounded((Rectangle){cardX, cardY, cardW, cardH}, 0.08f, 8, (Color){18, 22, 50, 255});
    DrawRectangleRoundedLines((Rectangle){cardX, cardY, cardW, cardH}, 0.08f, 8, (Color){80, 120, 220, 255});

    int avX = SCREEN_W/2, avY = cardY + 90;
    int avR = 54;
    for (int deg = 0; deg < 360; deg += 2) {
        float a1 = deg * 3.14159f / 180.0f;
        float a2 = (deg+2) * 3.14159f / 180.0f;
        DDALine((int)(avX + avR*cosf(a1)), (int)(avY + avR*sinf(a1)),
                (int)(avX + avR*cosf(a2)), (int)(avY + avR*sinf(a2)),
                (Color){80, 140, 230, 255});
    }
    for (int dy2 = -avR+2; dy2 <= avR-2; dy2 += 2) {
        int hw = (int)sqrtf((float)(avR*avR - dy2*dy2));
        DDALine(avX - hw, avY + dy2, avX + hw, avY + dy2, (Color){25, 40, 90, 255});
    }
    int s = 35;
    Color cLogo = VIOLET;
    DDALine(avX - 14, avY - 24, avX - 14, avY + 24, cLogo); 
    DDALine(avX - 14, avY + 24, avX - 2, avY + 24, cLogo);  
    DDALine(avX - 2, avY + 24, avX - 2, avY + 4, cLogo);    
    DDALine(avX - 2, avY + 4, avX + 10, avY + 4, cLogo);    
    DDALine(avX + 10, avY + 4, avX + 10, avY - 4, cLogo);   
    DDALine(avX + 10, avY - 4, avX - 2, avY - 4, cLogo);    
    DDALine(avX - 2, avY - 4, avX - 2, avY - 14, cLogo);    
    DDALine(avX - 2, avY - 14, avX + 16, avY - 14, cLogo);  
    DDALine(avX + 16, avY - 14, avX + 16, avY - 24, cLogo); 
    DDALine(avX + 16, avY - 24, avX - 14, avY - 24, cLogo);
    int textX = SCREEN_W/2 - 100;

    const char *nameText = "Fariz Dhifa Fakhriza";
    int nameW = MeasureText(nameText, 32);
    DrawText(nameText, SCREEN_W/2 - nameW/2, avY + avR + 18, 32, WHITE);

    const char *idText = "NIM: 241524040";
    int idW = MeasureText(idText, 20);
    DrawText(idText, SCREEN_W/2 - idW/2, avY + avR + 58, 20, (Color){160, 190, 255, 255});

    DDALine(cardX + 40, avY + avR + 88, cardX + cardW - 40, avY + avR + 88, (Color){60, 80, 160, 255});

    DrawText("Mata Kuliah : Grafika Komputer", cardX + 40, avY + avR + 102, 16, LIGHTGRAY);
    DrawText("Topik       : Algoritma DDA & Bresenham", cardX + 40, avY + avR + 124, 16, LIGHTGRAY);
    DrawText("Library     : Raylib 5.5  |  Bahasa: C", cardX + 40, avY + avR + 146, 16, LIGHTGRAY);

    int sumY = cardY + cardH + 20;
    int sumW = 220, sumH = 64, sumGap = 14;
    int sumStartX = SCREEN_W/2 - (4*sumW + 3*sumGap)/2;

    const char *pLabels[] = {"Program 1","Program 2","Program 3","Program 4"};
    const char *pDesc[]   = {"DDA Kartesian","DDA Style Garis","Bres Kartesian","Bres Style Garis"};
    Color pColors[] = {SKYBLUE, VIOLET, GREEN, ORANGE};

    for (int i = 0; i < 4; i++) {
        int bx = sumStartX + i*(sumW + sumGap);
        DrawRectangleRounded((Rectangle){bx, sumY, sumW, sumH}, 0.15f, 6, (Color){20,20,45,255});
        DrawRectangleRoundedLines((Rectangle){bx, sumY, sumW, sumH}, 0.15f, 6, pColors[i]);
        DrawText(pLabels[i], bx + 12, sumY + 10, 15, pColors[i]);
        DrawText(pDesc[i],   bx + 12, sumY + 32, 13, LIGHTGRAY);
    }

    int decorY = sumY + sumH + 30;
    DrawText("Dibuat dengan :", SCREEN_W/2 - 140, decorY, 14, (Color){80,80,120,255});
    DDA_DashedLine(SCREEN_W/2 - 140, decorY + 24, SCREEN_W/2, decorY + 24, 14, 8, (Color){80,140,200,200});
    DrawText("DDA", SCREEN_W/2 + 8, decorY + 16, 13, (Color){80,140,200,255});
    Bres_DashedLine(SCREEN_W/2 + 50, decorY + 24, SCREEN_W/2 + 200, decorY + 24, 14, 8, (Color){80,200,140,200});
    DrawText("Bresenham", SCREEN_W/2 + 210, decorY + 16, 13, (Color){80,200,140,255});

    DrawText("[ESC/BACKSPACE] Kembali  |  Klik BACK", 12, SCREEN_H-22, 13, DARKGRAY);
}

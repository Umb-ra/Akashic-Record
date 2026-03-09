#include "src/ui/back_button.h"
#include "raylib.h"

static Rectangle backBtn = { 12, 12, 110, 34 };

int BackButtonPressed(void) {
    Vector2 mouse = GetMousePosition();
    int hover = CheckCollisionPointRec(mouse, backBtn);
    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return 1;
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE)) return 1;
    return 0;
}

void DrawBackButton(void) {
    Vector2 mouse = GetMousePosition();
    int hover = CheckCollisionPointRec(mouse, backBtn);
    Color bg  = hover ? (Color){80,120,200,230} : (Color){30,40,80,220};
    Color brd = hover ? WHITE : (Color){100,140,220,255};
    DrawRectangleRounded(backBtn, 0.3f, 6, bg);
    DrawRectangleRoundedLines(backBtn, 0.3f, 6, brd);
    DrawText("< BACK", (int)backBtn.x+10, (int)backBtn.y+9, 16, WHITE);
}

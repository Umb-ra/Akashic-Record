#include "src/ui/primitives.h"

void DrawDot(int cx, int cy, int size, Color color) {
    for (int oy = -size; oy <= size; oy++)
        for (int ox = -size; ox <= size; ox++)
            DrawPixel(cx + ox, cy + oy, color);
}

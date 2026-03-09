#ifndef DDA_H
#define DDA_H

#include "raylib.h"

void DDALine(int x1, int y1, int x2, int y2, Color color);
void DDA_DashedLine(int x1, int y1, int x2, int y2, int dashLen, int gapLen, Color color);
void DDA_ThickLine(int x1, int y1, int x2, int y2, int thick, Color color);
void DDA_DashDotLine(int x1, int y1, int x2, int y2, Color color);

#endif

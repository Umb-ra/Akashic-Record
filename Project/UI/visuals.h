#ifndef visuals_h
#define visuals_h

#include <raylib.h>
#include "../physics/physics.h"
#include "../algo/bresenham.h"

void DrawGameVisuals(Car *car, Vector2 *terrain, int terrain_count, Texture2D bg, Texture2D body, Texture2D wheel);
#endif
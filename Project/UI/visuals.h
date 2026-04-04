#ifndef visuals_h
#define visuals_h

#include <raylib.h>
#include "../physics/physics.h"
#include "../algo/bresenham.h"
#include "../Car/car.h"

void DrawGameVisuals(Car *car, Texture2D body, Texture2D wheel);
#endif
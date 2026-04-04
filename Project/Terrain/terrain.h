#ifndef TERRAIN_H
#define TERRAIN_H

#include <raylib.h>
#include <math.h>
#include "../algo/bresenham.h"
#define TERRAIN_COUNT 2000
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    float x;
    float y;
    bool active;
} tree;

extern Vector2 terrain[TERRAIN_COUNT];
extern tree trees[TERRAIN_COUNT];

void generateTerrain(void);
void drawTerrain(bool is_debug);
float getTerrainHeight(float x_pos);
void drawTrees(bool is_debug);

#endif
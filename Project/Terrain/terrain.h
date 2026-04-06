#ifndef TERRAIN_H
#define TERRAIN_H

#define OBS_NONE 0
#define OBS_MUD 1
#define OBS_ROCK 2

#include <raylib.h>
#include <math.h>
#include "../algo/bresenham.h"
#define TERRAIN_COUNT 500
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
extern int obstacles[TERRAIN_COUNT];
extern int rock_radius[TERRAIN_COUNT];

void generateTerrain(void);
void drawTerrain(bool is_debug, float cam_x, float screen_w);
float getTerrainHeight(float x_pos);
void drawTrees(bool is_debug, float cam_x, float screen_w);
int getObstacleAt(float x_pos);


#endif
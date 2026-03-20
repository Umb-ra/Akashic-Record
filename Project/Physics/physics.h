#ifndef PHYSICS_H
#define PHYSICS_H
#include "../Car/car.h"
#include "../Terrain/terrain.h"
#include <stdio.h> 
#include <math.h>

void UpdatePhysics(Car *car, float dt);
void updateSmoke(float dt);
void drawSmoke(void);

#endif
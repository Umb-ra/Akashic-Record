#ifndef CAR_H
#define CAR_H

#include <raylib.h>
#include "../algo/bresenham.h"
#include <math.h>
#define CAR_VERTEX_COUNT 6 

typedef struct Car {
    Vector2 position;
    Vector2 velocity;
    float rotation;   
    Vector2 vertices[CAR_VERTEX_COUNT]; 
    Vector2 wheelPositions[2]; 
    float wheelRadius;
    float wheelRotation;       
    
} Car;
                 
void InitCar(Car *car, float startX, float startY) ;
void DrawCar(Car *car);

#endif
#ifndef CARTESIAN_H
#define CARTESIAN_H

#include "raylib.h"

void DrawCartesianGrid(void (*lineFunc)(int,int,int,int,Color));
void DrawCoordInfo(const char *algoName);

#endif

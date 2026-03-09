#include "coords.h"

int G_OriginX  = 0;
int G_OriginY  = 0;
int G_TickStep = 1;

int CS_X(int cart_x) { return G_OriginX + cart_x * G_TickStep; }
int CS_Y(int cart_y) { return G_OriginY - cart_y * G_TickStep; }

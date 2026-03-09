#ifndef COORDS_H
#define COORDS_H

/*
 * Konversi koordinat Kartesian <-> Layar
 *
 * Layar  : (0,0) pojok KIRI ATAS, Y bertambah ke BAWAH
 * Kartesian : (0,0) TENGAH layar, Y bertambah ke ATAS
 *
 * Rumus:
 *   screen_x = G_OriginX + cart_x * G_TickStep
 *   screen_y = G_OriginY - cart_y * G_TickStep  <- MINUS: Y terbalik
 */

extern int G_OriginX;
extern int G_OriginY;
extern int G_TickStep;

int CS_X(int cart_x);
int CS_Y(int cart_y);

#endif

#include "program5.h"
#include "src/ui/back_button.h"
#include "src/algo/bresenham.h"
#include "screen_type.h"
#include "raylib.h"

void DrawProgram5(void) {
    ClearBackground((Color){15, 20, 30, 255}); 
    DrawBackButton();

    int w = 40;    
    int h = 80;     
    int gap = 20;    
    Color c = SKYBLUE; 
    int totalLebar = (5 * w) + (4 * gap);
    int x = (SCREEN_W / 2) - (totalLebar / 2);
    int y = (SCREEN_H / 2) - (h / 2);

    // MENGGAMBAR HURUF F 
    BresenhamLine(x, y, x, y + h, c);             
    BresenhamLine(x, y, x + w, y, c);            
    BresenhamLine(x, y + h/2, x + w - 10, y + h/2, c); 
    
    x = x + w + gap; //Geser X ke kanan untuk huruf berikutnya

    // MENGGAMBAR HURUF A 
    BresenhamLine(x, y + h, x, y, c);            
    BresenhamLine(x, y, x + w, y, c);             
    BresenhamLine(x + w, y, x + w, y + h, c);     
    BresenhamLine(x, y + h/2, x + w, y + h/2, c); 
    
    x = x + w + gap; 

    // MENGGAMBAR HURUF R
    BresenhamLine(x, y, x, y + h, c);
    BresenhamLine(x, y, x + w, y, c);
    BresenhamLine(x + w, y, x + w, y + h/2, c);
    BresenhamLine(x, y + h/2, x + w, y + h/2, c);
    BresenhamLine(x, y + h/2, x + w, y + h, c);
    
    x = x + w + gap; 

    // MENGGAMBAR HURUF I
    BresenhamLine(x + w/2, y, x + w/2, y + h, c);
    BresenhamLine(x, y, x + w, y, c);
    BresenhamLine(x, y + h, x + w, y + h, c);
    
    x = x + w + gap; 

    // MENGGAMBAR HURUF Z 
    BresenhamLine(x, y, x + w, y, c);
    BresenhamLine(x + w, y, x, y + h, c);
    BresenhamLine(x, y + h, x + w, y + h, c);
}
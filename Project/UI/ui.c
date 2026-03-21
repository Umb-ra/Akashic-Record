#include <stdbool.h>
#include <raylib.h>
#include "ui.h"

bool DebugMode = true;

void toggleDraw9(){
    if (IsKeyPressed(KEY_TAB)) {
    DebugMode = !DebugMode;
}
} 
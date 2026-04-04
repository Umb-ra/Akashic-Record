@echo off
gcc game.c algo/bresenham.c Terrain/terrain.c Car/car.c Physics/physics.c UI/visuals.c -o game.exe -lraylib -lopengl32 -lgdi32 -lwinmm
if %errorlevel% neq 0 exit /b %errorlevel%
game.exe
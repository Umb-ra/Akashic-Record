#include "visuals.h"

void DrawGameVisuals(Car *car, Texture2D body, Texture2D wheel){
    float cosR = cosf(car->rotation);
    float sinR = sinf(car->rotation);

    // LAYER RODA
    for (int i = 0; i < 2; i++) {
        float loc_roda_x = car->wheelPositions[i].x;
        float loc_roda_y = car->wheelPositions[i].y;

        float pusat_roda_x = car->position.x + loc_roda_x * cosR - loc_roda_y * sinR;
        float pusat_roda_y = car->position.y + loc_roda_x * sinR + loc_roda_y * cosR;

        Rectangle source_wheel = {0.0f, 0.0f, (float)wheel.width, (float)wheel.height};
        Rectangle dest_wheel = { pusat_roda_x, pusat_roda_y, car->wheelRadius * 2.0f, car->wheelRadius * 2.0f };
        Vector2 origin_wheel = { car->wheelRadius, car->wheelRadius };
        DrawTexturePro(wheel, source_wheel, dest_wheel, origin_wheel, car->wheelRotation * RAD2DEG, WHITE);    
    }

    // LAYER BODI MOBIL
    Rectangle source_body = {0.0f, 0.0f, (float)body.width, (float)body.height};
    Rectangle dest_body = { car->position.x, car->position.y, car->width, car->height };
    Vector2 origin_body = { car->width / 2.0f, car->height / 2.0f };
    DrawTexturePro(body, source_body, dest_body, origin_body, car->rotation * RAD2DEG, WHITE);
}
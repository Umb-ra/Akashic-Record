#include "physics.h"

#define TENAGA_MOBIL 500.0f
#define GRAVITY 700.0f 

void UpdatePhysics(Car *car, float dt) {
    car->velocity.y = car->velocity.y + (GRAVITY * dt);
    car->position.y = car->position.y + (car->velocity.y * dt);
    
    printf("DeltaTime (dt): %f | Kecepatan Y: %f | Posisi Y: %f\n", dt, car->velocity.y, car->position.y);

    for (int i = 0; i < 2; i++){
        float roda_x_loc = car->wheelPositions[i].x;
        float roda_y_loc = car->wheelPositions[i].y;

        float cosR = cosf(car->rotation);
        float sinR = sinf(car->rotation);

        float pusat_roda_x = car->position.x + (roda_x_loc * cosR - roda_y_loc * sinR);
        float pusat_roda_y = car->position.y + (roda_x_loc * sinR + roda_y_loc * cosR);

        float batas_bawah_roda = pusat_roda_y + car->wheelRadius;
        float tinggi_tanah =  getTerrainHeight(pusat_roda_x);

        if (batas_bawah_roda > tinggi_tanah) {
            float kedalaman =  batas_bawah_roda - tinggi_tanah;

            //Hooke law: F = -k * x
            float k = 400.0f;
            float damping = 10.0f;
            float gaya_pegas = -k * kedalaman;
            float gaya_redaman = -damping * car->velocity.y;

            float total_gaya = gaya_pegas + gaya_redaman;
            car->velocity.y = car->velocity.y + (total_gaya * dt);

        }


    }

    //Rotasi Mobil
    float x_belakang = car->position.x + car->wheelPositions[0].x;
    float x_depan = car->position.x + car->wheelPositions[1].x;

    float y_tanah_belakang =  getTerrainHeight(x_belakang);
    float y_tanah_depan =  getTerrainHeight(x_depan);

    //hitung delta x dan delta y antara roda depan dan belakang
    float delta_x = x_depan - x_belakang;
    float delta_y = y_tanah_depan - y_tanah_belakang;

    //hitung sudut kemiringan mobil
    float target_rotation = atan2f(delta_y, delta_x);
    
    //pengaplikasian ke mobil 
    car->rotation = car->rotation + (target_rotation - car->rotation) * 10.0f * dt;

    //Kontrol Mobil
    if (IsKeyDown(KEY_RIGHT)) {
        car->velocity.x = car->velocity.x + (TENAGA_MOBIL * dt);
    } else if (IsKeyDown(KEY_LEFT)) {
        car->velocity.x = car->velocity.x - (TENAGA_MOBIL * dt);
    }

    //gaya gesek 
    car->velocity.x = car->velocity.x * 0.99f; 
    car->position.x = car->position.x + (car->velocity.x * dt);

    //putaran roda
    float jarak_x = car->velocity.x * dt;
    car->wheelRotation = car->wheelRotation + (jarak_x / car->wheelRadius);

}
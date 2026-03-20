#include "physics.h"

#define TENAGA_MOBIL 500.0f
#define GRAVITY 700.0f 

particle smokePool[50];

void UpdatePhysics(Car *car, float dt) {
    car->velocity.y = car->velocity.y + (GRAVITY * dt);
    car->position.y = car->position.y + (car->velocity.y * dt);
    
    printf("DeltaTime (dt): %f | Kecepatan Y: %f | Posisi Y: %f\n", dt, car->velocity.y, car->position.y);
    int roda_ditanah = 0;

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
            float max_suspension = 20.0f;

            if (kedalaman > max_suspension) {
                kedalaman = max_suspension;
            }
            //Hooke law: F = -k * x
            float k = 400.0f;
            float damping = 10.0f;
            float gaya_pegas = -k * kedalaman;
            float gaya_redaman = -damping * car->velocity.y;

            float total_gaya = gaya_pegas + gaya_redaman;
            car->velocity.y = car->velocity.y + (total_gaya * dt);

        }

        float penetrasi = batas_bawah_roda - tinggi_tanah;

        if (penetrasi > 0) {
            car->wheelCompression[i] = penetrasi;
            car->position.y = car->position.y - (penetrasi * 0.5f); // Koreksi posisi mobil agar tidak terlalu masuk ke tanah
            roda_ditanah++;
        }else{
            car->wheelCompression[i] = car->wheelCompression[i] - car->wheelCompression[i] * 15.0f * dt; 
        }

    }

    // physics mobil ditanah dan diudara
    if (roda_ditanah > 0) {
        float x_belakang = car->position.x + car->wheelPositions[0].x;
        float x_depan = car->position.x + car->wheelPositions[1].x;
        float y_tanah_belakang =  getTerrainHeight(x_belakang);
        float y_tanah_depan =  getTerrainHeight(x_depan);

        float delta_x = x_depan - x_belakang;
        float delta_y = y_tanah_depan - y_tanah_belakang;
        float target_rotation = atan2f(delta_y, delta_x);

        float kecepatan_putar = (target_rotation - car->rotation) * 10.0f;
        car->angularVelocity = kecepatan_putar;

        car->rotation = car->rotation + (car->angularVelocity * dt);
        
        //Kontrol Mobil
        if (IsKeyDown(KEY_RIGHT)) {
            car->velocity.x = car->velocity.x + (TENAGA_MOBIL * dt);

            float knalpot_loc_x = -40.0f;
            float knalpot_loc_y = 15.0f;
            float cosR = cosf(car->rotation);
            float sinR = sinf(car->rotation);

            //translasai dan rotasi  knalpot (Trigonometri)
            float knalpot_x = car->position.x + (knalpot_loc_x * cosR - knalpot_loc_y * sinR);
            float knalpot_y = car->position.y + (knalpot_loc_x * sinR + knalpot_loc_y * cosR);

            for (int i = 0; i < 50; i++) {
                if (smokePool[i].active == false){
                    smokePool[i].active = true;
                    smokePool[i].position.x = knalpot_x;
                    smokePool[i].position.y = knalpot_y;
                    smokePool[i].velocity.x = -150.0f;
                    smokePool[i].velocity.y = -50.0f;
                    smokePool[i].lifetime = 0.5f; // 0,5 detik
                    break;
                }
            }
        } else if (IsKeyDown(KEY_LEFT)) {
            car->velocity.x = car->velocity.x - (TENAGA_MOBIL * dt);
        }

    } else {
        //Kontrol mobil di udara
        float tenaga_putar_udara = 5.0f;
        if (IsKeyDown(KEY_RIGHT)) {
            car->angularVelocity = car->angularVelocity + (tenaga_putar_udara * dt);
        } else if (IsKeyDown(KEY_LEFT)) {
            car->angularVelocity = car->angularVelocity - (tenaga_putar_udara * dt);
        }

        car->rotation = car->rotation + (car->angularVelocity * dt);
        car->angularVelocity = car->angularVelocity * 0.98f; // Redaman putar di udara
    }

    //gaya gesek 
    car->velocity.x = car->velocity.x * 0.99f; 
    car->position.x = car->position.x + (car->velocity.x * dt);

    //putaran roda
    float jarak_x = car->velocity.x * dt;
    car->wheelRotation = car->wheelRotation + (jarak_x / car->wheelRadius);


    float panjang_map = (TERRAIN_COUNT - 1) * 10.0f;
    float batas_mobil_mentok = panjang_map - 40.0f; // 40 adalah jarak dari pusat mobil ke roda depan

    if (car->position.x > batas_mobil_mentok) {
    car->position.x = batas_mobil_mentok;
    car->velocity.x = 0.0f;
            }
}

void updateSmoke(float dt){
    for (int i = 0; i < 50; i++){
        smokePool[i].lifetime = smokePool[i].lifetime - dt;
        if (smokePool[i].lifetime <= 0) {
            smokePool[i].active = false;
        } else {
            smokePool[i].position.x = smokePool[i].position.x + (smokePool[i].velocity.x * dt);
            smokePool[i].position.y = smokePool[i].position.y + (smokePool[i].velocity.y * dt);
        }
    }

}

void drawSmoke(void){
    for (int i = 0; i < 50; i++){
        if (smokePool[i].active == true){
            int px = (int)smokePool[i].position.x;
            int py = (int)smokePool[i].position.y;

            BresenhamLine(px - 2, py, px + 2, py, GRAY);
            BresenhamLine(px, py - 2, px, py + 2, GRAY);
        }
    }
}
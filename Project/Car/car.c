#include "car.h"

void InitCar(Car *car, float startX, float startY) {
    car->position.x = startX;
    car->position.y = startY;
    
    car->velocity.x = 0.0f;
    car->velocity.y = 0.0f;
    car->rotation = 0.0f;

    car->vertices[0] = (Vector2){-40, 15};  // Bawah Belakang
    car->vertices[1] = (Vector2){-40, -5};  // Bagasi
    car->vertices[2] = (Vector2){-20, -20}; // Atap Belakang
    car->vertices[3] = (Vector2){10, -20};  // Atap Depan
    car->vertices[4] = (Vector2){40, -5};   // Kap Mesin
    car->vertices[5] = (Vector2){40, 15};   // Bawah Depan

    car->wheelPositions[0] = (Vector2){-25, 30}; // Roda Belakang
    car->wheelPositions[1] = (Vector2){25, 30};  // Roda Depan
    
    car->wheelRadius = 15.0f;
    car->wheelRotation = 0.0f;
    car->wheelCompression[0] = 0.0f;
    car->wheelCompression[1] = 0.0f;
    car->angularVelocity = 0.0f;
}

void DrawCar(Car *car) {
    float cosR = cosf(car->rotation );
    float sinR = sinf(car->rotation );

    Vector2 ScreenVertices[CAR_VERTEX_COUNT];

    for (int i = 0 ; i < CAR_VERTEX_COUNT; i++) {
        float x_loc = car->vertices[i].x;
        float y_loc = car->vertices[i].y;
        
        float X_rotation = x_loc * cosR - y_loc * sinR;
        float Y_rotation = x_loc * sinR + y_loc * cosR;

        //Translasion
        ScreenVertices[i].x = car->position.x + X_rotation;
        ScreenVertices[i].y = car->position.y + Y_rotation;
       
    }

    //Gambar body mobil
    for (int i = 0; i < CAR_VERTEX_COUNT; i++) {
        int next = (i + 1) % CAR_VERTEX_COUNT;
        BresenhamLine((int)ScreenVertices[i].x, (int)ScreenVertices[i].y,
                      (int)ScreenVertices[next].x, (int)ScreenVertices[next].y, 
                      BLACK);
    }

    //Gambar roda
    for (int w = 0; w < 2; w++) {
        float y_roda_dinamis = car->wheelPositions[w].y - car->wheelCompression[w];
        float pusat_roda_x = (car->wheelPositions[w].x * cosf(car->rotation)) - (y_roda_dinamis * sinf(car->rotation));
        float pusat_roda_y = (car->wheelPositions[w].x * sinf(car->rotation)) + (y_roda_dinamis * cosf(car->rotation));
        
        float Screen_X = pusat_roda_x + car->position.x;
        float Screen_Y = pusat_roda_y + car->position.y;

        int N = 20; // Jumlah titik untuk menggambar lingkaran
        float Theta =  (2 * 3.14159265f) / N; // Sudut antar titik
        Vector2 tepiRoda[N];

        for (int i = 0; i < N; i++){
            float angle = (i * Theta) + car->wheelRotation; 
            tepiRoda[i].x = Screen_X +(car->wheelRadius * cosf(angle)) ;
            tepiRoda[i].y = Screen_Y +(car->wheelRadius * sinf(angle)) ;
        }

        for (int i = 0; i < N; i++) {
            int next = (i + 1) % N;
            int jumlah_velg = 5 ;
            int langkah = N / jumlah_velg;
            BresenhamLine((int)tepiRoda[i].x, (int)tepiRoda[i].y,
                          (int)tepiRoda[next].x, (int)tepiRoda[next].y, 
                          BLACK);

            for (int i = 0; i < N; i += langkah) {
            BresenhamLine((int)Screen_X, (int)Screen_Y,
                          (int)tepiRoda[i].x, (int)tepiRoda[i].y, 
                          BLACK);
            }
        }
    }
}


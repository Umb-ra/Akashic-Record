# Grafika Komputer — Algoritma DDA & Bresenham

Aplikasi desktop interaktif menggunakan **Raylib** dan **C** yang mendemonstrasikan empat program gambar garis berbasis algoritma rasterisasi klasik.

> **Catatan penting:** Tidak ada fungsi gambar garis bawaan Raylib yang digunakan. Setiap piksel digambar menggunakan `DrawPixel()` dari implementasi DDA atau Bresenham yang ditulis sendiri.

---

## Daftar Program

| Program | Algoritma | Materi |
|---------|-----------|--------|
| 1 | DDA | Diagram Kartesian — garis lurus pada sumbu XY |
| 2 | DDA | Berbagai style garis (normal, dash, tebal, dash-dot) |
| 3 | Bresenham | Diagram Kartesian — garis lurus pada sumbu XY |
| 4 | Bresenham | Berbagai style garis (normal, dash, tebal, dash-dot) |

---

## Struktur Modular

Kode sumber dipisah menjadi modul-modul yang mandiri:

```
├── main.c                        ← Entry point, main loop
├── screen_type.h                 ← Enum Screen & konstanta layar
├── coords.h / coords.c           ← Konversi koordinat CS_X(), CS_Y()
│
├── src/algo/
│   ├── dda.h + dda.c             ← DDALine, DDA_DashedLine, DDA_ThickLine, DDA_DashDotLine
│   └── bresenham.h + bresenham.c ← BresenhamLine, Bres_DashedLine, Bres_ThickLine, Bres_DashDotLine
│
├── src/ui/
│   ├── primitives.h + primitives.c     ← DrawDot
│   ├── back_button.h + back_button.c   ← DrawBackButton, BackButtonPressed
│   └── cartesian.h + cartesian.c       ← DrawCartesianGrid, DrawCoordInfo
│
├── src/screens/
│   ├── program1.h + program1.c   ← DDA Kartesian
│   ├── program2.h + program2.c   ← DDA Style Garis
│   ├── program3.h + program3.c   ← Bresenham Kartesian
│   ├── program4.h + program4.c   ← Bresenham Style Garis
│   ├── about.h + about.c         ← Halaman About
│   └── menu.h + menu.c           ← Menu Utama
│
├── Makefile                      ← Build Linux/macOS (pkg-config)
├── Makefile.win                  ← Build Windows (MinGW + raylib manual)
└── README.md                     ← Dokumentasi ini
```

---

## Cara Menjalankan

### Linux / macOS

```bash
make run
```

### Windows (MinGW / w64devkit)

```bat
      make -f Makefile.win        <- hanya build
      make -f Makefile.win run    <- build + jalankan 
      make -f Makefile.win clean  <- hapus hasil build
```

Pastikan Raylib sudah diunduh dan sesuaikan path di `Makefile.win` (lihat komentar di dalamnya).

### Kontrol

| Tombol | Fungsi |
|--------|--------|
| `1` – `4` | Membuka program |
| `A` | Membuka halaman About |
| `ESC` atau `BACKSPACE` | Kembali ke menu |
| Klik tombol `< BACK` | Kembali ke menu (mouse) |

---

## Penyesuaian Sistem Koordinat

Sebelum membahas algoritma, penting memahami perbedaan dua sistem koordinat:

```
LAYAR (Screen)               KARTESIAN
(0,0)─────────► +X           +Y ▲
  │                             │
  │                          ───┼──► +X
  ▼                             │
 +Y                          (0,0)
```

| Properti | Layar | Kartesian |
|----------|-------|-----------|
| Titik (0,0) | Pojok kiri atas | Tengah bidang |
| Arah Y positif | **Ke bawah** | **Ke atas** |
| Arah X positif | Ke kanan | Ke kanan |

**Rumus konversi Kartesian → Layar:**

```
screen_x = originX + cart_x × tickStep
screen_y = originY − cart_y × tickStep   ← tanda MINUS karena Y terbalik
```

**Contoh konkret** (originX=500, originY=380, tickStep=38):

| Titik Kartesian | Hitung screen_x | Hitung screen_y | Hasil Layar |
|-----------------|-----------------|-----------------|-------------|
| (−6, −4) | 500 + (−6)×38 = 500−228 | 380 − (−4)×38 = 380+152 | (272, 532) |
| ( 6,  5) | 500 + ( 6)×38 = 500+228 | 380 − ( 5)×38 = 380−190 | (728, 190) |
| ( 0,  0) | 500 + 0×38 = 500 | 380 − 0×38 = 380 | (500, 380) |
| ( 3, −6) | 500 + 3×38 = 614 | 380 − (−6)×38 = 380+228 | (614, 608) |

Titik (−6,−4) ada di kiri-bawah sumbu Kartesian → layar: (272, **532**) = lebih bawah (nilai besar). ✓  
Titik (6,5) ada di kanan-atas → layar: (728, **190**) = lebih atas (nilai kecil). ✓

---

## Program 1 — Algoritma DDA

### Konsep Matematika

**DDA (Digital Differential Analyzer)** membagi panjang garis menjadi sejumlah langkah, lalu menghitung posisi piksel tiap langkah dengan inkrement floating-point konstan.

Diberikan titik awal `(x1, y1)` dan titik akhir `(x2, y2)`:

```
dx    = x2 − x1
dy    = y2 − y1
steps = max(|dx|, |dy|)     ← pilih dimensi terbesar agar tidak ada piksel yang dilewati

xInc  = dx / steps           ← pertambahan X per langkah (float)
yInc  = dy / steps           ← pertambahan Y per langkah (float)
```

Kemudian plot piksel untuk setiap langkah `i = 0..steps`:
```
x[i] = x1 + i × xInc
y[i] = y1 + i × yInc
plot_pixel( round(x[i]), round(y[i]) )
```

### Contoh Perhitungan Lengkap — Titik (2, 3) ke (7, 6)

```
dx    = 7 − 2 = 5
dy    = 6 − 3 = 3
steps = max(5, 3) = 5

xInc  = 5 / 5 = 1.0
yInc  = 3 / 5 = 0.6
```

Tabel iterasi:

| i | x (float) | y (float) | round(x) | round(y) | Piksel |
|---|-----------|-----------|----------|----------|--------|
| 0 | 2.0       | 3.0       | **2**    | **3**    | (2, 3) |
| 1 | 3.0       | 3.6       | **3**    | **4**    | (3, 4) |
| 2 | 4.0       | 4.2       | **4**    | **4**    | (4, 4) |
| 3 | 5.0       | 4.8       | **5**    | **5**    | (5, 5) |
| 4 | 6.0       | 5.4       | **6**    | **5**    | (6, 5) |
| 5 | 7.0       | 6.0       | **7**    | **6**    | (7, 6) |

Total: **6 piksel** — (2,3), (3,4), (4,4), (5,5), (6,5), (7,6)

Visualisasi piksel:
```
y=6  . . . . . █
y=5  . . . . █ .   ← i=3 round(4.8)=5, i=4 round(5.4)=5
y=4  . . █ █ . .   ← i=1 round(3.6)=4, i=2 round(4.2)=4
y=3  █ . . . . .
     x=2 3 4 5 6 7
```

### Contoh Nyata dari Program 1 — Garis 1: (−6,−4) ke (6,5)

Setelah konversi koordinat: DDALine(272, 532, 728, 190)
```
dx    = 728 − 272 = 456
dy    = 190 − 532 = −342     ← negatif karena naik ke atas layar
steps = max(456, 342) = 456

xInc  = 456 / 456 =  1.000
yInc  = −342 / 456 = −0.750  ← Y berkurang = piksel naik ke atas
```

Tiga langkah pertama:

| i | x | y | Piksel |
|---|---|---|--------|
| 0 | 272.000 | 532.000 | (272, 532) |
| 1 | 273.000 | 531.250 | (273, 531) |
| 2 | 274.000 | 530.500 | (274, 531) |
| 3 | 275.000 | 529.750 | (275, 530) |
| … | … | … | … |
| 456 | 728.000 | 190.000 | (728, 190) |

### Implementasi C

```c
// File: src/algo/dda.c
void DDALine(int x1, int y1, int x2, int y2, Color color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    if (steps == 0) { DrawPixel(x1, y1, color); return; }

    float xInc = (float)dx / steps;
    float yInc = (float)dy / steps;
    float x = (float)x1, y = (float)y1;

    for (int i = 0; i <= steps; i++) {
        DrawPixel((int)roundf(x), (int)roundf(y), color);
        x += xInc;
        y += yInc;
    }
}
```

---

## Program 2 — Style Garis dengan DDA

Semua variasi garis dibangun di atas `DDALine()` sebagai primitif dasar.

### 2a. Garis Putus-putus (Dashed)

**Ide:** Modifikasi algoritma dasar DDA dengan menambahkan penghitung (counter) langkah integer. Selama langkah masih di bawah `dashLen`, piksel digambar. Setelah melampauinya, penggambaran dimatikan selama `gapLen`, lalu diulangi bergantian secara kontinu tanpa harus menghitung ulang panjang garis dengan `sqrt`.

**Contoh Visual:** Garis dari (0, 0) ke (100, 0), dash=20, gap=10
Hasil visual: `████████████████████___________████████████████████___________████████████████████`

### 2b. Garis Tebal (Thick Line via DDA)

**Ide:** Gambar beberapa garis DDA paralel yang bergeser tegak lurus terhadap arah garis.

**Contoh:** Garis dari (50, 200) ke (950, 200), ketebalan=5

```
dx = 900, dy = 0
len = sqrt(900² + 0²) = 900

Vektor tegak lurus:
  px = −dy / len = −0 / 900 =  0.0
  py =  dx / len =  900/900 =  1.0

half = 5/2 = 2

Garis yang digambar (t dari −2 sampai +2):
  t=−2: ox=round(0×−2)=0, oy=round(1×−2)=−2 → DDALine(50, 198, 950, 198)
  t=−1: ox=0, oy=−1                           → DDALine(50, 199, 950, 199)
  t= 0: ox=0, oy= 0                           → DDALine(50, 200, 950, 200)  ← garis utama
  t=+1: ox=0, oy=+1                           → DDALine(50, 201, 950, 201)
  t=+2: ox=0, oy=+2                           → DDALine(50, 202, 950, 202)
```

Hasilnya 5 garis horizontal yang rapat = garis tebal 5px.

### 2c. Garis Dash-Dot

Sama halnya dengan Dashed Line, pola ini menghindari iterasi berbasis panjang jarak floating-point demi performa. Polanya diformulasikan ulang meggunakan *state-machine* dengan array batasan fase:

```
phases[] = { 18, 5, 5, 5 }    ← target jumlah langkah per fase
drawPh[] = {  1, 0, 1, 0 }    ← 1=gambar, 0=lewati

Algoritma mengiterasi satu langkah DDA/Piksel demi langkah, seraya menambah counter. Jika counter mencapai target `phases`, index `phase` bergeser ke fase berikutnya.
```

---

## Program 3 — Algoritma Bresenham (Garis)

### Konsep Matematika

**Algoritma Bresenham** menggunakan **decision parameter integer** untuk memutuskan piksel mana yang digambar, tanpa satu pun operasi floating-point.

Diberikan titik `(x1, y1)` ke `(x2, y2)`:

```
dx  = |x2 − x1|,   dy  = |y2 − y1|
sx  = +1 jika x2 > x1, else −1      ← arah X
sy  = +1 jika y2 > y1, else −1      ← arah Y
err = dx − dy                        ← decision parameter awal
```

Setiap iterasi:
```
1. Plot piksel(x, y)
2. Jika sudah sampai tujuan → stop
3. e2 = 2 × err
4. Jika e2 > −dy:  err −= dy;  x += sx    ← langkah horizontal
5. Jika e2 <  dx:  err += dx;  y += sy    ← langkah vertikal
```

### Mengapa Tanda `err = dx − dy`?

Persamaan garis ideal: `f(x, y) = dy·x − dx·y + C = 0`

Jika `f > 0`: piksel berada di atas garis → geser ke bawah-kanan (NE)  
Jika `f < 0`: piksel berada di bawah garis → geser ke kanan (E)

Decision parameter `err` menangkap selisih ini secara integer. Karena yang penting hanya **tanda** dari err (bukan nilainya), seluruh perhitungan bisa dilakukan dengan penjumlahan/pengurangan integer saja.

### Contoh Perhitungan Lengkap — Titik (2, 3) ke (7, 6)

```
dx = |7−2| = 5,   dy = |6−3| = 3
sx = +1,          sy = +1
err = dx − dy = 5 − 3 = 2
```

Tabel iterasi lengkap:

| Langkah | Plot | err | e2 = 2×err | e2 > −dy(−3)? | Aksi X | e2 < dx(5)? | Aksi Y | err baru |
|---------|------|-----|------------|----------------|--------|-------------|--------|----------|
| 1 | **(2,3)** | 2 | 4 | 4 > −3 ✓ | x=3, err=2−3=**−1** | 4 < 5 ✓ | y=4, err=−1+5=**4** | 4 |
| 2 | **(3,4)** | 4 | 8 | 8 > −3 ✓ | x=4, err=4−3=**1** | 8 < 5 ✗ | — | 1 |
| 3 | **(4,4)** | 1 | 2 | 2 > −3 ✓ | x=5, err=1−3=**−2** | 2 < 5 ✓ | y=5, err=−2+5=**3** | 3 |
| 4 | **(5,5)** | 3 | 6 | 6 > −3 ✓ | x=6, err=3−3=**0** | 6 < 5 ✗ | — | 0 |
| 5 | **(6,5)** | 0 | 0 | 0 > −3 ✓ | x=7, err=0−3=**−3** | 0 < 5 ✓ | y=6, err=−3+5=**2** | 2 |
| 6 | **(7,6)** | — | — | — | — | — | — | selesai |

Total: **6 piksel** — (2,3), (3,4), (4,4), (5,5), (6,5), (7,6)

Perhatikan: **hasilnya identik dengan DDA** pada contoh yang sama! Perbedaannya ada pada *cara menghitung* (float vs integer), bukan hasil akhirnya.

Visualisasi piksel:
```
y=6  . . . . . █
y=5  . . . . █ .   ← langkah 3 dan 4 (maju X saja di langkah 4, tidak naik Y)
y=4  . . █ █ . .   ← langkah 1 dan 2 (langkah 2: maju X saja, tidak naik Y)
y=3  █ . . . . .
     x=2 3 4 5 6 7
```

### Contoh Nyata dari Program 3 — Garis 1: (−7,−2) ke (7,5)

Setelah konversi koordinat: BresenhamLine(234, 456, 766, 190)
```
dx = |766−234| = 532
dy = |190−456| = 266
sx = +1,  sy = −1         ← Y layar berkurang (naik ke atas layar = +Y Kartesian)
err = 532 − 266 = 266

Tiga langkah pertama:
  Langkah 1: plot(234,456), e2=532
    e2(532) > −266 ✓ → x=235, err=266−266=0
    e2(532) <  532 ✗ → Y tidak berubah

  Langkah 2: plot(235,456), e2=0
    e2(0) > −266 ✓ → x=236, err=0−266=−266
    e2(0) <  532 ✓ → y=455, err=−266+532=266

  Langkah 3: plot(236,455), e2=532
    e2(532) > −266 ✓ → x=237, err=266−266=0
    e2(532) <  532 ✗ → Y tidak berubah
  ...
```

Pola yang terlihat: setiap 2 langkah horizontal, piksel naik 1 baris — sesuai kemiringan 5/(2×7)=5/14 di Kartesian.

### Implementasi C

```c
// File: src/algo/bresenham.c
void BresenhamLine(int x1, int y1, int x2, int y2, Color color) {
    int dx  = abs(x2 - x1), dy  = abs(y2 - y1);
    int sx  = (x1 < x2) ? 1 : -1;
    int sy  = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        DrawPixel(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 <  dx) { err += dx; y1 += sy; }
    }
}
```

---

## Program 4 — Style Garis dengan Bresenham

Sama dengan Program 2, gaya garis seperti Dashed maupun Dash-Dot diimplementasikan terintegrasi di dalam **perulangan keputusan error Bresenham utama** sepenuhnya menggunakan kalkulasi integer.

### Keunggulan: Bebas Fungsi Akar (Floating-Point)

Pada implementasi garis putus-putus awam yang naif, program sering memecah segmen dan menghitung jaraknya menggunakan rumus jarak Euclidean `sqrt(dx² + dy²)` yang memakan komputasi berat (*floating-point*). 

Dengan optimasi iterasi yang kita lakukan, Dashed Bresenham secara eksklusif menggunakan algoritma *decision parameter* `err` untuk memutuskan penambahan koordinat piksel dan menggunakan *integer counter++* sederhana untuk menentukan state visibilitas (gambar / bolong). Dengan kata lain, logika garis gaya kini **bebas sepenuhnya** kalkulasi perhitungan floating-point dan operasi akar.

---

## Perbandingan DDA vs Bresenham

| Aspek | DDA | Bresenham |
|-------|-----|-----------|
| Tipe data | `float` | `int` saja |
| Operasi per langkah | tambah float, `roundf()` | ×2, perbandingan, tambah int |
| Kemungkinan error | Round-off float pada garis panjang | Tidak ada — integer exact |
| Kemudahan dipahami | Sangat mudah | Perlu memahami decision parameter |
| Kecepatan relatif | Lambat (FPU) | Cepat (ALU integer) |
| Cocok untuk | Edukasi, prototyping | Produksi, embedded, GPU pipeline |
| Jumlah piksel (contoh 5px) | 6 piksel | 6 piksel — **sama** |

> Jumlah piksel biasanya identik. Perbedaan ada pada **efisiensi komputasi**, bukan visual.

---

## Primitif yang Digunakan

Satu-satunya fungsi Raylib untuk menggambar:
```c
DrawPixel(x, y, color);   // menempatkan satu piksel di koordinat layar
```

Semua garis, pola, titik endpoint, grid, dan avatar di halaman About dibangun dari fungsi kustom di atas `DrawPixel()`.

---

## Stack

- **Bahasa:** C (GCC / MinGW)
- **Library:** Raylib 5.5
- **Build:** GNU Make + pkg-config (Linux) / Makefile.win (Windows)
- **Display:** VNC desktop (Linux) / Window native (Windows)


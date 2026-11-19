#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

// Proiect 1:

// Task 2:
// Aloca o imagine cu N linii si M coloane, formata exact cum o face functia "bmp_read":
unsigned char ***alloc_image(int N, int M) {
    unsigned char ***img = malloc(N * sizeof(unsigned char **));
    for(int i = 0; i < N; i++) {
        img[i] = malloc(M * sizeof(unsigned char *));
        for(int j = 0; j < M; j++) {
            img[i][j] = malloc(3 * sizeof(unsigned char));
        }
    }
    return img;
}

// Elibereara memoria ocupata de o imagine:
void free_image(unsigned char ***img, int N, int M) {
    if(!img) return;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            free(img[i][j]);
        }
        free(img[i]);
    }
    free(img);
}

// Task 3: Dreptunghi rosu de grosime k:
void draw_red_rectangle(unsigned char ***img, int N, int M, int left, int right, int top, int bottom, int k) {
    // Verificare pentru limitele imaginii:
    if(left < 0) left = 0;
    if(right >= M) right = M - 1;
    if(top < 0) top = 0;
    if(bottom >= N) bottom = N - 1;
    
    for(int i = top; i <= bottom; i++) {
        for(int j = left; j <= right; j++) {
            // Verificare daca pixelul se afla pe marginea dreptunghiului:
            if(i < top + k || i > bottom - k || j < left + k || j > right - k) {
                img[i][j][0] = 255; // red
                img[i][j][1] = 0;   // green
                img[i][j][2] = 0;   // blue
            }
        }
    }
}

// Task 4: Crop image:
unsigned char ***crop_image(unsigned char ***img, int *N, int *M, int left, int right, int top, int bottom) {
    // Verificare pentru limitele imaginii:
    if(left < 0) left = 0;
    if(right >= *M) right = *M - 1;
    if(top < 0) top = 0;
    if(bottom >= *N) bottom = *N - 1;

    int new_N = bottom - top + 1;
    int new_M = right - left + 1;
    unsigned char ***crop_img = alloc_image(new_N, new_M);

    for(int i = 0; i < new_N; i++) {
        for(int j = 0; j < new_M; j++) {
            crop_img[i][j][0] = img[top + i][left + j][0];
            crop_img[i][j][1] = img[top + i][left + j][1];
            crop_img[i][j][2] = img[top + i][left + j][2];
        }
    }
    // Eliberez vechea imagine si actualizez dimensiunile:
    free_image(img, *N, *M);
    *N = new_N;
    *M = new_M;

    return crop_img;
}

// Task 5: Transformare imagine in alb-negru:
void apply_grayscale(unsigned char ***img, int N, int M) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            int r = img[i][j][0];
            int g = img[i][j][1];
            int b = img[i][j][2];
            unsigned char gray = (unsigned char)((r + g + b) / 3);
            img[i][j][0] = img[i][j][1] = img[i][j][2] = gray;
        }
    }
}

// Task 6: Resize imagine in forma patrata:
unsigned char ***resize_square(unsigned char ***img, int *N, int *M) {
    int max_dim = (*N > *M) ? *N : *M;
    unsigned char ***new_img = alloc_image(max_dim, max_dim);

    int offset_N = (max_dim - *N) / 2;
    int offset_M = (max_dim - *M) / 2;
    
    for(int i = 0; i < max_dim; i++) {
        for(int j = 0; j < max_dim; j++) {
            int rel_i = i - offset_N;
            int rel_j = j - offset_M;
            if(rel_i < 0) rel_i = 0;
            if(rel_i >= *N) rel_i = *N - 1;
            if(rel_j < 0) rel_j = 0;
            if(rel_j >= *M) rel_j = *M - 1;

            new_img[i][j][0] = img[rel_i][rel_j][0];
            new_img[i][j][1] = img[rel_i][rel_j][1];
            new_img[i][j][2] = img[rel_i][rel_j][2];
        }
    }

    free_image(img, *N, *M);
    *N = *M = max_dim;
    return new_img;
}

int test_proiect1(void) {
    int N, M;
    // Task 2: Citirea imaginii:
    unsigned char ***img = bmp_read("input.bmp", &N, &M);
    if(!img) {
        printf("Eroare la citirea imaginii.\n");
        return 1;
    }
    // Coordonate test:
    int left = M / 4, right = M * 3 / 4;
    int top = N / 4, bottom = N * 3 / 4;
    int thickness = 5;

    // Test Task 3 (dreptunghi rosu):
    draw_red_rectangle(img, N, M, left, right, top, bottom, thickness);
    bmw_write("output_task3.bmp", img, N, M);
    
    // Test Task 4 (crop):
    img = crop_image(img, &N, &M, left, right, top, bottom);
    bmw_write("output_task4.bmp", img, N, M);

    // Test Task 5 (grayscale):
    apply_grayscale(img, N, M);
    bmw_write("output_task5.bmp", img, N, M);

    // Test Task 6 (resize square):
    img = resize_square(img, &N, &M);
    bmw_write("output_task6.bmp", img, N, M);

    free_image(img, N, M);
    printf("Operatiuni procesate cu succes. Au fost generate fisierele output.\n");
    return 0;
}
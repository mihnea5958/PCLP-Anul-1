#ifndef BMP_IO_RGB_H
#define BMP_IO_RGB_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define BMP_GET32(p) ((uint32_t)(p)[0] | (uint32_t)(p)[1]<<8 | (uint32_t)(p)[2]<<16 | (uint32_t)(p)[3]<<24)
#define BMP_PUT32(p,v) do { uint32_t bmp_v_ = (uint32_t)(v); for(int bmp_k_=0; bmp_k_<4; ++bmp_k_) (p)[bmp_k_] = (unsigned char)(bmp_v_ >> (8*bmp_k_)); } while(0)

/* img[N][M][3]: canalele 0=R, 1=G, 2=B; img[0][0] = coltul stanga-sus.
   Fiecare img[i] si img[i][j] este alocat separat. Citire BI_RGB 24/32 bpp.
   Returneaza NULL la eroare; pentru argumente valide, *N si *M raman 0. */
static inline unsigned char ***bmp_read(const char *path, int *N, int *M)
{
    if (!N || !M || N == M) return NULL;
    *N = *M = 0; if (!path) return NULL;
    FILE *f = fopen(path, "rb"); if (!f) return NULL;
    unsigned char h[54], *buf=NULL, ***img=NULL; int nr=0, nc=0;
    if (fread(h, 1, 54, f) != 54 || h[0]!='B' || h[1]!='M') goto fail;
    uint32_t off=BMP_GET32(h+10), dib=BMP_GET32(h+14), w=BMP_GET32(h+18), sh=BMP_GET32(h+22);
    int top = (int)(sh >> 31), b = h[28]/8; uint32_t n = top ? (uint32_t)(0u-sh) : sh;
    if ((dib!=40 && dib!=52 && dib!=56 && dib!=108 && dib!=124) || (uint64_t)off<14ull+dib ||
        h[26]!=1 || h[27] || (h[28]!=24 && h[28]!=32) || h[29] || BMP_GET32(h+30) ||
        !w || w>INT32_MAX || w>INT_MAX || !n || n>INT32_MAX || n>INT_MAX) goto fail;
    uint64_t stride = ((uint64_t)w*b+3)/4*4;
    if (stride>SIZE_MAX || (uint64_t)n*sizeof(*img)>SIZE_MAX || (uint64_t)w*sizeof(**img)>SIZE_MAX) goto fail;
    if (fseek(f, 0, SEEK_END)) goto fail;
    long len = ftell(f);
    if (len<0 || (uint64_t)len<(uint64_t)off+stride*n || fseek(f, (long)off, SEEK_SET)) goto fail;
    img=malloc((size_t)n*sizeof(*img)); buf=malloc((size_t)stride); if (!img || !buf) goto fail;
    for (uint32_t y=0; y<n; ++y) {
        img[y]=malloc((size_t)w*sizeof(**img)); if (!img[y]) goto fail; ++nr; nc=0;
        for (uint32_t x=0; x<w; ++x) { img[y][x]=malloc(3); if (!img[y][x]) goto fail; ++nc; }
    }
    for (uint32_t y=0; y<n; ++y) {
        if (fread(buf, 1, (size_t)stride, f)!=(size_t)stride) goto fail;
        for (size_t x=0; x<w; ++x)
            for (int k=0; k<3; ++k) img[top?y:n-1-y][x][k]=buf[b*x+2-k];
    }
    free(buf); fclose(f); *N=(int)n; *M=(int)w; return img;
fail:
    if (img) { for (int y=0; y<nr; ++y) { for (uint32_t x=0; x<(y==nr-1?(uint32_t)nc:w); ++x) free(img[y][x]); free(img[y]); } free(img); }
    free(buf); fclose(f); return NULL;
}

/* Scrie BMP 24 bpp. Returneaza 1 la succes, 0 la eroare. Nu modifica matricea. */
static inline int bmp_write(const char *path, unsigned char ***img, int N, int M)
{
    if (!path || !img || N<=0 || M<=0) return 0;
    if ((uint64_t)N>INT32_MAX || (uint64_t)M>INT32_MAX) return 0;
    uint64_t stride=((uint64_t)M*3+3)/4*4, bytes=stride*(uint64_t)N;
    if (stride>SIZE_MAX || bytes>UINT32_MAX-54u) return 0;
    for (int y=0; y<N; ++y) { if (!img[y]) return 0; for (int x=0; x<M; ++x) if (!img[y][x]) return 0; }
    unsigned char h[54]={0}, *buf=calloc(1,(size_t)stride); if (!buf) return 0;
    h[0]='B'; h[1]='M'; h[26]=1; h[28]=24;
    BMP_PUT32(h+2,54+bytes); BMP_PUT32(h+10,54); BMP_PUT32(h+14,40);
    BMP_PUT32(h+18,M); BMP_PUT32(h+22,N); BMP_PUT32(h+34,bytes);
    FILE *f=fopen(path,"wb"); if (!f) { free(buf); return 0; }
    int ok=fwrite(h,1,54,f)==54;
    for (int y=N; ok && y-->0;) {
        for (size_t x=0; x<(size_t)M; ++x)
            for (int k=0; k<3; ++k) buf[3*x+2-k]=img[y][x][k];
        ok=fwrite(buf,1,(size_t)stride,f)==(size_t)stride;
    }
    if (fclose(f)!=0) ok=0;
    free(buf); return ok;
}
#undef BMP_GET32
#undef BMP_PUT32
#endif

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

int main(void) {
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
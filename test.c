#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"

// Task 1:

Student *alocare_student(char *nume, int varsta, char *cnp, char *grupa, float media) {
    Student *stud = (Student *)malloc(sizeof(Student));
    if(!stud) return NULL;

    strcpy(stud->nume, nume);
    stud->varsta = varsta;
    strcpy(stud->cnp, cnp);
    strcpy(stud->grupa, grupa);
    stud->media = media;

    return stud;
}   

void afisare_student(Student *stud) {
    printf("%s %d %s %s %f\n", stud->nume, stud->varsta, stud->cnp, stud->grupa, stud->media);
}


int comp_cresct(const void *a, const void *b) {
        int a1 = *((const int *)a), b1 = *((const int *)b);
        return a1 > b1;
}

#define N 10
int v[N] = {5, 4, 10, 7, 6, 9, 3, 1, 8, 2};

int main(void) {
    Student *studenti[N];
    // for(int i = 0; i < N; i++) {
    //     studenti[i] = alocare_student(nume[i], varste[i], cnp[i], grupe[i], medii[i]);
    //     afisare_student(studenti[i]);
    // }

    // Task 2:
    // float medii[4], sume[4], cnt[4];
    // for(int i = 0; i < N; i++) {
    //     int an = studenti[i]->grupa[1] - '1';
    //     sume[an] += studenti[i]->varsta;
    //     cnt[an]++;
    // }

    // for(int i = 0; i < 4; i++) {
    //     medii[i] = sume[i] / cnt[i];
    //     printf("Media de varsta pentru anul %d este %f\n", i + 1, medii[i]);
    // }
    qsort(v, N, sizeof(int), comp_cresct);
    for(int i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    return 0;
}
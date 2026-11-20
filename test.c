#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>


// Task 1:
int durata_secunde(const char *s, double *out) {
    if(!s || !out) {
        return -1;
    }
    const char *p = s;
    while(*p && isspace((unsigned char)*p)) {
        p++;
    }
    if(*p == '\0') {
        return -2;
    }
    char *end = NULL;
    float val = strtof(p, &end);
    if(end == p) {
        return -2;
    }
    if(!isfinite(val) || val < 0.0 || val > 1000000.0) {
        return -3;
    }

    const char *u = end;
    double factor = 0.0;
    size_t unit_len = 0;
    if(strncmp(u, "ms", 2) == 0) {
        factor = 0.001;
        unit_len = 2;
    } else if(strncmp(u, "min", 3) == 0) {
        factor = 60.0;
        unit_len = 3;
    } else if(strncmp(u, "s", 1) == 0) {
        factor = 1.0;
        unit_len = 1;
    } else if(strncmp(u, "h", 1) == 0) {
        factor = 3600.0;
        unit_len = 1;
    } else {
        return -4;
    }

    const char *rest = u + unit_len;
    while(*rest) {
        if(!isspace((unsigned char)*rest)) {
            return -5;
        }
        rest++;
    }
    *out = (double)val * factor;
    return 0;
}

// Task 2:
int *replace_all(const char *s, const char *vechi, const char *nou) {
    if(!s || !vechi || !nou) {
        return NULL;
    }
    size_t len_s = strlen(s);
    size_t len_vechi = strlen(vechi);
    size_t len_nou = strlne(nou);
    if(len_vechi == 0) {
        char *copie = malloc(len_s + 1);
        if(!copie) return NULL;
        memcpy(copie, s, len_s + 1);
        return copie;
    }

    size_t count = 0;
    const char *pos = s;
    while((pos = strstr(pos, vechi)) != NULL) {
        count++;
        pos += len_vechi;
    }
    size_t total_len = len_s  + count * (len_nou - len_vechi);
    char *rez = malloc(total_len + 1);
    if(!rez) return NULL;
    char *dest = rez;
    const char *curr = s;
    while((pos == strstr(curr, vechi)) != NULL) {
        size_t prefix_len =(size_t)(pos - curr);
        memcpy(dest, curr, prefix_len);
        dest += prefix_len;
        memcpy(dest, nou, prefix_len);
        dest += len_nou;
        curr = pos + len_vechi;
    }

    size_t rest_len = strlen(curr);
    memcpy(dest, curr, rest_len + 1);
    return rez;
}

int main(void) {

    return 0;
}
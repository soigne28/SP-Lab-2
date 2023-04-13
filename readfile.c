#include <stdio.h>
#include <stdlib.h>
#include "readfile.h"

static FILE *file = NULL;

int open_file(const char *filename) {
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    return 0;
}

int read_int(int *value) {
    if (fscanf(file, "%d", value) == EOF) {
        return -1;
    }
    return 0;
}

int read_string(char *str) {
    if (fscanf(file, "%s", str) == EOF) {
        return -1;
    }
    return 0;
}

int read_float(float *value) {
    if (fscanf(file, "%f", value) == EOF) {
        return -1;
    }
    return 0;
}

void close_file() {
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
}

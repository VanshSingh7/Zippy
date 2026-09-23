#include <stdio.h>
#include "freq.h"

int count_frequencies(const char *filepath, unsigned long freq_table[256]) {
    FILE *fp = fopen(filepath, "rb");  // binary mode: works for any file type
    if (fp == NULL) {
        return -1;
    }

    for (int i = 0; i < 256; i++) {
        freq_table[i] = 0;
    }

    int byte;
    while ((byte = fgetc(fp)) != EOF) {
        freq_table[byte]++;
    }

    fclose(fp);
    return 0;
}

void print_frequencies(unsigned long freq_table[256]) {
    for (int i = 0; i < 256; i++) {
        if (freq_table[i] > 0) {
            if (i >= 32 && i <= 126) {

                printf("'%c' (%3d): %lu\n", i, i, freq_table[i]);
            } else {

                printf("0x%02X      : %lu\n", i, freq_table[i]);
            }
        }
    }
}
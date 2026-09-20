#include <stdio.h>
#include "freq.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    unsigned long freq_table[256];

    if (count_frequencies(argv[1], freq_table) != 0) {
        printf("Error: could not open file '%s'\n", argv[1]);
        return 1;
    }

    print_frequencies(freq_table);
    return 0;
}
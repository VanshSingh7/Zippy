#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freq.h"
#include "tree.h"
#include "bitio.h"
#include "compress.h"

int compress_file(const char *input_path, const char *output_path) {
    unsigned long freq_table[256];
    if (count_frequencies(input_path, freq_table) != 0) {
        return -1;
    }

    unsigned long original_size = 0;
    unsigned short unique_symbols = 0;
    for (int i = 0; i < 256; i++) {
        original_size += freq_table[i];
        if (freq_table[i] > 0) {
            unique_symbols++;
        }
    }

    Node *root = build_tree(freq_table);
    char *codes[256];
    generate_codes(root, codes);

    FILE *out = fopen(output_path, "wb");
    if (out == NULL) {
        free_tree(root);
        return -1;
    }

    fwrite("ZPY1", 1, 4, out);
    fwrite(&original_size, sizeof(unsigned long), 1, out);
    fwrite(&unique_symbols, sizeof(unsigned short), 1, out);

    for (int i = 0; i < 256; i++) {
        if (freq_table[i] > 0) {
            unsigned char byte = (unsigned char)i;
            fwrite(&byte, sizeof(unsigned char), 1, out);
            fwrite(&freq_table[i], sizeof(unsigned long), 1, out);
        }
    }

    FILE *in = fopen(input_path, "rb");
    if (in == NULL) {
        fclose(out);
        free_tree(root);
        return -1;
    }

    BitWriter *bw = bitwriter_create(out);
    int byte;
    while ((byte = fgetc(in)) != EOF) {
        bitwriter_write_code(bw, codes[byte]);
    }
    bitwriter_flush(bw);

    bitwriter_free(bw);
    fclose(in);
    fclose(out);

    for (int i = 0; i < 256; i++) {
        if (codes[i] != NULL) {
            free(codes[i]);
        }
    }
    free_tree(root);

    return 0;
}
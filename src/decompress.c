#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "bitio.h"
#include "decompress.h"

int decompress_file(const char *input_path, const char *output_path) {
    FILE *in = fopen(input_path, "rb");
    if (in == NULL) {
        return -1;
    }

    char magic[4];
    fread(magic, 1, 4, in);
    if (memcmp(magic, "ZPY1", 4) != 0) {
        fclose(in);
        return -1;
    }

    unsigned long original_size;
    fread(&original_size, sizeof(unsigned long), 1, in);

    unsigned short unique_symbols;
    fread(&unique_symbols, sizeof(unsigned short), 1, in);

    unsigned long freq_table[256] = {0};
    for (int i = 0; i < unique_symbols; i++) {
        unsigned char byte;
        unsigned long freq;
        fread(&byte, sizeof(unsigned char), 1, in);
        fread(&freq, sizeof(unsigned long), 1, in);
        freq_table[byte] = freq;
    }

    Node *root = build_tree(freq_table);

    FILE *out = fopen(output_path, "wb");
    if (out == NULL) {
        fclose(in);
        free_tree(root);
        return -1;
    }

    BitReader *br = bitreader_create(in);
    Node *current = root;
    unsigned long bytes_written = 0;

    while (bytes_written < original_size) {
        int bit = bitreader_read_bit(br);
        if (bit == -1) {
            break;
        }

        current = (bit == 0) ? current->left : current->right;

        if (current->left == NULL && current->right == NULL) {
            fputc(current->byte, out);
            bytes_written++;
            current = root;
        }
    }

    bitreader_free(br);
    fclose(in);
    fclose(out);
    free_tree(root);

    return 0;
}
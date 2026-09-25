#include <stdlib.h>
#include "bitio.h"

BitWriter* bitwriter_create(FILE *file) {
    BitWriter *bw = malloc(sizeof(BitWriter));
    bw->file = file;
    bw->buffer = 0;
    bw->bit_count = 0;
    return bw;
}

void bitwriter_write_bit(BitWriter *bw, int bit) {
    bw->buffer = (bw->buffer << 1) | (bit & 1);
    bw->bit_count++;
    if (bw->bit_count == 8) {
        fputc(bw->buffer, bw->file);
        bw->buffer = 0;
        bw->bit_count = 0;
    }
}

void bitwriter_write_code(BitWriter *bw, const char *code) {
    for (int i = 0; code[i] != '\0'; i++) {
        bitwriter_write_bit(bw, code[i] - '0');
    }
}

void bitwriter_flush(BitWriter *bw) {
    if (bw->bit_count > 0) {
        bw->buffer = bw->buffer << (8 - bw->bit_count);
        fputc(bw->buffer, bw->file);
        bw->buffer = 0;
        bw->bit_count = 0;
    }
}

void bitwriter_free(BitWriter *bw) {
    free(bw);
}

BitReader* bitreader_create(FILE *file) {
    BitReader *br = malloc(sizeof(BitReader));
    br->file = file;
    br->buffer = 0;
    br->bit_count = 0;
    return br;
}

int bitreader_read_bit(BitReader *br) {
    if (br->bit_count == 0) {
        int byte = fgetc(br->file);
        if (byte == EOF) {
            return -1;
        }
        br->buffer = (unsigned char)byte;
        br->bit_count = 8;
    }
    br->bit_count--;
    return (br->buffer >> br->bit_count) & 1;
}

void bitreader_free(BitReader *br) {
    free(br);
}
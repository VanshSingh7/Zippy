#ifndef BITIO_H
#define BITIO_H

#include <stdio.h>

typedef struct {
    FILE *file;
    unsigned char buffer;
    int bit_count;   // bits currently held in buffer (0-7)
} BitWriter;

typedef struct {
    FILE *file;
    unsigned char buffer;
    int bit_count;    // bits remaining unread in buffer (0-7)
} BitReader;

BitWriter* bitwriter_create(FILE *file);
void bitwriter_write_bit(BitWriter *bw, int bit);
void bitwriter_write_code(BitWriter *bw, const char *code);
void bitwriter_flush(BitWriter *bw);
void bitwriter_free(BitWriter *bw);

BitReader* bitreader_create(FILE *file);
int bitreader_read_bit(BitReader *br);   // returns 0, 1, or -1 on EOF
void bitreader_free(BitReader *br);

#endif
// #include <stdio.h>
// #include "freq.h"

// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         printf("Usage: %s <file>\n", argv[0]);
//         return 1;
//     }

//     unsigned long freq_table[256];

//     if (count_frequencies(argv[1], freq_table) != 0) {
//         printf("Error: could not open file '%s'\n", argv[1]);
//         return 1;
//     }

//     print_frequencies(freq_table);
//     return 0;
// }

// heap testing

// #include <stdio.h>
// #include <stdlib.h>
// #include "heap.h"

// int main(void) {
//     MinHeap *heap = heap_create(10);

//     // push some test nodes with known frequencies
//     heap_push(heap, node_create('d', 1, NULL, NULL));
//     heap_push(heap, node_create('c', 1, NULL, NULL));
//     heap_push(heap, node_create('b', 2, NULL, NULL));
//     heap_push(heap, node_create('r', 2, NULL, NULL));
//     heap_push(heap, node_create('a', 5, NULL, NULL));

//     printf("Popping in order (should be ascending by freq):\n");
//     while (heap_size(heap) > 0) {
//         Node *n = heap_pop(heap);
//         printf("'%c' : %lu\n", n->byte, n->freq);
//         free(n);
//     }

//     heap_free(heap);
//     return 0;
// }


// combined testinf of freq, heap and tree
// #include <stdio.h>
// #include <stdlib.h>
// #include "freq.h"
// #include "tree.h"

// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         printf("Usage: %s <file>\n", argv[0]);
//         return 1;
//     }

//     unsigned long freq_table[256];
//     if (count_frequencies(argv[1], freq_table) != 0) {
//         printf("Error: could not open file '%s'\n", argv[1]);
//         return 1;
//     }

//     Node *root = build_tree(freq_table);

//     char *codes[256];
//     generate_codes(root, codes);

//     for (int i = 0; i < 256; i++) {
//         if (codes[i] != NULL) {
//             if (i >= 32 && i <= 126) {
//                 printf("'%c' : %s\n", i, codes[i]);
//             } else {
//                 printf("0x%02X : %s\n", i, codes[i]);
//             }
//             free(codes[i]);
//         }
//     }

//     free_tree(root);
//     return 0;
// }

// checking bitio.c

#include <stdio.h>
#include "bitio.h"

int main(void) {
    // --- WRITE PHASE ---
    FILE *out = fopen("bittest.bin", "wb");
    BitWriter *bw = bitwriter_create(out);

    // known test sequence: 1,0,1,1,0,0,1,0,1  (9 bits — not a multiple of 8)
    int test_bits[] = {1, 0, 1, 1, 0, 0, 1, 0, 1};
    int n = 9;

    for (int i = 0; i < n; i++) {
        bitwriter_write_bit(bw, test_bits[i]);
    }
    bitwriter_flush(bw);   // pad and write the final partial byte

    bitwriter_free(bw);
    fclose(out);

    // --- READ PHASE ---
    FILE *in = fopen("bittest.bin", "rb");
    BitReader *br = bitreader_create(in);

    printf("Read back: ");
    for (int i = 0; i < n; i++) {
        int bit = bitreader_read_bit(br);
        printf("%d", bit);
    }
    printf("\n");

    bitreader_free(br);
    fclose(in);

    return 0;
}
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

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main(void) {
    MinHeap *heap = heap_create(10);

    // push some test nodes with known frequencies
    heap_push(heap, node_create('d', 1, NULL, NULL));
    heap_push(heap, node_create('c', 1, NULL, NULL));
    heap_push(heap, node_create('b', 2, NULL, NULL));
    heap_push(heap, node_create('r', 2, NULL, NULL));
    heap_push(heap, node_create('a', 5, NULL, NULL));

    printf("Popping in order (should be ascending by freq):\n");
    while (heap_size(heap) > 0) {
        Node *n = heap_pop(heap);
        printf("'%c' : %lu\n", n->byte, n->freq);
        free(n);
    }

    heap_free(heap);
    return 0;
}
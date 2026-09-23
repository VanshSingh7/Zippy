#ifndef HEAP_H
#define HEAP_H

// A node in the Huffman tree
typedef struct Node {
    unsigned char byte;       // the byte this leaf represents
    unsigned long freq;       // frequency / combined frequency
    struct Node *left;
    struct Node *right;
} Node;

// Min-heap of Node pointers, ordered by freq
typedef struct {
    Node **items;
    int size;           
    int capacity;        
} MinHeap;

MinHeap* heap_create(int capacity);
void heap_free(MinHeap *heap);          // frees the heap array only, not the nodes
void heap_push(MinHeap *heap, Node *node);
Node* heap_pop(MinHeap *heap);           // removes and returns smallest-freq node
int heap_size(MinHeap *heap);

Node* node_create(unsigned char byte, unsigned long freq, Node *left, Node *right);

#endif
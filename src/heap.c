#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Node* node_create(unsigned char byte, unsigned long freq, Node *left, Node *right) {
    Node *n = malloc(sizeof(Node));
    n->byte = byte;
    n->freq = freq;
    n->left = left;
    n->right = right;
    return n;
}

MinHeap* heap_create(int capacity) {
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->items = malloc(sizeof(Node*) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heap_free(MinHeap *heap) {
    free(heap->items);
    free(heap);
}

int heap_size(MinHeap *heap) {
    return heap->size;
}


static void sift_up(MinHeap *heap, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->items[parent]->freq <= heap->items[i]->freq) {
            break; 
        }

        // swap
        Node *temp = heap->items[parent];
        heap->items[parent] = heap->items[i];
        heap->items[i] = temp;
        i = parent;
    }
}

void heap_push(MinHeap *heap, Node *node) {
    if (heap->size >= heap->capacity) {
        printf("Heap overflow\n");
        return;
    }
    heap->items[heap->size] = node;
    sift_up(heap, heap->size);
    heap->size++;
}


static void sift_down(MinHeap *heap, int i) {
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->items[left]->freq < heap->items[smallest]->freq) {
            smallest = left;
        }
        if (right < heap->size && heap->items[right]->freq < heap->items[smallest]->freq) {
            smallest = right;
        }
        if (smallest == i) {
            break; 
        }
        
        Node *temp = heap->items[i];
        heap->items[i] = heap->items[smallest];
        heap->items[smallest] = temp;
        i = smallest;
    }
}

Node* heap_pop(MinHeap *heap) {
    if (heap->size == 0) {
        return NULL;
    }
    Node *min = heap->items[0];
    heap->size--;
    heap->items[0] = heap->items[heap->size]; 
    sift_down(heap, 0);
    return min;
}
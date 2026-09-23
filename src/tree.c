#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node* build_tree(unsigned long freq_table[256]) {
    MinHeap *heap = heap_create(512);

    for (int i = 0; i < 256; i++) {
        if (freq_table[i] > 0) {
            heap_push(heap, node_create((unsigned char)i, freq_table[i], NULL, NULL));
        }
    }

    if (heap_size(heap) == 1) {
        Node *only = heap_pop(heap);
        Node *root = node_create(0, only->freq, only, NULL);
        heap_free(heap);
        return root;
    }

    while (heap_size(heap) > 1) {
        Node *left = heap_pop(heap);
        Node *right = heap_pop(heap);
        Node *parent = node_create(0, left->freq + right->freq, left, right);
        heap_push(heap, parent);
    }

    Node *root = heap_pop(heap);
    heap_free(heap);
    return root;
}

static void generate_codes_helper(Node *node, char *codes[256], char *buffer, int depth) {
    if (node->left == NULL && node->right == NULL) {
        buffer[depth] = '\0';
        codes[node->byte] = strdup(buffer);
        return;
    }

    if (node->left != NULL) {
        buffer[depth] = '0';
        generate_codes_helper(node->left, codes, buffer, depth + 1);
    }
    if (node->right != NULL) {
        buffer[depth] = '1';
        generate_codes_helper(node->right, codes, buffer, depth + 1);
    }
}

void generate_codes(Node *root, char *codes[256]) {
    for (int i = 0; i < 256; i++) {
        codes[i] = NULL;
    }
    char buffer[256];
    generate_codes_helper(root, codes, buffer, 0);
}

void free_tree(Node *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
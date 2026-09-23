#ifndef TREE_H
#define TREE_H

#include "heap.h"

Node* build_tree(unsigned long freq_table[256]);
void generate_codes(Node *root, char *codes[256]);
void free_tree(Node *root);

#endif
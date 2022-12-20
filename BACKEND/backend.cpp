#include "backend.h"

void tree_backend_ctor (struct Tree* tree)
{
    tree_ctor (tree);

    char* buffer = tree->buffer_language->file_buffer;
    tree->root = node_reverse_frontend_creater (tree, nullptr, &buffer);
    tree_reverse_frontend_creater (tree, &buffer);  
}


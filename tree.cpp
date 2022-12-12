#include "tree.h"

void tree_ctor (struct Tree* tree)
{
    assert (tree);
    
    tree->size = 0;
    tree->code_error = 0;

    if (BufferCreater (tree->file_function, tree->buffer_function) != GOOD_WORKING)
    {
        printf ("Error BufferCreater in tree.cpp on line = %d", __LINE__);
        tree->code_error |= TREE_ERROR_BUFFER_CREATER;
        abort ();
    }

    char* file_buffer = tree->buffer_function->file_buffer;

    tree->root = GetG (&tree->buffer_function->file_buffer, tree);

    tree->buffer_function->file_buffer = file_buffer;
}

void tree_dtor (struct Tree* tree)
{
    assert (tree);

    if (tree->buffer_function != nullptr)
    {
        TextDtor (tree->buffer_function);
    }
    if (tree->file_function != nullptr)
    {
        tree->file_function->file_name = nullptr;
    }

    knot_dtor (tree->root);

    tree->root = nullptr;
    tree->code_error = DTOR_SIZE_T;
    tree->size = DTOR_SIZE_T;

}

void knot_dtor (struct Knot* current_knot)
{
    assert (current_knot);

    if (current_knot->left != nullptr) 
    {
        knot_dtor (current_knot->left);
    }
    if (current_knot->right != nullptr) 
    {
        knot_dtor (current_knot->right);
    }

    current_knot->prev = nullptr;
    current_knot->right = nullptr;
    current_knot->left = nullptr;

}
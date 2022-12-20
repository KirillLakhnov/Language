#ifndef REVERSE_FRONTEND_H
#define REVERSE_FRONTEND_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <locale.h>

#include "../tree.h"
#include "../DSL.h"
#include "../libraries/stack.h"

void tree_reverse_frontend_ctor (struct Tree* tree);

void tree_reverse_frontend_creater (struct Tree* tree, char** current_position);

Node* node_reverse_frontend_creater (struct Tree* tree, struct Node* prev, char** current_position);

void tree_print_on_language (FILE* language_tree, struct Node* root);

//=================================================================

void skip_space (char** current_position);

#endif // REVERSE_FRONTEND_H
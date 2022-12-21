#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <locale.h>

#include "../tree.h"
#include "../DSL.h"
#include "../libraries/stack.h"

void tree_fronted_ctor (struct Tree* tree);

Stack* tokinization (struct Tree* tree, char* language_file, size_t size_file);

//=====================================================================

Node* GetG (struct Tree* tree, struct Stack* token_tree);

void GetAfterCommaPoint (struct Tree* tree, struct Stack* token_tree, int* index, struct Node* NODE);

void GetAfterGlobal (struct Tree* tree, struct Stack* token_tree, int* index, struct Node* NODE);

Node* GetGlobal (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetFunc (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetWhile (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetIf (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetRet (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetCallVoid (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetIn (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetOut (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetDeclaringVar (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetAssignVar (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetCallType (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetE (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetT (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetP (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetMathFunc (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetV (struct Tree* tree, struct Stack* token_tree, int* index);

Node* GetN (struct Tree* tree, struct Stack* token_tree, int* index);

//=====================================================================

void tree_standart_print (FILE* language_tree, struct Node* root);

//=====================================================================

void listing_token (Stack* token_tree);

#endif // PARSER_H
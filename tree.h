#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "enum.h"
#include "libraries/FileProcessing.h"
#include "libraries/common.h"

const double POISON_VALUE = NAN;
const size_t MAX_LEN_STR = 300;
const size_t DTOR_SIZE_T = 0xBABADEDA;
const int DTOR_INT = 0xBABADEAD;

enum TREE_ERROR
{
    TREE_ERROR_SYNTAX_IN_BASE         = 1 << 0,
    TREE_WRONG_NAME_DATA_BASE         = 1 << 1,
    TREE_ERROR_POINTER_STRUCT_NULL    = 1 << 2,
    TREE_ERROR_POINTER_ROOT_NULL      = 1 << 3,
    TREE_ERROR_POINTER_BUFFER_NULL    = 1 << 4,
    TREE_ERROR_POINTER_FILE_INFO_NULL = 1 << 5,
    TREE_ERROR_SIZE_SMALLER_ZERO      = 1 << 6,
    TREE_ERROR_SYNTAX_IN_TREE         = 1 << 7,

    TREE_ERROR_CALLOC         = 1 << 8,
    TREE_ERROR_STRCPY         = 1 << 9,
    TREE_ERROR_BUFFER_CREATER = 1 << 10,
};

struct Knot
{
    struct Knot* prev;

    struct Knot* right;
    struct Knot* left;
};

struct Tree 
{
    struct FileInfo* file_function;
    struct Text* buffer_function;

    struct Knot* root;

    size_t size;
    size_t code_error;
};

void tree_ctor (struct Tree* tree);

void tree_dtor (struct Tree* tree);

void knot_dtor (struct Knot* current_knot);

#endif TREE_H
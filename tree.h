#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "enum.h"
#include "FRONTEND/parser.h"
#include "libraries/FileProcessing.h"
#include "libraries/common.h"
#include "libraries/stack.h"

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

enum TYPE {
    VALUE     = 1,
    VARIABLE  = 2,

    OPERATION = 3,
    SEPARATOR = 4,
    FUNCTION  = 5,

    TYPE_FUNC = 6,

    PARAM = 7,
    NIL   = 8,
    ST    = 9,
    FUNC  = 10,
};

enum OP_TYPE {
    ADD    = 1,
    SUB    = 2,
    MUL    = 3,
    DIV    = 4,
    POW    = 5,
    SIN    = 6,
    COS    = 7,
    ASSIGN = 8,
    IF     = 9,
    ELSE   = 10,
    WHILE  = 11,
    RETURN = 12,
};

enum SEPARATOR_TYPE {
    OPEN_STANDART_BRACKET  = 1,
    OPEN_CURLY_BRACKET     = 2,
    CLOSE_STANDART_BRACKET = 3,
    CLOSE_CURLY_BRACKET    = 4,

    COMMA_POINT = 5,
    COMMA       = 6,
};

enum FUNCTION_TYPE {
    PRINTF = 1,
    SCANF  = 2,
};

enum TYPE_FUNC_TYPE {
    VOID = 1,
    TYPE = 2,
    VAR  = 3,
};

struct Node
{
    struct Node* prev;

    struct Node* right;
    struct Node* left;

    enum TYPE type;

    union
    {
        enum OP_TYPE op_type;
        enum SEPARATOR_TYPE separator_type;
        enum FUNCTION_TYPE function_type;
        enum TYPE_FUNC_TYPE type_func_type;

        double value;
        char* variable;
    };

    int number_line;
};

struct Tree 
{
    struct FileInfo* file_language;
    struct Text* buffer_language;

    struct Node* root;

    size_t size;
    size_t code_error;
};

void tree_ctor (struct Tree* tree);

void tree_dtor (struct Tree* tree);

void node_dtor (struct Node* current_node);

//=====================================================================

Node* node_creater (Node* prev, Node* left, Node* right, enum TYPE type);

Node* node_op_creater (Node* prev, Node* left, Node* right, enum OP_TYPE op_type);

Node* node_signs_creater (Node* prev, Node* left, Node* right, enum SEPARATOR_TYPE separator_type);

Node* node_func_creater (Node* prev, Node* left, Node* right, enum FUNCTION_TYPE function_type);

Node* node_val_creater (Node* prev, Node* left, Node* right, double value);

Node* node_var_creater (Node* prev, Node* left, Node* right, char* variable);

Node* node_type_func_creater (Node* prev, Node* left, Node* right, enum TYPE_FUNC_TYPE type);

//=====================================================================

void knot_graph (struct Tree* tree, struct Node* current_node, FILE* tree_log_graph, int* count);

int tree_graph_dump (struct Tree* tree);

#endif // TREE_H
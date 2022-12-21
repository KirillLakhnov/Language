#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <locale.h>

#include "../tree.h"
#include "../DSL.h"
#include "../libraries/stack.h"

const size_t MAX_NUM_VAR = 100;
const size_t MAX_NUM_FUNC = 100;

enum INIT_VAR
{
    VAR_NO_INIT = 0,
    VAR_INIT    = 1,
};

struct RAM
{
    struct Variable* global_var;
    struct Function* function;

    size_t num_global_var;
    size_t num_func;

    size_t num_free_place;
};

struct Variable
{
    char* name;
    enum INIT_VAR initialization;
    double value;

    int ram_place;
};

struct Function
{
    char* name;
    enum TYPE_FUNC_TYPE type;

    struct Variable var_func[MAX_NUM_VAR];
    size_t num_var;
};

int tree_backend_ctor (struct Tree* tree);

int transfer_to_asm (FILE* asm_code, struct Node* node, struct Tree* tree);

int get_param_func (Node* node, Function* current_func, struct Tree* tree);

int get_func_body (Node* node, Function* current_func, struct Tree* tree, FILE* asm_code);

int get_out_param (Node* NODE, Function* current_func, Tree* tree, FILE* asm_code);

int get_in_param (Node* NODE, Function* current_func, Tree* tree, FILE* asm_code);

int get_call_param (Node* NODE, Function* current_func, Function* call, Tree* tree, FILE* asm_code, int call_number);

//=================================================================
void tree_backend_creater (struct Tree* tree, char** current_position);

Node* node_backend_creater (struct Tree* tree, struct Node* prev, char** current_position);

//=================================================================

Stack* path_node_to_root (Node* NODE);

int is_global_var (Node* NODE);

int is_from_param (Node* NODE);

int find_name_global_var (struct Tree* tree, char* name);

int find_name_function_var (struct Function* func, char* name);

int is_announced_var (struct Function* func, struct Tree* tree, char* name);

Variable* find_func_var (struct Function* func, struct Tree* tree, char* name);

Function* find_func (struct Tree* tree, char* name);

Node* find_eq_node (struct Node* NODE);

int main_find (struct Node* node);

int find_name_function (struct Tree* tree, char* name);

Variable* var_function_copy (Function* func);

#endif // BACKEND_H

#include "tree.h"

void tree_ctor (struct Tree* tree)
{
    assert (tree);
    
    tree->size = 0;
    tree->code_error = 0;

    if (BufferCreater (tree->file_language, tree->buffer_language) != GOOD_WORKING)
    {
        printf ("Error BufferCreater in tree.cpp on line = %d", __LINE__);
        tree->code_error |= TREE_ERROR_BUFFER_CREATER;
        abort ();
    }
}

void tree_dtor (struct Tree* tree)
{
    assert (tree);

    if (tree->buffer_language != nullptr)
    {
        TextDtor (tree->buffer_language);
    }
    if (tree->file_language != nullptr)
    {
        tree->file_language->file_name = nullptr;
    }

    node_dtor (tree->root);

    tree->root = nullptr;
    tree->code_error = DTOR_SIZE_T;
    tree->size = DTOR_SIZE_T;

}

void node_dtor (struct Node* current_node)
{
    assert (current_node);

    if (current_node->left != nullptr) 
    {
        node_dtor (current_node->left);
    }
    if (current_node->right != nullptr) 
    {
        node_dtor (current_node->right);
    }

    current_node->prev = nullptr;
    current_node->right = nullptr;
    current_node->left = nullptr;
}

//=====================================================================

Node* node_creater (Node* prev, Node* left, Node* right, enum TYPE type)
{
    Node* current_node = (Node*) calloc (1, sizeof (Node));

    current_node->prev  = prev;
    current_node->left  = left;
    current_node->right = right;

    current_node->type = type;

    return current_node;
}

Node* node_op_creater (Node* prev, Node* left, Node* right, enum OP_TYPE op_type)
{
    Node* current_node = node_creater (prev, left, right, OPERATION);

    current_node->op_type = op_type;

    return current_node;
}

Node* node_signs_creater (Node* prev, Node* left, Node* right, enum SEPARATOR_TYPE separator_type)
{
    Node* current_node = node_creater (prev, left, right, SEPARATOR);

    current_node->separator_type = separator_type;

    return current_node;
}

Node* node_func_creater (Node* prev, Node* left, Node* right, enum FUNCTION_TYPE function_type)
{
    Node* current_node = node_creater (prev, left, right, FUNCTION);

    current_node->function_type = function_type;

    return current_node;
}

Node* node_val_creater (Node* prev, Node* left, Node* right, double value)
{
    Node* current_node = node_creater (prev, left, right, VALUE);

    current_node->value = value;

    return current_node;
}

Node* node_var_creater (Node* prev, Node* left, Node* right, char* variable)
{
    Node* current_node = node_creater (prev, left, right, VARIABLE);

    current_node->variable = variable;

    return current_node;
}

Node* node_type_func_creater (Node* prev, Node* left, Node* right, enum TYPE_FUNC_TYPE type)
{
    Node* current_node = node_creater (prev, left, right, TYPE_FUNC);

    current_node->type_func_type = type;

    return current_node;
}

//=====================================================================

void knot_graph (struct Tree* tree, struct Node* current_node, FILE* tree_log_graph, int* count)
{
    assert (tree);
    assert (tree_log_graph);

    if (current_node == nullptr)
    {
        return;
    }
    (*count)++;

    if (current_node->right == nullptr && current_node->left == nullptr)
    {
        if (current_node->type == OPERATION)
        {
            char operation[MAX_LEN_CMD] = {0};
            #define DEF_OP(name, length, global_type, OP)   if (current_node->op_type == OP)        \
                                                            {                                       \
                                                                strcpy (operation, #OP);            \
                                                            }
            #define DEF_FUNC(name, length, global_type, OP)
            #define DEF_SEP(name, length, global_type, OP)
            #define DEF_TYPE(name, length, global_type, OP)

            #include "code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE
            
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#ee9b52\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %s | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, operation, current_node->right);
        }
        else if (current_node->type == VALUE)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#ee9b52\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %lf | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->value, current_node->right);
        }
        else if (current_node->type == FUNCTION)
        {
            char function[MAX_LEN_CMD] = {0};
            #define DEF_FUNC(name, length, global_type, FUNC)   if (current_node->function_type == FUNC)    \
                                                                {                                           \
                                                                    strcpy (function, #FUNC);               \
                                                                }
            #define DEF_OP(name, length, global_type, OP)
            #define DEF_SEP(name, length, global_type, OP)
            #define DEF_TYPE(name, length, global_type, OP)

            #include "code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE

            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#ee9b52\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %s | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, function, current_node->right);
        }
        else if (current_node->type == VARIABLE)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#ee9b52\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %s | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->variable, current_node->right);
        }
        else if (current_node->type == SEPARATOR)
        {
            char separation[MAX_LEN_CMD] = {0};
            #define DEF_SEP(name, length, global_type, FUNC)   if (current_node->separator_type == FUNC)    \
                                                                {                                          \
                                                                    strcpy (separation, #FUNC);            \
                                                                }
            #define DEF_OP(name, length, global_type, OP)
            #define DEF_FUNC(name, length, global_type, OP)
            #define DEF_TYPE(name, length, global_type, OP)

            #include "code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#ee9b52\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %s | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, separation, current_node->right);
        }
        else if (current_node->type == TYPE_FUNC)
        {
            char type[MAX_LEN_CMD] = {0};
            #define DEF_TYPE(name, length, global_type, FUNC)   if (current_node->type_func_type == FUNC)    \
                                                                {                                          \
                                                                    strcpy (type, #FUNC);            \
                                                                }
            #define DEF_OP(name, length, global_type, OP)
            #define DEF_FUNC(name, length, global_type, OP)
            #define DEF_SEP(name, length, global_type, OP)

            #include "code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE

            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#ee9b52\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %s | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, type, current_node->right);
        }
        else if (current_node->type == NIL)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#ee9b52\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| NIL | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->right);
        }
        else if (current_node->type == ST)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#ee9b52\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| ST | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->right);
        }
        else if (current_node->type == PARAM)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#ee9b52\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| PARAM | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->right);
        }
        else if (current_node->type == FUNC)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#ee9b52\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| FUNC | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->right);
        }
    }
    else 
    {
        if (current_node->type == OPERATION)
        {
            char operation[MAX_LEN_CMD] = {0};

            #define DEF_OP(name, length, global_type, OP)   if (current_node->op_type == OP)        \
                                                            {                                       \
                                                                strcpy (operation, #OP);            \
                                                            }
            #define DEF_FUNC(name, length, global_type, OP)
            #define DEF_SEP(name, length, global_type, OP)
            #define DEF_TYPE(name, length, global_type, OP)

            #include "code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE

            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#87CEFA\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %s | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, operation, current_node->right);
        }
        else if (current_node->type == VALUE)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#87CEFA\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %lf | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->value, current_node->right);
        }
        else if (current_node->type == FUNCTION)
        {
            char function[MAX_LEN_CMD] = {0};
            #define DEF_FUNC(name, length, global_type, FUNC)   if (current_node->function_type == FUNC)    \
                                                                {                                           \
                                                                    strcpy (function, #FUNC);               \
                                                                }
            #define DEF_OP(name, length, global_type, OP)
            #define DEF_SEP(name, length, global_type, OP)
            #define DEF_TYPE(name, length, global_type, OP)

            #include "code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE

            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#87CEFA\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %s | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, function, current_node->right);
        }
        else if (current_node->type == VARIABLE)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#87CEFA\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %s | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->variable, current_node->right);
        }
        else if (current_node->type == SEPARATOR)
        {
            char separation[MAX_LEN_CMD] = {0};
            #define DEF_SEP(name, length, global_type, FUNC)   if (current_node->separator_type == FUNC)    \
                                                                {                                          \
                                                                    strcpy (separation, #FUNC);            \
                                                                }
            #define DEF_OP(name, length, global_type, OP)
            #define DEF_FUNC(name, length, global_type, OP)
            #define DEF_TYPE(name, length, global_type, OP)

            #include "code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE

            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#87CEFA\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %s | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, separation, current_node->right);
        }
        else if (current_node->type == TYPE_FUNC)
        {
            char type[MAX_LEN_CMD] = {0};
            #define DEF_TYPE(name, length, global_type, FUNC)   if (current_node->type_func_type == FUNC)    \
                                                                {                                          \
                                                                    strcpy (type, #FUNC);            \
                                                                }
            #define DEF_OP(name, length, global_type, OP)
            #define DEF_FUNC(name, length, global_type, OP)
            #define DEF_SEP(name, length, global_type, OP)

            #include "code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE

            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#87CEFA\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| %s | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, type, current_node->right);
        }
        else if (current_node->type == NIL)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#87CEFA\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| NIL | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->right);
        }
        else if (current_node->type == ST)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#87CEFA\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| ST | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->right);
        }
        else if (current_node->type == PARAM)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#87CEFA\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| PARAM | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->right);
        }
        else if (current_node->type == FUNC)
        {
            fprintf(tree_log_graph, "\t\"%p\" [shape = \"record\", style = \"rounded, filled\", fontname = \"Helvetica-Bold\", fillcolor = \"#87CEFA\","
		                            "\n\t\tlabel = \"prev = %p \\lcurrent = %p | {<left> left = %p| FUNC | <right> right = %p}\"]\n", 
                                    current_node, current_node->prev, current_node, current_node->left, current_node->right);
        }
    }

    if (current_node->left != nullptr)
    {
        fprintf(tree_log_graph, "\t \"%p\" -> \"%p\" [style = \"bold\"]\n", current_node, current_node->left);
    }

    if (current_node->right != nullptr)
    {
        fprintf(tree_log_graph, "\t \"%p\" -> \"%p\" [style = \"bold\"]\n", current_node, current_node->right);
    }

    if (current_node->left  != nullptr) 
    {
        knot_graph(tree, current_node->left, tree_log_graph, count);
    }

    if (current_node->right != nullptr) 
    {
        knot_graph(tree, current_node->right, tree_log_graph, count); 
    }
}

int tree_graph_dump (struct Tree* tree)
{
    assert (tree);

    static int number_of_function_launches = 0;

    FILE* tree_log_graph = fopen ("graph/graph_log_tree.dot", "w");

    fprintf (tree_log_graph, "digraph G\n{\n");
    fprintf (tree_log_graph, "\tgraph [dpi = 250];\n");
    fprintf (tree_log_graph, "\trankdir = TB;\n");

    int count = 0;
    knot_graph (tree, tree->root, tree_log_graph, &count);

    fprintf (tree_log_graph, "\n}");

    fclose (tree_log_graph);

    char command[MAX_LEN_STR] = "";
    sprintf (command, "dot -Tpng -ograph/graph_log_tree_%d.png graph/graph_log_tree.dot", number_of_function_launches);

    system(command);

    FILE* htm_log_file = fopen ("graph/htm_log_file.htm", "a");

    fprintf (htm_log_file, "<pre>\n");
    fprintf (htm_log_file, "<img src = \"graph_log_tree_%d.png\">", number_of_function_launches);
    fprintf (htm_log_file, "<hr>\n");

    fclose(htm_log_file);

    number_of_function_launches++;

    return number_of_function_launches - 1;
}
#include "reverse_frontend.h"

void tree_reverse_frontend_ctor (struct Tree* tree)
{
    tree_ctor (tree);

    char* buffer = tree->buffer_language->file_buffer;
    tree->root = node_reverse_frontend_creater (tree, nullptr, &buffer);

    tree_reverse_frontend_creater (tree, &buffer);

    tree_graph_dump (tree);

    FILE* language_file = fopen ("language_file_from_tree.txt", "wb");
    int table_index = 0;
    tree_print_on_language (language_file, tree->root, &table_index);
    fclose (language_file);
}

void tree_print_on_language (FILE* language_tree, struct Node* root, int* table_index)
{
    assert (language_tree);

    if (root == nullptr)
    {
        return;
    }
    
    switch (root->type)
    {
        case (ST):
        {
            tree_print_on_language (language_tree, L(root), table_index);
            tree_print_on_language (language_tree, R(root), table_index);
            break;
        }
        case (PARAM):
        {
            tree_print_on_language (language_tree, L(root), table_index);
            if (R(root)->type != NIL)
            {
                fprintf (language_tree, ", ");
            }
            tree_print_on_language (language_tree, R(root), table_index);
            break;
        }
        case (FUNC):
        {
            tree_print_on_language (language_tree, LR(root), table_index);
            fprintf (language_tree, "%s (", L(root)->variable);
            tree_print_on_language (language_tree, LL(root), table_index);
            fprintf (language_tree, ")\n");
            fprintf (language_tree, "{\n");
            (*table_index)++;
            tree_print_on_language (language_tree, R(root), table_index);
            fprintf (language_tree, "}\n");
            (*table_index)--;
            break;
        }
        case (CALL):
        {
            table_printf (language_tree, *table_index);
            fprintf (language_tree, "%s (", root->left->variable);
            tree_print_on_language (language_tree, LL(root), table_index);
            fprintf (language_tree, ");\n");
            break;
        }
        case (NIL):
        {
            break;
        }
        case (TYPE_FUNC):
        {
            switch (root->type_func_type)
            {   
                //==========
                case (VAR):
                {
                    if (P(root) != nullptr && P(root)->type != PARAM)
                    {
                        table_printf (language_tree, *table_index);
                    }

                    fprintf (language_tree, "var ");
                    tree_print_on_language (language_tree, L(root), table_index);
                    if (root->right->type != NIL)
                    {
                        fprintf (language_tree, " = ");
                        tree_print_on_language (language_tree, R(root), table_index);
                    }
                    if (root->prev != nullptr && root->prev->type != PARAM)
                    {
                        fprintf (language_tree, ";\n");
                    }
                    break;
                }
                //=========
                case (VOID): 
                {
                    table_printf (language_tree, *table_index);
                    fprintf (language_tree, "void ");
                    break;
                }
                case (TYPE): 
                {
                    table_printf (language_tree, *table_index);
                    fprintf (language_tree, "type ");
                    break;
                }
            }
            break;
        }
        case (VALUE):
        {
            fprintf (language_tree, "%lg", root->value);
            break;
        }
        case (VARIABLE):
        {
            fprintf (language_tree, "%s", root->variable);
            break;
        }
        case (OPERATION):
        {
            switch (root->op_type)
            {
                case (ADD):
                {
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, " + ");
                    tree_print_on_language (language_tree, R(root), table_index);
                    break;
                }
                case (SUB):
                {
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, " - ");
                    tree_print_on_language (language_tree, R(root), table_index);
                    break;
                }
                case (MUL):
                {
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, " * ");
                    tree_print_on_language (language_tree, R(root), table_index);
                    break;
                }
                case (DIV):
                {
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, " / ");
                    tree_print_on_language (language_tree, R(root), table_index);
                    break;
                }
                case (EQ):
                {
                    table_printf (language_tree, *table_index);
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, " = ");
                    tree_print_on_language (language_tree, R(root), table_index);
                    fprintf (language_tree, ";\n");
                    break;
                }
                case (SIN):
                {
                    fprintf (language_tree, "sin (");
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, ")");
                    break;
                }
                case (COS):
                {
                    fprintf (language_tree, "cos (");
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, ")");
                    break;
                }
                case (POW):
                {   
                    fprintf (language_tree, "pow (");
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, ", ");
                    tree_print_on_language (language_tree, R(root), table_index);
                    fprintf (language_tree, ")");
                    break;
                }
                case (IF):
                {
                    table_printf (language_tree, *table_index);
                    fprintf (language_tree, "if (");
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, ")\n");
                    table_printf (language_tree, *table_index);

                    if (R(root)->type == ST)
                    {
                        fprintf (language_tree, "{\n");
                        (*table_index)++;
                        //========
                        tree_print_on_language (language_tree, R(root), table_index);
                        //=======
                        (*table_index)--;
                        table_printf (language_tree, *table_index);
                        fprintf (language_tree, "}\n");
                    }
                    else
                    {
                        fprintf (language_tree, "{\n");
                        (*table_index)++;
                        //========
                        tree_print_on_language (language_tree, RL(root), table_index);
                        //========
                        (*table_index)--;
                        table_printf (language_tree, *table_index);
                        fprintf (language_tree, "}\n");
                        table_printf (language_tree, *table_index);
                        fprintf (language_tree, "else\n");
                        table_printf (language_tree, *table_index);
                        fprintf (language_tree, "{\n");
                        (*table_index)++;
                        //========
                        tree_print_on_language (language_tree, RR(root), table_index);
                        //========
                        (*table_index)--;
                        table_printf (language_tree, *table_index);
                        fprintf (language_tree, "}\n");
                    }
                    break;
                }
                case (WHILE):
                {
                    table_printf (language_tree, *table_index);
                    fprintf (language_tree, "while (");
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, ")\n");
                    table_printf (language_tree, *table_index);
                    fprintf (language_tree, "{\n");
                    (*table_index)++;
                    //=========
                    tree_print_on_language (language_tree, R(root), table_index);
                    //=========
                    (*table_index)--;
                    table_printf (language_tree, *table_index);
                    fprintf (language_tree, "}\n");
                    break;
                }
                case (RET):
                {
                    table_printf (language_tree, *table_index);
                    fprintf (language_tree, "return");
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, ";\n");
                    break;  
                }  
            }
            break;
        }
        case (FUNCTION):
        {
            switch (root->function_type)
            {
                case (IN):
                {
                    table_printf (language_tree, *table_index);
                    fprintf (language_tree, "scanf (");
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, ");\n");
                    break;
                }
                case (OUT):
                {
                    table_printf (language_tree, *table_index);
                    fprintf (language_tree, "printf (");
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, ");\n");
                    break;
                }
            }
            break;
        }
    }
}

//=====================================================================

void tree_reverse_frontend_creater (struct Tree* tree, char** current_position)
{
    FILE* base = fopen (tree->file_language->file_name, "rb");
    if (base == nullptr)
    {
        printf ("Error fopen in tree.cpp on line = %d", __LINE__);
        tree->code_error |= TREE_WRONG_NAME_DATA_BASE;
        abort ();
    }

    Node* NODE = tree->root;

    char bracket[2] = {0};

    while (tree->buffer_language->file_buffer + tree->buffer_language->size_buffer > *current_position)
    {
        int lenght = 0;
        if (sscanf (*current_position, "%s %n", bracket, &lenght) != 1)
        {
            printf ("Error sscanf in tree.cpp on line = %d", __LINE__);
            tree->code_error |= TREE_ERROR_SYNTAX_IN_BASE; 
            abort ();
        }

        if (strcmp (bracket, "{") == 0)
        {
            struct Node* new_knot = node_reverse_frontend_creater (tree, NODE, current_position);
            if (new_knot == nullptr)
            {
                return;
            }

            LNODE = new_knot;
            NODE = new_knot;
        }
        else if (strcmp (bracket, "}") == 0)
        {
            *current_position += lenght;
            NODE = PNODE;
            sscanf (*current_position, "%s%n", bracket, &lenght);
            
            if (strcmp (bracket, "{") == 0)
            {
                struct Node* new_knot = node_reverse_frontend_creater (tree, NODE, current_position);
                if (new_knot == nullptr)
                {
                    return;
                }

                RNODE = new_knot;
                NODE = new_knot;
            }
        }
        else
        {
            tree->code_error |= TREE_ERROR_SYNTAX_IN_BASE; 
            abort ();
        }
    }

    fclose (base);
}

Node* node_reverse_frontend_creater (struct Tree* tree, struct Node* prev, char** current_position)
{
    struct Node* NODE = (Node*) calloc (1, sizeof (Node));
    if (NODE == nullptr)
    {
        printf ("Error calloc in tree.cpp on line = %d", __LINE__);
        tree->code_error |= TREE_ERROR_CALLOC;
        abort ();
    }

    tree->size++;
    
    NODE->prev = prev;
    NODE->left = nullptr;
    NODE->right = nullptr;

    *current_position = strchr (*current_position, '{') + 1;
    if (*current_position == nullptr)
    {
        printf ("Error syntax in tree.cpp on line = %d", __LINE__);
        tree->code_error |= TREE_ERROR_SYNTAX_IN_BASE;
        abort();
    }

    char* command = (char*) calloc (MAX_LEN_CMD, sizeof(char));
    int len_cmd = 0;

    sscanf (*current_position, "%s %n", command, &len_cmd);
    *current_position += len_cmd;

    if (strcmp (command, "ST") == 0)
    {
        NODE->type = ST;
    }
    else if (strcmp (command, "PARAM") == 0)
    {
        NODE->type = PARAM;
    }
    else if (strcmp (command, "NIL") == 0)
    {
        NODE->type = NIL;
    }
    else if (strcmp (command, "FUNC") == 0)
    {
        NODE->type = FUNC;
    }
    else if (strcmp (command, "CALL") == 0)
    {
        NODE->type = CALL;
    }
    else if (*command == '\"')
    {
        NODE->type = VARIABLE;

        char* close_mark = strchr (command + 1, '\"');
        if (close_mark == nullptr)
        {
            printf ("Error syntax in tree.cpp on line = %d", __LINE__);
            tree->code_error |= TREE_ERROR_SYNTAX_IN_BASE;
            abort();
        }
        *close_mark = '\0';

        NODE->variable = strdup (command + 1);
    }
    else if (isdigit (*command))
    {
        char* command_new = nullptr;
        double value = strtod (command, &command_new);

        NODE->type = VALUE;
        NODE->value = value;
    }
    else if (strcmp (command, "Void") == 0)
    {
        NODE->type = TYPE_FUNC;
        NODE->type_func_type = VOID;
    }
    else if (strcmp (command, "Type") == 0)
    {
        NODE->type = TYPE_FUNC;
        NODE->type_func_type = TYPE;
    }
    else if (strcmp (command, "VAR") == 0)
    {
        NODE->type = TYPE_FUNC;
        NODE->type_func_type = VAR;
    }
    else if (strcmp (command, "IN") == 0)
    {
        NODE->type = FUNCTION;
        NODE->function_type = IN;
    }
    else if (strcmp (command, "OUT") == 0)
    {
        NODE->type = FUNCTION;
        NODE->function_type = OUT;
    }

    else

    #define DEF_OP(str_name, length, global_type, sub_type) if (strcmp (command, #sub_type) == 0)   \
                                                            {                                       \
                                                                NODE->type = OPERATION;             \
                                                                NODE->op_type = sub_type;           \
                                                            }                                       \

    #define DEF_FUNC(str_name, length, global_type, sub_type)
    #define DEF_TYPE(str_name, length, global_type, sub_type)
    #define DEF_SEP(str_name, length, global_type, sub_type)

    #include "../code_generation.h"

    #undef DEF_OP
    #undef DEF_FUNC
    #undef DEF_TYPE
    #undef DEF_SEP

    free (command);
    return NODE;
}

//=================================================================

void skip_space (char** current_position)
{
    while (isspace (**current_position))
    {
        (*current_position)++;
    }
}

void table_printf (FILE* file, int number_table)
{
    for (int i = 0; i < number_table; i++)
    {
        fprintf (file, "\t");
    }
}
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
                case (ASSIGN):
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
                case (RETURN):
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
                case (SCANF):
                {
                    table_printf (language_tree, *table_index);
                    fprintf (language_tree, "scanf (");
                    tree_print_on_language (language_tree, L(root), table_index);
                    fprintf (language_tree, ");\n");
                    break;
                }
                case (PRINTF):
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
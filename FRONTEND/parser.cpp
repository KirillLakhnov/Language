#include "parser.h"

void tree_fronted_ctor (struct Tree* tree)
{
    tree_ctor (tree);
    Stack* token_tree = tokinization (tree, tree->buffer_language->file_buffer, tree->buffer_language->size_buffer);

    if (token_tree == nullptr)
    {
        return;
    }

    listing_token (token_tree);

    tree->root = GetG (tree, token_tree);
    if (tree->root == nullptr)
    {
        return;
    }
    tree_graph_dump (tree);

    FILE* language_tree = fopen("language_tree.awp", "wb");

    tree_standart_print (language_tree, tree->root);

    fclose (language_tree);
}

Stack* tokinization (struct Tree* tree, char* language_file, size_t size_file)
{
    Node* NODE = nullptr;

    int number_line = 1;

    Stack* stack_tree = (Stack*) calloc (1, sizeof(Stack));
    StackCtor (stack_tree, 5);

    char* current_symbol = language_file;
    int index = 0;

    while (*current_symbol != '\0')
    {
        number_line += skip_spaces (&current_symbol);
        if (*current_symbol == '\0')
        {
            break;
        }

//=======================================================================================
        if (strncmp ("if", current_symbol, 2) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, IF);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 2;
        }
        else if (strncmp ("else", current_symbol, 4) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, ELSE);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 4;
        }
        else if (strncmp ("while", current_symbol, 5) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, WHILE);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 5;
        }
        else if (strncmp ("return", current_symbol, 6) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, RETURN);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 6;
        }
        else if (strncmp("/*", current_symbol, 2) == 0)
        {
            current_symbol += 2;
            while (strncmp("*/", current_symbol, 2) != 0)
            {
                if (*(current_symbol + 1) == '\0')
                {
                    printf ("Syntax error in %s: absent */, but there is /* on the line %d\n", tree->file_language->file_name, number_line);
                    return nullptr;
                }
                current_symbol++;
            }
            current_symbol += 2;
        }
        else if (strncmp ("+", current_symbol, 1) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, ADD);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 1;
        }
        else if (strncmp ("-", current_symbol, 1) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, SUB);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 1;
        }
        else if (strncmp ("*", current_symbol, 1) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, MUL);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 1;
        }
        else if (strncmp ("/", current_symbol, 1) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, DIV);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 1;
        }
        else if (strncmp ("pow", current_symbol, 3) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, POW);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 3;
        }
        else if (strncmp ("sin", current_symbol, 3) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, SIN);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 3;        
        }
        else if (strncmp ("cos", current_symbol, 3) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, COS); 
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE); 
            current_symbol += 3;     
        }
        else if (strncmp ("=", current_symbol, 1) == 0)
        {
            NODE = node_op_creater (nullptr, nullptr, nullptr, ASSIGN); 
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE); 
            current_symbol += 1;   
        }
//=======================================================================================

        else if (strncmp ("scanf", current_symbol, 5) == 0)
        {
            NODE = node_func_creater (nullptr, nullptr, nullptr, SCANF);  
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 5;   
        }
        else if (strncmp ("printf", current_symbol, 6) == 0)
        {
            NODE = node_func_creater (nullptr, nullptr, nullptr, PRINTF);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 6;   
        }

//=======================================================================================
        else if (strncmp ("(", current_symbol, 1) == 0)
        {
            NODE = node_signs_creater (nullptr, nullptr, nullptr, OPEN_STANDART_BRACKET);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 1;
        }
        else if (strncmp (")", current_symbol, 1) == 0)
        {
            NODE = node_signs_creater (nullptr, nullptr, nullptr, CLOSE_STANDART_BRACKET);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 1;
        }
        else if (strncmp ("{", current_symbol, 1) == 0)
        {
            NODE = node_signs_creater (nullptr, nullptr, nullptr, OPEN_CURLY_BRACKET);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 1;
        }
        else if (strncmp ("}", current_symbol, 1) == 0)
        {
            NODE = node_signs_creater (nullptr, nullptr, nullptr, CLOSE_CURLY_BRACKET);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 1;
        }
        else if (strncmp (",", current_symbol, 1) == 0)
        {
            NODE = node_signs_creater (nullptr, nullptr, nullptr, COMMA);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 1;
        }
        else if (strncmp (";", current_symbol, 1) == 0)
        {
            NODE = node_signs_creater (nullptr, nullptr, nullptr, COMMA_POINT);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 1;
        }
//=======================================================================================

        else if (strncmp ("var", current_symbol, 3) == 0)
        {
            NODE = node_type_func_creater (nullptr, nullptr, nullptr, VAR);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 3;
        }
        else if (strncmp ("void", current_symbol, 4) == 0)
        {
            NODE = node_type_func_creater (nullptr, nullptr, nullptr, VOID);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 4;
        }
        else if (strncmp ("type", current_symbol, 4) == 0)
        {
            NODE = node_type_func_creater (nullptr, nullptr, nullptr, TYPE);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
            current_symbol += 4;
        }
//=======================================================================================
        else if (isdigit (*current_symbol))
        {
            double value = strtod (current_symbol, &current_symbol);
            if (*(current_symbol - 1) == ',')
            {
                current_symbol--;
            }

            NODE = node_val_creater (nullptr, nullptr, nullptr, value);
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
        }
        else if (isalpha (*current_symbol))
        {   
            char* begin_name = current_symbol;

            while ((isalnum (*current_symbol) || (*current_symbol == '_')) && (*current_symbol != '\0'))
            {
                current_symbol++;
            }

            NODE = node_var_creater (nullptr, nullptr, nullptr, strndup(begin_name, current_symbol - begin_name));
            NODE->number_line = number_line;
            StackPush (stack_tree, NODE);
        }
        else
        {
            printf ("Syntax error in %s: unknown command on line %d", tree->file_language->file_name, number_line);
            return nullptr;
        }
        
        index++;
    }

    return stack_tree;
}

//=====================================================================

Node* GetG (struct Tree* tree, struct Stack* token_tree)
{
    assert (tree);
    assert (token_tree);

    int index = 0;

    Node* NODE = GetGlobal (tree, token_tree, &index);
    NULL_CHECK(NODE);

    /*if (index < token_tree->size - 1)
    {
        tree->code_error |= TREE_ERROR_SYNTAX_IN_BASE;
        printf ("syntax error: in Recursive_descent.cpp on %d, code_error = %lu", __LINE__, tree->code_error);
        abort ();
    }*/

    return NODE;
}

void GetAfterGlobal (struct Tree* tree, struct Stack* token_tree, int* index, struct Node* NODE)
{
    if (*index < (token_tree->size - 1))
    {
        RNODE = GetGlobal (tree, token_tree, index);

        if (RNODE == nullptr)
        {
            RNODE = node_creater (NODE, nullptr, nullptr, NIL);
        }
        P(RNODE) = NODE;
    }
    else
    {
        RNODE = node_creater (NODE, nullptr, nullptr, NIL);
        P(RNODE) = NODE;
    }
}

void GetAfterCommaPoint (struct Tree* tree, struct Stack* token_tree, int* index, struct Node* NODE)
{
    if (*index < (token_tree->size - 1))
    {
        RNODE = GetWhile (tree, token_tree, index);

        if (RNODE == nullptr)
        {
            RNODE = node_creater (NODE, nullptr, nullptr, NIL);
        }
        P(RNODE) = NODE;
    }
    else
    {
        RNODE = node_creater (NODE, nullptr, nullptr, NIL);
        P(RNODE) = NODE;
    }
}

Node* GetGlobal (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;

    if (token_tree->data[*index]->type == TYPE_FUNC &&
        token_tree->data[*index]->type_func_type == VAR)
    {
        int number_line = token_tree->data[*index]->number_line;
        NODE = token_tree->data[*index];

        (*index)++;

        if (token_tree->data[*index]->type == VARIABLE)
        {
            LNODE = token_tree->data[*index];
            P(LNODE) = NODE;

            (*index)++;

            if (*index < (token_tree->size - 1) &&
                token_tree->data[*index]->type == OPERATION && 
                token_tree->data[*index]->op_type == ASSIGN)
            {
                (*index)++;
                RNODE = GetN (tree, token_tree, index);
                if (RNODE != nullptr)
                {
                    P(RNODE) = NODE;
                }
                else
                {
                    return nullptr;
                }
            }
            else
            {
                RNODE = node_creater (NODE, nullptr, nullptr, NIL);
            }

            COMMA_POINT_CHECK(index);
            (*index)++; 

            Node* st_node = node_creater (nullptr, 
                                      NODE,
                                      node_creater (st_node, nullptr, nullptr, NIL), 
                                      ST);
            PNODE = st_node;
            NODE = st_node;

            GetAfterGlobal (tree, token_tree, index, NODE);
        }
        else
        {
            printf ("Syntax error in %s: on line %d there is no variable name after \"var\"\n", tree->file_language->file_name, number_line);
            return nullptr;
        }
    }
    else
    {
        NODE = GetFunc (tree, token_tree, index);
        NULL_CHECK (NODE);
    }

    return NODE;
}

Node* GetFunc (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;
    int number_line = 0;

    if (token_tree->data[*index]->type == TYPE_FUNC &&
        token_tree->data[*index]->type_func_type != VAR)
    {
        Node* type_func = token_tree->data[*index];
        number_line = token_tree->data[*index]->number_line;

        (*index)++;

        if (*index < (token_tree->size) &&
            token_tree->data[*index]->type == VARIABLE)
        {
            NODE = token_tree->data[*index];

            RNODE = type_func;
            P(RNODE) = NODE;

            (*index)++;

            OPEN_STANDART_BRACKET_CHECK (index);
            (*index)++;

            if (*index < (token_tree->size) &&
                token_tree->data[*index]->type == SEPARATOR &&
                token_tree->data[*index]->separator_type == CLOSE_STANDART_BRACKET)
            {
                LNODE = node_creater (NODE, nullptr, nullptr, NIL);
                (*index)++;
            }
            else
            {
                LNODE = node_creater (NODE, nullptr, nullptr, PARAM);
                Node* param_node = LNODE;

                while (1)
                {
                    if (token_tree->data[*index]->type == TYPE_FUNC &&
                        token_tree->data[*index]->type_func_type == VAR)
                    {
                        L(param_node) = token_tree->data[*index];
                        (*index)++;

                        if (token_tree->data[*index]->type == VARIABLE)
                        {
                            LL(param_node) = token_tree->data[*index];
                            LR(param_node) = node_creater (L(param_node), nullptr, nullptr, NIL);

                            (*index)++;

                            if (token_tree->data[*index]->type == SEPARATOR &&
                                token_tree->data[*index]->separator_type == COMMA)
                            {
                                R(param_node) = node_creater (NODE, nullptr, nullptr, PARAM);
                                param_node = R(param_node);
                                (*index)++;
                            }
                            else if (token_tree->data[*index]->type == SEPARATOR &&
                                     token_tree->data[*index]->separator_type == CLOSE_STANDART_BRACKET)
                            {
                                R(param_node) = node_creater (NODE, nullptr, nullptr, NIL);
                                (*index)++;
                                break;
                            }
                            else
                            {
                                printf ("Syntax error in %s: on line %d extra comma \",\" or missing )\n", tree->file_language->file_name, number_line);
                                return nullptr;
                            }
                        }
                        else
                        {
                            printf ("Syntax error in %s: on line %d error name variable\n", tree->file_language->file_name, number_line);
                            return nullptr;
                        }
                    }
                    else
                    {
                        printf ("Syntax error in %s: on line %d no variable declaration\n", tree->file_language->file_name, number_line);
                        return nullptr;
                    }
                }
            }

            Node* func_node = node_creater (nullptr, NODE, nullptr, FUNC);

            OPEN_CURLY_BRACKET_CHECK (index);
            (*index)++;

            R(func_node) = GetWhile (tree, token_tree, index);
            
            CLOSE_CURLY_BRACKET_CHECK (index);
            (*index)++;

            NODE = func_node;

            Node* st_node = node_creater (nullptr, 
                                          NODE,
                                          node_creater (st_node, nullptr, nullptr, NIL), 
                                          ST);
            PNODE = st_node;
            NODE = st_node;
        }
        else
        {
            printf ("Syntax error in %s: on line %d name function absent\n", tree->file_language->file_name, number_line);
            return nullptr;
        }
    }

    GetAfterGlobal (tree, token_tree, index, NODE);

    return NODE;
}

Node* GetWhile (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;
    int number_line = 0;

    if (token_tree->data[*index]->type == OPERATION &&
        token_tree->data[*index]->op_type == WHILE)
    {
        NODE = token_tree->data[*index];
        number_line = token_tree->data[*index]->number_line;

        (*index)++;
        OPEN_STANDART_BRACKET_CHECK (index);
        number_line = token_tree->data[*index]->number_line;
        (*index)++;

        LNODE = GetE (tree, token_tree, index);
        NULL_CHECK (LNODE);
        P(LNODE) = NODE;
        
        CLOSE_STANDART_BRACKET_CHECK (index);
        (*index)++;

        OPEN_CURLY_BRACKET_CHECK (index);
        number_line = token_tree->data[*index]->number_line;
        (*index)++;

        RNODE = GetWhile (tree, token_tree, index);
        NULL_CHECK (RNODE);
        P(RNODE) = NODE;

        CLOSE_CURLY_BRACKET_CHECK (index);
        (*index)++;

        Node* st_node = node_creater (nullptr, 
                                      NODE,
                                      node_creater (st_node, nullptr, nullptr, NIL), 
                                      ST);
        PNODE = st_node;
        NODE = st_node;
    }
    else
    {
        NODE = GetIf (tree, token_tree, index);
        NULL_CHECK (NODE);
    }

    GetAfterCommaPoint (tree, token_tree, index, NODE);

    return NODE;
}

Node* GetIf (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;
    int number_line = 0;

    if (token_tree->data[*index]->type == OPERATION &&
        token_tree->data[*index]->op_type == IF)
    {
        NODE = token_tree->data[*index];
        number_line = token_tree->data[*index]->number_line;

        (*index)++;
        OPEN_STANDART_BRACKET_CHECK (index);
        number_line = token_tree->data[*index]->number_line;
        (*index)++;

        LNODE = GetE (tree, token_tree, index);
        NULL_CHECK (LNODE);
        P(LNODE) = NODE;
        
        CLOSE_STANDART_BRACKET_CHECK (index);
        (*index)++;

        OPEN_CURLY_BRACKET_CHECK (index);
        number_line = token_tree->data[*index]->number_line;
        (*index)++;

        Node* true_node = GetWhile (tree, token_tree, index);
        NULL_CHECK (true_node);

        CLOSE_CURLY_BRACKET_CHECK (index);
        (*index)++;

        if (*index < (token_tree->size - 1) &&
            token_tree->data[*index]->type == OPERATION &&
            token_tree->data[*index]->op_type == ELSE)
        {
            Node* else_node = token_tree->data[*index];
            (*index)++;

            OPEN_CURLY_BRACKET_CHECK (index);
            (*index)++;

            Node* false_node = GetWhile (tree, token_tree, index);
            NULL_CHECK (false_node);

            CLOSE_CURLY_BRACKET_CHECK (index);
            (*index)++;

            RNODE = else_node;
            P(RNODE) = NODE;

            L(RNODE) = true_node;
            P(L(RNODE)) = RNODE;
            R(RNODE) = false_node;
            P(R(RNODE)) = RNODE;
        }
        else
        {
            RNODE = true_node;
            P(RNODE) = NODE;
        }

        Node* st_node = node_creater (nullptr, 
                                      NODE,
                                      node_creater (st_node, nullptr, nullptr, NIL), 
                                      ST);
        PNODE = st_node;
        NODE = st_node;
    }
    else
    {
        NODE = GetRet (tree, token_tree, index);
        NULL_CHECK (NODE);
    }

    return NODE;
}
Node* GetRet (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;
    int number_line = token_tree->data[*index]->number_line;

    if (token_tree->data[*index]->type == OPERATION &&
        token_tree->data[*index]->op_type == RETURN)
    {
        NODE = token_tree->data[*index];
        (*index)++;

        if (*index < (token_tree->size - 1) &&
           (token_tree->data[*index]->type != SEPARATOR ||
            token_tree->data[*index]->separator_type != COMMA_POINT))
        {
            LNODE = GetE (tree, token_tree, index);
            P(LNODE) = NODE;
        }
        else
        {
            LNODE = node_creater (NODE, nullptr, nullptr, NIL);
        }

        RNODE = node_creater (NODE, nullptr, nullptr, NIL);

        COMMA_POINT_CHECK (index);
        (*index)++;

        Node* st_node = node_creater (nullptr, 
                                      NODE,
                                      node_creater (st_node, nullptr, nullptr, NIL), 
                                      ST);
        PNODE = st_node;
        NODE = st_node;
    }
    else
    {
        NODE = GetIn (tree, token_tree, index);
        NULL_CHECK (NODE);
    }

    return NODE;
}

Node* GetIn (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;
    int number_line = token_tree->data[*index]->number_line;

    if (token_tree->data[*index]->type == FUNCTION &&
        token_tree->data[*index]->function_type == SCANF)
    {
        NODE = token_tree->data[*index];
        RNODE = node_creater (NODE, nullptr, nullptr, NIL);

        (*index)++;
        OPEN_STANDART_BRACKET_CHECK (index);
        number_line = token_tree->data[*index]->number_line;
        (*index)++;

        LNODE = node_creater (NODE, nullptr, nullptr, PARAM);
        Node* param_node = LNODE;

        while (1)
        {
            if (token_tree->data[*index]->type == VARIABLE)
            {
                L(param_node) = token_tree->data[*index];
                P(L(param_node)) = param_node;
            }
            else
            {
                printf ("Syntax error in %s: on line %d invalid parameters of the \"scanf\" function\n", tree->file_language->file_name, number_line);
                return nullptr;
            }

            (*index)++;

            if (*index > (token_tree->size - 1))
            {
                printf ("Syntax error in %s: on line %d there is ( , but ) absent\n", tree->file_language->file_name, number_line);
                return nullptr;
            }
            else if (token_tree->data[*index]->type == SEPARATOR &&                                                             
                     token_tree->data[*index]->separator_type == CLOSE_STANDART_BRACKET)
            {
                R(param_node) = node_creater (param_node, nullptr, nullptr, NIL);
                param_node = R(param_node);
                (*index)++;
                break;
            }
            else if (token_tree->data[*index]->type == SEPARATOR &&                                                             
                     token_tree->data[*index]->separator_type == COMMA)
            {
                R(param_node) = node_creater (param_node, nullptr, nullptr, PARAM);
                param_node = R(param_node);
                (*index)++;
            }
            else
            {
                printf ("Syntax error in %s: on line %d there is ( , but ) absent\n", tree->file_language->file_name, number_line);
                return nullptr;
            }
        }

        COMMA_POINT_CHECK(index);
        (*index)++;

        Node* st_node = node_creater (nullptr, 
                                      NODE,
                                      node_creater (st_node, nullptr, nullptr, NIL), 
                                      ST);
        PNODE = st_node;
        NODE = st_node;
    }
    else
    {
        NODE = GetOut (tree, token_tree, index);
        NULL_CHECK (NODE);
    }

    return NODE;
}

Node* GetOut (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;
    int number_line = token_tree->data[*index]->number_line;

    if (token_tree->data[*index]->type == FUNCTION &&
        token_tree->data[*index]->function_type == PRINTF)
    {
        NODE = token_tree->data[*index];
        RNODE = node_creater (NODE, nullptr, nullptr, NIL);

        (*index)++;
        OPEN_STANDART_BRACKET_CHECK (index);
        number_line = token_tree->data[*index]->number_line;
        (*index)++;

        LNODE = node_creater (NODE, nullptr, nullptr, PARAM);
        Node* param_node = LNODE;

        while (1)
        {
            L(param_node) = GetE (tree, token_tree, index);
            P(L(param_node)) = param_node;

            if (*index > (token_tree->size - 1))
            {
                printf ("Syntax error in %s: on line %d there is ( , but ) absent\n", tree->file_language->file_name, number_line);
                return nullptr;
            }
            else if (token_tree->data[*index]->type == SEPARATOR &&                                                             
                     token_tree->data[*index]->separator_type == CLOSE_STANDART_BRACKET)
            {
                R(param_node) = node_creater (param_node, nullptr, nullptr, NIL);
                param_node = R(param_node);
                (*index)++;
                break;
            }
            else if (token_tree->data[*index]->type == SEPARATOR &&                                                             
                     token_tree->data[*index]->separator_type == COMMA)
            {
                R(param_node) = node_creater (param_node, nullptr, nullptr, PARAM);
                param_node = R(param_node);
                (*index)++;
            }
            else
            {
                if (token_tree->data[*index]->type == SEPARATOR ||                                                                   
                    token_tree->data[*index]->separator_type == COMMA)                                                         
                {                                                                                                               
                    printf ("Syntax error in %s: on line %d comma \",\" absent\n", tree->file_language->file_name, number_line); 
                }
                else
                {
                    printf ("Syntax error in %s: on line %d there is ( , but ) absent\n", tree->file_language->file_name, number_line);
                }
                return nullptr;
            }
        }

        COMMA_POINT_CHECK(index);
        (*index)++;

        Node* st_node = node_creater (nullptr, 
                                      NODE,
                                      node_creater (st_node, nullptr, nullptr, NIL), 
                                      ST);
        PNODE = st_node;
        NODE = st_node;
    }
    else
    {
        NODE = GetDeclaringVar (tree, token_tree, index);
        NULL_CHECK (NODE);
    }

    return NODE;
}

Node* GetDeclaringVar (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;

    if (token_tree->data[*index]->type == TYPE_FUNC &&
        token_tree->data[*index]->type_func_type == VAR)
    {
        int number_line = token_tree->data[*index]->number_line;
        NODE = token_tree->data[*index];

        (*index)++;

        if (token_tree->data[*index]->type == VARIABLE)
        {
            LNODE = token_tree->data[*index];
            P(LNODE) = NODE;

            (*index)++;

            if (*index < (token_tree->size - 1) &&
                token_tree->data[*index]->type == OPERATION && 
                token_tree->data[*index]->op_type == ASSIGN)
            {
                (*index)++;
                RNODE = GetE (tree, token_tree, index);
                P(RNODE) = NODE;
            }
            else
            {
                RNODE = node_creater (NODE, nullptr, nullptr, NIL);
            }

            COMMA_POINT_CHECK(index);
            (*index)++; 

            Node* st_node = node_creater (nullptr, 
                                      NODE,
                                      node_creater (st_node, nullptr, nullptr, NIL), 
                                      ST);
            PNODE = st_node;
            NODE = st_node;
        }
        else
        {
            printf ("Syntax error in %s: on line %d there is no variable name after \"var\"\n", tree->file_language->file_name, number_line);
            return nullptr;
        }
    }
    else
    {
        NODE = GetAssignVar (tree, token_tree, index);
        NULL_CHECK (NODE);
    }

    return NODE;
}

Node* GetAssignVar (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;

    if (token_tree->data[*index]->type == VARIABLE)
    {
        int number_line = token_tree->data[*index]->number_line;

        Node* variable_node = token_tree->data[*index];
        (*index)++;

        if (*index < (token_tree->size - 1) &&
            token_tree->data[*index]->type == OPERATION && 
            token_tree->data[*index]->op_type == ASSIGN)
        {
            NODE = token_tree->data[*index];
            LNODE = variable_node;
            P(LNODE) = NODE;

            (*index)++;

            RNODE = GetE (tree, token_tree, index);
            NULL_CHECK (RNODE);
            P(RNODE) = NODE;

            COMMA_POINT_CHECK(index);
            (*index)++;

            Node* st_node = node_creater (nullptr, 
                                          NODE,
                                          node_creater (st_node, nullptr, nullptr, NIL), 
                                          ST);
            PNODE = st_node;
            NODE = st_node;

        }
        else
        {
            printf ("Syntax error in %s: on line %d there is no \"=\" after \"var\"\n", tree->file_language->file_name, number_line);
            return nullptr;
        }
    }

    return NODE;
}

Node* GetE (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = GetT (tree, token_tree, index);
    NULL_CHECK(NODE);

    while (*index < token_tree->size &&
           token_tree->data[*index]->type == OPERATION && 
          (token_tree->data[*index]->op_type == ADD || 
           token_tree->data[*index]->op_type == SUB))
    {
        Node* op_node = token_tree->data[*index];

        (*index)++;

        Node* value_node = GetT (tree, token_tree, index);
        NULL_CHECK(value_node);

        L(op_node) = NODE;
        R(op_node) = value_node;

        PNODE = op_node;
        P(value_node) = op_node;

        NODE = op_node;
    }

    return NODE;
}

Node* GetT (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = GetP (tree, token_tree, index);

    NULL_CHECK(NODE);

    while (*index < token_tree->size &&
           token_tree->data[*index]->type == OPERATION && 
          (token_tree->data[*index]->op_type == MUL || 
           token_tree->data[*index]->op_type == DIV))
    {
        Node* op_node = token_tree->data[*index];

        (*index)++;

        Node* value_node = GetP (tree, token_tree, index);
        NULL_CHECK(value_node);

        L(op_node) = NODE;
        R(op_node) = value_node;

        PNODE = op_node;
        P(value_node) = op_node;

        NODE = op_node;
    }

    return NODE;
}

Node* GetP (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;

    if (token_tree->data[*index]->type == SEPARATOR &&
        token_tree->data[*index]->separator_type == OPEN_STANDART_BRACKET)
    {
        int number_line = token_tree->data[*index]->number_line;

        (*index)++;

        NODE = GetE (tree, token_tree, index);
        NULL_CHECK(NODE);

        CLOSE_STANDART_BRACKET_CHECK(index);

        (*index)++;
    }
    else
    {
        NODE = GetMathFunc (tree, token_tree, index);
        NULL_CHECK(NODE);
    }

    return NODE;
}

Node* GetMathFunc (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;

    if (token_tree->data[*index]->type == OPERATION)
    {
        int number_line = 0;

        if (token_tree->data[*index]->op_type == SIN ||
            token_tree->data[*index]->op_type == COS )
        {
            number_line = token_tree->data[*index]->number_line;
            
            NODE = token_tree->data[*index];
            (*index)++;

            OPEN_STANDART_BRACKET_CHECK(index);

            (*index)++;

            Node* argument_node = GetE (tree, token_tree, index);
            NULL_CHECK(argument_node);

            LNODE = argument_node;
            P(LNODE) = NODE;

            RNODE = node_creater (NODE, nullptr, nullptr, NIL);

            CLOSE_STANDART_BRACKET_CHECK(index)

            (*index)++;
        }
        else if (token_tree->data[*index]->op_type == POW)
        {
            number_line = token_tree->data[*index]->number_line;
            
            NODE = token_tree->data[*index];
            (*index)++;

            OPEN_STANDART_BRACKET_CHECK(index);

            (*index)++;

            number_line = token_tree->data[*index]->number_line;

            Node* first_argument_node = GetE (tree, token_tree, index);
            NULL_CHECK(first_argument_node);

            LNODE = first_argument_node;
            P(LNODE) = NODE;

            COMMA_CHECK(index);

            (*index)++;

            Node* second_argument_node = GetE (tree, token_tree, index);
            NULL_CHECK(second_argument_node);

            RNODE = second_argument_node;
            P(RNODE) = NODE;

            CLOSE_STANDART_BRACKET_CHECK(index)
            (*index)++;
        }
    }
    else
    {   
        NODE = GetV (tree, token_tree, index);
        NULL_CHECK (NODE);
    }

    return NODE;
}

Node* GetV (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;

    if (token_tree->data[*index]->type == VARIABLE)
    {
        NODE = token_tree->data[*index];
        (*index)++;
    }
    else
    {
        NODE = GetN (tree, token_tree, index);
        NULL_CHECK (NODE);
    }

    return NODE;
}

Node* GetN (struct Tree* tree, struct Stack* token_tree, int* index)
{
    assert (tree);
    assert (token_tree);
    assert (index);

    Node* NODE = nullptr;

    if (token_tree->data[*index]->type == VALUE)
    {
        NODE = token_tree->data[*index];
    }
    else
    {
        printf ("Syntax error in %s: on line %d the global variable is not assigned a number\n", tree->file_language->file_name, token_tree->data[*index]->number_line);
        return nullptr;
    }

    (*index)++;

    return NODE;
}
//=====================================================================

void tree_standart_print (FILE* language_tree, struct Node* root)
{
    assert (language_tree);
    assert (root);

    fprintf (language_tree, "{");

    if (!root)
    {
        return;
    }

    if (root->type == ST)
    {
        fprintf (language_tree, " ST \n");
    }
    else if (root->type == NIL)
    {
        fprintf (language_tree, " NIL \n");
    }
    else if (root->type == PARAM)
    {
        fprintf (language_tree, " PARAM \n");
    }
    else if (root->type == FUNC)
    {
        fprintf (language_tree, " FUNC \n");
    }
    else if (root->type == TYPE_FUNC)
    {
        switch (root->type_func_type)
        {
            case (VAR) : fprintf (language_tree, " VAR \n");  break;
            case (TYPE): fprintf (language_tree, " Type \n"); break;
            case (VOID): fprintf (language_tree, " Void \n"); break;
        }
    }
    else if (root->type == FUNCTION)
    {
        switch (root->function_type)
        {
            case (PRINTF): fprintf (language_tree, " OUT \n"); break;
            case (SCANF) : fprintf (language_tree, " IN \n");  break;
        }
    }
    else if (root->type == OPERATION)
    {
        switch (root->op_type)
        {
            case (IF):     fprintf (language_tree, " IF \n");    break;
            case (ELSE):   fprintf (language_tree, " ELSE \n");  break;
            case (WHILE):  fprintf (language_tree, " WHILE \n"); break;
            case (RETURN): fprintf (language_tree, " RET \n");   break;
            case (ADD):    fprintf (language_tree, " ADD \n");   break;
            case (SUB):    fprintf (language_tree, " SUB \n");   break;
            case (MUL):    fprintf (language_tree, " MUL \n");   break;
            case (DIV):    fprintf (language_tree, " DIV \n");   break;
            case (ASSIGN): fprintf (language_tree, " EQ \n");    break;
            case (POW):    fprintf (language_tree, " POW \n");   break;
            case (SIN):    fprintf (language_tree, " SIN \n");   break;
            case (COS):    fprintf (language_tree, " COS \n");   break;
        }
    }
    else if (root->type == VARIABLE)
    {
        fprintf (language_tree, " \"%s\"\n", root->variable);
    }
    else if (root->type == VALUE)
    {
        fprintf (language_tree, " %lg \n", root->value);
    }

    if (root->left)
    {
        tree_standart_print (language_tree, root->left);
    }
    
    if (root->right)
    {
        tree_standart_print (language_tree, root->right);
    }

    fprintf (language_tree, "}\n");
}

//=====================================================================

void listing_token (Stack* token_tree)
{
    FILE* token_listing = fopen ("FRONTEND/token_listing.txt","ab");
    for (int i = 0; i < token_tree->size; i++)
    {
        if (token_tree->data[i]->type == VALUE)
        {
            fprintf (token_listing, "%lg\t%d\n", token_tree->data[i]->value, token_tree->data[i]->number_line);
        }
        else if (token_tree->data[i]->type == VARIABLE)
        {
            fprintf (token_listing, "%s\t%d\n", token_tree->data[i]->variable, token_tree->data[i]->number_line);
        }
        else if (token_tree->data[i]->type == OPERATION)
        {
            #define DEF_OP(name, length, global_type, OP)   if (token_tree->data[i]->op_type == OP)                    \
                                                            {                                                                 \
                                                                fprintf (token_listing, #OP "\t%d\n", token_tree->data[i]->number_line);  \
                                                            }
            #define DEF_FUNC(name, length, global_type, OP)
            #define DEF_SEP(name, length, global_type, OP)
            #define DEF_TYPE(name, length, global_type, OP)

            #include "../code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE
        }
        else if (token_tree->data[i]->type == SEPARATOR)
        {
             #define DEF_SEP(name, length, global_type, FUNC)   if (token_tree->data[i]->separator_type == FUNC)                    \
                                                                {                                                                   \
                                                                    fprintf (token_listing, #FUNC "\t%d\n", token_tree->data[i]->number_line);  \
                                                                }
            #define DEF_OP(name, length, global_type, OP)
            #define DEF_FUNC(name, length, global_type, OP)
            #define DEF_TYPE(name, length, global_type, OP)

            #include "../code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE

        }
        else if (token_tree->data[i]->type == FUNCTION)
        {
            #define DEF_FUNC(name, length, global_type, FUNC)   if (token_tree->data[i]->function_type == FUNC)                     \
                                                                {                                                                   \
                                                                    fprintf (token_listing, #FUNC "\t%d\n", token_tree->data[i]->number_line);  \
                                                                }
            #define DEF_OP(name, length, global_type, OP)
            #define DEF_SEP(name, length, global_type, OP)
            #define DEF_TYPE(name, length, global_type, OP)

            #include "../code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE
        }
        else if (token_tree->data[i]->type == TYPE_FUNC)
        {
            #define DEF_TYPE(name, length, global_type, FUNC)   if (token_tree->data[i]->type_func_type == FUNC)                    \
                                                                {                                                                   \
                                                                    fprintf (token_listing, #FUNC "\t%d\n", token_tree->data[i]->number_line);  \
                                                                }
            #define DEF_OP(name, length, global_type, OP)
            #define DEF_FUNC(name, length, global_type, OP)
            #define DEF_SEP(name, length, global_type, OP)

            #include "../code_generation.h"

            #undef DEF_OP
            #undef DEF_FUNC
            #undef DEF_SEP
            #undef DEF_TYPE
        }
    }
    fprintf (token_listing, "=============================\n");

    fclose (token_listing);
}



#include "backend.h"

int tree_backend_ctor (struct Tree* tree)
{
    tree_ctor (tree);

    char* buffer = tree->buffer_language->file_buffer;
    tree->root = node_backend_creater (tree, nullptr, &buffer);
    tree_backend_creater (tree, &buffer);

    tree->ram = (RAM*) calloc (1, sizeof(RAM));
    tree->ram->global_var = (Variable*) calloc (MAX_NUM_VAR, sizeof (Variable));
    tree->ram->function = (Function*) calloc (MAX_NUM_FUNC, sizeof(Function));

    tree->ram->num_func = 0;
    tree->ram->num_global_var = 0;
    tree->ram->num_free_place = 0;

    FILE* asm_code = fopen ("/Users/kirilllahnov/Documents/Language/CPU/command.txt", "wb");

    int is_main_find = main_find (tree->root);

    if (is_main_find == 0)
    {
        printf ("Compilation failed: main is missing from the program");
        return ERROR_COMPILATION;
    }
    else
    {   
        fprintf (asm_code, "push 1\njmp :main\n");
    }

    if (transfer_to_asm (asm_code, tree->root, tree) != GOOD_WORKING)
    {
        fclose (asm_code);
        return ERROR_COMPILATION;
    }

    fclose (asm_code);

    return GOOD_WORKING;
}

int transfer_to_asm (FILE* asm_code, struct Node* node, struct Tree* tree)
{
    switch (node->type)
    {
        case (ST):
        {
            if (transfer_to_asm (asm_code, L(node), tree) != GOOD_WORKING)
            {
                return ERROR_COMPILATION;
            }
            if (transfer_to_asm (asm_code, R(node), tree) != GOOD_WORKING)
            {
                return ERROR_COMPILATION;
            }
            break;
        }
        case (NIL):
        {
            break;
        }
        case (FUNC):
        {
            int find_func = find_name_function (tree, L(node)->variable);
            if (find_func == 1)
            {
                printf ("Compilation failed: function \"%s\" already exists\n",L(node)->variable);
                return ERROR_COMPILATION;
            }

            CURRENT_FUNC.name = strdup (L(node)->variable);
            CURRENT_FUNC.type = LR(node)->type_func_type;
            CURRENT_FUNC.num_var = 0;
            tree->ram->num_func++;

            if (LL(node)->type != NIL)
            {
                if (get_param_func (LL(node), &_CURRENT_FUNC_, tree) != GOOD_WORKING)
                {
                    return ERROR_COMPILATION;
                }
            }

            fprintf (asm_code, "\n%s:\n\n", _CURRENT_FUNC_.name);

            if (get_func_body (R(node), &_CURRENT_FUNC_, tree, asm_code) != GOOD_WORKING)
            {
                return ERROR_COMMAND_CMP;
            }

            if (strcmp (L(node)->variable, "main") == 0)
            {
                fprintf (asm_code, "hlt\n");
            }
            else
            {
                fprintf (asm_code, "ret\n");
            }
            break;
        }
        case (TYPE_FUNC):
        {
            switch (node->type_func_type)
            {
                case (VAR):
                {
                    int check_global_var = is_global_var (node);
                    if (check_global_var == 1)
                    {
                        int find_replace_global_name = find_name_global_var (tree, L(node)->variable);
        
                        if (find_replace_global_name == 1)
                        {
                            printf ("Compilation failed: global variable \"%s\" already initialized\n",L(node)->variable);
                            return ERROR_COMPILATION;
                        }

                        CURRENT_GLOB_VAR.name = strdup (L(node)->variable);
                        CURRENT_GLOB_VAR.ram_place = tree->ram->num_free_place;
                        tree->ram->num_free_place++;

                        if (R(node)->type != NIL)
                        {
                            CURRENT_GLOB_VAR.initialization = VAR_INIT;
                            CURRENT_GLOB_VAR.value = R(node)->value;
                            fprintf (asm_code, "push %lg\npop [%d]\n", CURRENT_GLOB_VAR.value, CURRENT_GLOB_VAR.ram_place);
                        }
                        else
                        {
                            CURRENT_GLOB_VAR.initialization = VAR_NO_INIT;
                            CURRENT_GLOB_VAR.value = NAN;
                        }

                        tree->ram->num_global_var++;
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
        
    }

    return GOOD_WORKING;
}

int get_param_func (Node* node, Function* current_func, struct Tree* tree)
{
    if (node != nullptr && node->type == PARAM)
    {   
        int find_replace_global_name = find_name_global_var (tree, LL(node)->variable);
        
        if (find_replace_global_name == 1)
        {
            printf ("Compilation failed: in function \"%s\" variable's name \"%s\" repeat global variable's name\n", current_func->name, LL(node)->variable);
            return ERROR_COMPILATION;
        }

        current_func->var_func[current_func->num_var].name = strdup (LL(node)->variable);
        current_func->var_func[current_func->num_var].value = NAN;
        current_func->var_func[current_func->num_var].initialization = VAR_NO_INIT;
        current_func->var_func[current_func->num_var].ram_place = tree->ram->num_free_place;
        tree->ram->num_free_place++;
        current_func->num_var++;

        if (get_param_func (R(node), current_func, tree) != GOOD_WORKING)
        {
            return ERROR_COMPILATION;
        }
    }

    return GOOD_WORKING;
}

int get_func_body (Node* node, Function* current_func, struct Tree* tree, FILE* asm_code)
{
    switch (node->type)
    {
        case (ST):
        {
            if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
            {
                return ERROR_COMPILATION;
            }
            if (get_func_body (R(node), current_func, tree, asm_code) != GOOD_WORKING)
            {
                return ERROR_COMPILATION;
            }
            break;
        }
        case (NIL):
        {
            break;
        }
        case (CALL):
        {
            Function* func = find_func (tree, L(node)->variable);

            if (func == nullptr)
            {
                printf ("Compilation failed: function \"%s\" in function \"%s\" not defined\n", L(node)->variable, current_func->name);
                return ERROR_COMPILATION;
            }

            Variable* var_before = var_function_copy (func);

            if (get_call_param (LL(node), current_func, func, tree, asm_code, 0) != GOOD_WORKING)
            {
                return ERROR_COMPILATION;
            }

            fprintf (asm_code, "call :%s\n", L(node)->variable);
            fprintf (asm_code, "push rax\n");
            
            /*for (int i = func->num_var - 2; i >= 0; i--)
            {
                func->var_func[i].ram_place = var_before[i].ram_place; 
                func->var_func[i].initialization = var_before[i].initialization;
                func->var_func[i].value = var_before[i].value;

                fprintf (asm_code, "pop [%d]\n", var_before[i].ram_place);
            }*/

            free (var_before);
            
            break;
        }
        case (TYPE_FUNC):
        {
            if (node->type_func_type == VAR)
            {
                int find_repeat_global_name = find_name_global_var (tree, L(node)->variable);
                if (find_repeat_global_name == 1)
                {
                    printf ("Compilation failed: in function \"%s\" variable's name \"%s\" repeat global variable's name\n", current_func->name, L(node)->variable);
                    return ERROR_COMPILATION;
                }

                int find_repeat_func_name = find_name_function_var (current_func, L(node)->variable);
                if (find_repeat_func_name == 1)
                {
                    printf ("Compilation failed: variable \"%s\" in function \"%s\" already initialized\n", current_func->name, L(node)->variable);
                    return ERROR_COMPILATION;
                }

                current_func->var_func[current_func->num_var].name = strdup (L(node)->variable);

                if (R(node)->type != NIL)
                {
                    current_func->var_func[current_func->num_var].value = R(node)->value;
                    current_func->var_func[current_func->num_var].initialization = VAR_INIT;
                }
                else
                {
                    current_func->var_func[current_func->num_var].value = NAN;
                    current_func->var_func[current_func->num_var].initialization = VAR_NO_INIT;
                }

                current_func->var_func[current_func->num_var].ram_place = tree->ram->num_free_place;
                tree->ram->num_free_place++;

                if (get_func_body (R(node), current_func, tree, asm_code) != GOOD_WORKING)
                {
                    return ERROR_COMPILATION;
                }
                fprintf (asm_code, "pop [%d]\n", current_func->var_func[current_func->num_var].ram_place);
                current_func->num_var++;   
            }
            else
            {
                printf ("Compilation failed: type or void cannot be used in the function \"%s\" body", current_func->name);
                return ERROR_COMPILATION;
            }
            break;
        }
        case (OPERATION):
        {
            switch (node->op_type)
            {
                case (EQ):
                {
                    if (get_func_body (R(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }

                    if (L(node) != nullptr && L(node)->type == VARIABLE)
                    {
                        int announced_var = is_announced_var (current_func, tree, L(node)->variable);
                        if (announced_var == 0)
                        {
                            printf ("Compilation failed: variable \"%s\" not declared in the function \"%s\"\n", L(node)->variable, current_func->name);
                            return ERROR_COMPILATION;
                        }

                        Variable* var = find_func_var (current_func, tree, L(node)->variable);
                        var->initialization = VAR_INIT;
                        fprintf (asm_code, "pop [%d]\n", var->ram_place);
                    }
                    else
                    {
                        printf ("Compilation failed: unknown error");
                        return ERROR_COMPILATION;
                    }

                    break;
                }
                case (ADD):
                {   
                    if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    if (get_func_body (R(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    fprintf (asm_code, "add\n");
                    break;
                }
                case (SUB):
                {
                    if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    if (get_func_body (R(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    fprintf (asm_code, "sub\n");
                    break;
                }
                case (MUL):
                {
                    if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    if (get_func_body (R(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    fprintf (asm_code, "mul\n");
                    break;
                }
                case (DIV):
                {
                    if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    if (get_func_body (R(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    fprintf (asm_code, "div\n");
                    break;
                }
                case (SIN):
                {
                    if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    fprintf (asm_code, "sin\n");
                    break;
                }
                case (COS):
                {
                    if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    fprintf (asm_code, "cos\n");
                    break;
                }
                case (POW):
                {
                    if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    if (get_func_body (R(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }

                    fprintf (asm_code, "pow\n");
                    break;
                }
                case (IF):
                {
                    if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    fprintf (asm_code, "push 0\n");
                    fprintf (asm_code, "ja :if%p\n", node);
                    fprintf (asm_code, "jmp :ifnot%p\n", node);

                    if (node->right->op_type != ELSE)
                    {
                        fprintf (asm_code, "if%p:\n", node);
                        if (get_func_body (R(node), current_func, tree, asm_code) != GOOD_WORKING)
                        {
                            return ERROR_COMPILATION;
                        }
                        fprintf (asm_code, "\nifnot%p:\n", node);
                    }
                    else
                    {
                        fprintf (asm_code, "\nif%p:\n", node);
                        if (get_func_body (RL(node), current_func, tree, asm_code) != GOOD_WORKING)
                        {
                            return ERROR_COMPILATION;
                        }
                        fprintf (asm_code, "\njmp :ifafter%p\n", node);
                        fprintf (asm_code, "\nifnot%p:\n", node);
                        if (get_func_body (RR(node), current_func, tree, asm_code) != GOOD_WORKING)
                        {
                            return ERROR_COMPILATION;
                        }
                        fprintf (asm_code, "ifafter%p:\n", node);
                    }

                    break;
                }
                case (WHILE):
                {
                    fprintf (asm_code, "while%p:\n", node);
                    if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    fprintf (asm_code, "push 0\n");
                    fprintf (asm_code, "ja :whilebody%p\n", node);
                    fprintf (asm_code, "jmp :whileafter%p\n", node);

                    fprintf (asm_code, "whilebody%p:\n", node);
                    if (get_func_body (R(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    fprintf (asm_code, "jmp :while%p\n", node);
                    fprintf (asm_code, "whileafter%p:\n", node);
                    break;
                }
                case (RET):
                {
                    if (current_func->type == VOID)
                    {
                        if (L(node)->type != NIL)
                        {
                            printf ("Compilation failed: function \"%s\" is void and cannot return number\n", current_func->name);
                        }
                        else
                        {
                            fprintf (asm_code, "ret\n");
                        }
                    }
                    else if (current_func->type == TYPE)
                    {
                        if (L(node)->type == NIL)
                        {
                            printf ("Compilation failed: function \"%s\" is type and should return a number\n", current_func->name);
                        }
                        else
                        {
                            if (get_func_body (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                            {
                                return ERROR_COMPILATION;
                            }
                            fprintf (asm_code, "pop rax\n");
                        }
                    }
                    break;
                }
            }
            break;
        }
        case (FUNCTION):
        {
            switch (node->function_type)
            {
                case (OUT):
                {   
                    if (get_out_param (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {
                        return ERROR_COMPILATION;
                    }
                    break;
                }
                case (IN):
                {
                    if (get_in_param (L(node), current_func, tree, asm_code) != GOOD_WORKING)
                    {   
                        return ERROR_COMPILATION;
                    }
                    break;
                }
            }
            break;
        }
        case (VALUE):
        {
            fprintf (asm_code, "push %lg\n", node->value);
            break;
        }
        case (VARIABLE):
        {
            int announced_var = is_announced_var (current_func, tree, node->variable);
            if (announced_var == 0)
            {
                printf ("Compilation failed: variable \"%s\" not declared in the function \"%s\"\n", node->variable, current_func->name);
                return ERROR_COMPILATION;
            }

            Variable* var = find_func_var (current_func, tree, node->variable);

            fprintf (asm_code, "push [%d]\n", var->ram_place);
            break;
        }
        default:
            break;

    }

    return GOOD_WORKING;
}

int get_in_param (Node* NODE, Function* current_func, Tree* tree, FILE* asm_code)
{
    if (NODE->type == PARAM)
    {
        Variable* var = find_func_var (current_func, tree, LNODE->variable);
        if (var == nullptr)
        {
            printf ("Compilation failed: variable \"%s\" not declared in the function scanf\n", LNODE->variable);
            return ERROR_COMPILATION;
        }

        fprintf (asm_code, "\nin\n");
        fprintf (asm_code, "pop [%d]\n", var->ram_place);

        if (get_in_param (RNODE, current_func, tree, asm_code) != GOOD_WORKING)
        {
            return ERROR_COMPILATION;
        }
    }
    else if (NODE->type == NIL)
    {
        return GOOD_WORKING;
    }
    else
    {
        printf ("Compilation failed: unknown error\n");
        return ERROR_COMPILATION;
    }

    return GOOD_WORKING;
}

int get_out_param (Node* NODE, Function* current_func, Tree* tree, FILE* asm_code)
{   
    if (NODE->type == PARAM)
    {
        if (get_func_body (LNODE, current_func, tree, asm_code) != GOOD_WORKING)
        {
            return ERROR_COMPILATION;
        }

        fprintf (asm_code, "out\n\n");

        if (get_out_param (RNODE, current_func, tree, asm_code) != GOOD_WORKING)
        {
            return ERROR_COMPILATION;
        }
    }
    else if (NODE->type == NIL)
    {
        return GOOD_WORKING;
    }
    else
    {
        printf ("Compilation failed: unknown error\n");
        return ERROR_COMPILATION;
    }

    return GOOD_WORKING;
}

int get_call_param (Node* NODE, Function* current_func, Function* call, Tree* tree, FILE* asm_code, int call_number)
{
    if (NODE->type == PARAM)
    {   
        if (get_func_body (LNODE, current_func, tree, asm_code) != GOOD_WORKING)
        {
            return ERROR_COMPILATION;
        }
        fprintf (asm_code, "pop [%d]\n", call->var_func[call_number].ram_place);
        current_func->var_func[call_number].initialization = VAR_INIT;

        call_number++;
        if (get_call_param (RNODE, current_func, call, tree, asm_code, call_number) != GOOD_WORKING)
        {
            return ERROR_COMPILATION;
        }
    }
    else if (NODE->type == NIL)
    {
        return GOOD_WORKING;
    }
    else
    {
        printf ("Compilation failed: unknown error\n");
        return ERROR_COMPILATION;
    }

    return GOOD_WORKING;
}

//=================================================================

void tree_backend_creater (struct Tree* tree, char** current_position)
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
            struct Node* new_knot = node_backend_creater (tree, NODE, current_position);
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
                struct Node* new_knot = node_backend_creater (tree, NODE, current_position);
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

Node* node_backend_creater (struct Tree* tree, struct Node* prev, char** current_position)
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
    #define  DEF_SEP(str_name, length, global_type, sub_type)

    #include "../code_generation.h"

    #undef DEF_OP
    #undef DEF_FUNC
    #undef DEF_TYPE
    #undef DEF_SEP

    free (command);

    return NODE;
}

//=================================================================

Stack* path_node_to_root (Node* NODE)
{
    Stack* path_node = (Stack*) calloc (1, sizeof(Stack));
    StackCtor (path_node, 1);

    while (NODE != nullptr)
    {
        StackPush (path_node, PNODE);
        NODE = PNODE;
    }

    return path_node;
}

int is_global_var (Node* NODE)
{
    Stack* path_node = path_node_to_root (NODE);

    for (int i = 0; i < path_node->size; i++)
    {
        if (path_node->data[i] != nullptr && path_node->data[i]->type != ST)
        {
            StackDtor (path_node);
            return 0;
        }
    }

    StackDtor (path_node);
    return 1;
}

int is_from_param (Node* NODE)
{
    Stack* path_node = path_node_to_root (NODE);

    for (int i = 0; i < path_node->size; i++)
    {
        if (path_node->data[i] != nullptr && path_node->data[i]->type != CALL)
        {
            StackDtor (path_node);
            return 3;
        }
        else if (path_node->data[i] != nullptr && path_node->data[i]->type != FUNCTION)
        {
            StackDtor (path_node);
            return 2;
        }
        else if (path_node->data[i] != nullptr && path_node->data[i]->type != FUNC)
        {
            StackDtor (path_node);
            return 1;
        }
    }

    StackDtor (path_node);
    return 0;
}

int find_name_global_var (struct Tree* tree, char* name)
{
    for (int i = 0; i < tree->ram->num_global_var; i++)
    {
        if (strcmp (tree->ram->global_var[i].name, name) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int find_name_function_var (struct Function* func, char* name)
{
    for (int i = 0; i < func->num_var; i++)
    {
        if (strcmp (func->var_func[i].name, name) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int is_announced_var (struct Function* func, struct Tree* tree, char* name)
{
    int find_global = find_name_global_var (tree, name);
    int find_func = find_name_function_var (func, name);

    if (find_func == 1 || find_global == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Variable* find_func_var (struct Function* func, struct Tree* tree, char* name)
{
    for (int i = 0; i < tree->ram->num_global_var; i++)
    {
        if (strcmp (tree->ram->global_var[i].name, name) == 0)
        {
            return &tree->ram->global_var[i];
        }
    }
    for (int i = 0; i < func->num_var; i++)
    {
        if (strcmp (func->var_func[i].name, name) == 0)
        {
            return &func->var_func[i];
        }
    }

    return nullptr;
}

Function* find_func (struct Tree* tree, char* name)
{
    for (int i = 0; i < tree->ram->num_func; i++)
    {
        if (strcmp (tree->ram->function[i].name, name) == 0)
        {
            return &tree->ram->function[i];
        }
    }

    return nullptr;
}

Node* find_eq_node (struct Node* NODE)
{
    while (PNODE->type != OPERATION && PNODE->op_type != EQ)
    {
        NODE = PNODE;
    }

    return NODE;
}

int main_find (struct Node* node)
{
    switch (node->type)
    {
        case (ST):
        {
            int rez_1 = main_find (L(node));
            int rez_2 = main_find (R(node));

            return rez_1 + rez_2;
        }
        case (FUNC):
        {
            if (L(node)->type == VARIABLE && strcmp(L(node)->variable, "main") == 0)
            {
                return 1;
            }
        }
        case (TYPE_FUNC):
        case (VALUE):
        case (VARIABLE):
        case (OPERATION):
        case (FUNCTION):
        case (PARAM):
        case (CALL):
        case (NIL):
        default:
            break;
    }
    return 0;
}

int find_name_function (struct Tree* tree, char* name)
{
    for (int i = 0; i < tree->ram->num_func; i++)
    {
        if (strcmp (name, tree->ram->function[i].name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

Variable* var_function_copy (Function* func)
{
    Variable* var_copy = (Variable*) calloc (func->num_var, sizeof(Variable));

    for (int i = 0; i < func->num_var; i++)
    {
        var_copy[i].ram_place = func->var_func[i].ram_place;
        var_copy[i].initialization = func->var_func[i].initialization;
        var_copy[i].value = func->var_func[i].value;
    }

    return var_copy;
}

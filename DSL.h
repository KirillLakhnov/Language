#define NODE  current_node
#define PNODE current_node->prev
#define LNODE current_node->left
#define RNODE current_node->right

#define P(node) node->prev
#define L(node) node->left
#define R(node) node->right

#define LL(node) node->left->left
#define LR(node) node->left->right

#define RL(node) node->right->left
#define RR(node) node->right->right

#define NULL_CHECK(node) if (node == nullptr) {return nullptr;}

#define OPEN_STANDART_BRACKET_CHECK(index)  if (*index > (token_tree->size - 1) ||                                                                      \
                                            (token_tree->data[*index]->type != SEPARATOR ||                                                             \
                                             token_tree->data[*index]->separator_type != OPEN_STANDART_BRACKET))                                        \
                                            {                                                                                                           \
                                                printf ("Syntax error in %s: on line %d ( absent\n", tree->file_language->file_name, number_line);      \
                                                return nullptr;                                                                                         \
                                            }

#define CLOSE_STANDART_BRACKET_CHECK(index) if (*index > (token_tree->size - 1) ||                                                                                      \
                                            (token_tree->data[*index]->type != SEPARATOR ||                                                                             \
                                             token_tree->data[*index]->separator_type != CLOSE_STANDART_BRACKET))                                                       \
                                            {                                                                                                                           \
                                                printf ("Syntax error in %s: on line %d there is ( , but ) absent\n", tree->file_language->file_name, number_line);     \
                                                return nullptr;                                                                                                         \
                                            }

#define OPEN_CURLY_BRACKET_CHECK(index)     if (*index > (token_tree->size - 1) ||                                                                      \
                                            (token_tree->data[*index]->type != SEPARATOR ||                                                             \
                                             token_tree->data[*index]->separator_type != OPEN_CURLY_BRACKET))                                        \
                                            {                                                                                                           \
                                                printf ("Syntax error in %s: on line %d { absent\n", tree->file_language->file_name, number_line);      \
                                                return nullptr;                                                                                         \
                                            }

#define CLOSE_CURLY_BRACKET_CHECK(index)    if (*index > (token_tree->size - 1) ||                                                                                      \
                                            (token_tree->data[*index]->type != SEPARATOR ||                                                                             \
                                             token_tree->data[*index]->separator_type != CLOSE_CURLY_BRACKET))                                                          \
                                            {                                                                                                                           \
                                                printf ("Syntax error in %s: on line %d there is { , but } absent\n", tree->file_language->file_name, number_line);     \
                                                return nullptr;                                                                                                         \
                                            }

#define COMMA_CHECK(index)  if (*index > (token_tree->size - 1) ||                                                                            \
                            (token_tree->data[*index]->type != SEPARATOR ||                                                                   \
                             token_tree->data[*index]->separator_type != COMMA))                                                              \
                            {                                                                                                                 \
                                printf ("Syntax error in %s: on line %d comma \",\" absent\n", tree->file_language->file_name, number_line);  \
                                return nullptr;                                                                                               \
                            }

#define COMMA_POINT_CHECK(index)    if (*index > (token_tree->size - 1) ||                                                                                          \
                                    (token_tree->data[*index]->type != SEPARATOR ||                                                                                 \
                                    token_tree->data[*index]->separator_type != COMMA_POINT))                                                                       \
                                    {                                                                                                                               \
                                        printf ("Syntax error in %s: on line %d comma and point \";\" absent\n", tree->file_language->file_name, number_line);      \
                                        return nullptr;                                                                                                             \
                                    }

#define COMMENT_CLOSE_CHECK(current_symbol) while (strncmp("*/", current_symbol, 2) != 0)                                                                                       \
                                            {                                                                                                                                   \
                                                if (*(current_symbol + 1) == '\0')                                                                                              \
                                                {                                                                                                                               \
                                                    printf ("Syntax error in %s: absent */, but there is /* on the line %d\n", tree->file_language->file_name, number_line);    \
                                                    return nullptr;                                                                                                             \
                                                }                                                                                                                               \
                                                current_symbol++;                                                                                                               \
                                            }                                                                                                                                   \
                                            current_symbol += 2;

#define UNKNOWN_COMMAND(number_line)    printf ("Syntax error in %s: unknown command on line %d", tree->file_language->file_name, number_line); \
                                        return nullptr;

#define CURRENT_GLOB_VAR tree->ram->global_var[tree->ram->num_global_var]
#define CURRENT_FUNC tree->ram->function[tree->ram->num_func]
#define _CURRENT_FUNC_ tree->ram->function[tree->ram->num_func - 1]

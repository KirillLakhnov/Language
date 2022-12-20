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


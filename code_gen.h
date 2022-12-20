DEF_WORD("if",     2, OPERATION, IF)
DEF_WORD("else",   4, OPERATION, ELSE)
DEF_WORD("while",  5, OPERATION, WHILE)
DEF_WORD("RETURN", 6, OPERATION, RETURN)
DEF_WORD("+",      1, OPERATION, ADD)
DEF_WORD("-",      1, OPERATION, SUB)
DEF_WORD("*",      1, OPERATION, MUL)
DEF_WORD("/",      1, OPERATION, DIV)
DEF_WORD("=",      1, OPERATION, ASSIGN)
DEF_WORD("pow",    3, OPERATION, POW)
DEF_WORD("sin",    3, OPERATION, SIN)
DEF_WORD("cos",    3, OPERATION, COS)

DEF_WORD("scanf",  5, FUNCTION, SCANF)
DEF_WORD("printf", 6, FUNCTION, PRINTF)

DEF_WORD("type", 4, TYPE_FUNC, TYPE)
DEF_WORD("void", 4, TYPE_FUNC, VOID)
DEF_WORD("var",  3, TYPE_FUNC, VAR)

DEF_WORD("(", 1, SEPARATOR, OPEN_STANDART_BRACKET)
DEF_WORD(")", 1, SEPARATOR, CLOSE_STANDART_BRACKET)
DEF_WORD("{", 1, SEPARATOR, OPEN_CURLY_BRACKET)
DEF_WORD("}", 1, SEPARATOR, CLOSE_CURLY_BRACKET)
DEF_WORD(";", 1, SEPARATOR, COMMA_POINT)
DEF_WORD(",", 1, SEPARATOR, COMMA)
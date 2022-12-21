DEF_OP("if",     2, OPERATION, IF)
DEF_OP("else",   4, OPERATION, ELSE)
DEF_OP("while",  5, OPERATION, WHILE)
DEF_OP("return", 6, OPERATION, RET)
DEF_OP("+",      1, OPERATION, ADD)
DEF_OP("-",      1, OPERATION, SUB)
DEF_OP("*",      1, OPERATION, MUL)
DEF_OP("/",      1, OPERATION, DIV)
DEF_OP("=",      1, OPERATION, EQ)
DEF_OP("pow",    3, OPERATION, POW)
DEF_OP("sin",    3, OPERATION, SIN)
DEF_OP("cos",    3, OPERATION, COS)

DEF_FUNC("scanf",  5, FUNCTION, IN)
DEF_FUNC("printf", 6, FUNCTION, OUT)

DEF_TYPE("type", 4, TYPE_FUNC, TYPE)
DEF_TYPE("void", 4, TYPE_FUNC, VOID)
DEF_TYPE("var",  3, TYPE_FUNC, VAR)

DEF_SEP("(", 1, SEPARATOR, OPEN_STANDART_BRACKET)
DEF_SEP(")", 1, SEPARATOR, CLOSE_STANDART_BRACKET)
DEF_SEP("{", 1, SEPARATOR, OPEN_CURLY_BRACKET)
DEF_SEP("}", 1, SEPARATOR, CLOSE_CURLY_BRACKET)
DEF_SEP(";", 1, SEPARATOR, COMMA_POINT)
DEF_SEP(",", 1, SEPARATOR, COMMA)







#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "tree.h"

Knot* GetG (char **str, struct Tree* tree);

#endif PARSER_H
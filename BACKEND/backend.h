#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <locale.h>

#include "../tree.h"
#include "../DSL.h"
#include "../libraries/stack.h"

void tree_backend_ctor (struct Tree* tree);

#endif // BACKEND_H

#include <token.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef FILE file;

bool lexical(token_t** array, size_t* array_size, file* file);
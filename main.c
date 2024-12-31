#include <token.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syntax.h>
#include <lexical.h>

file* input_file;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Error: incorrect command.");
        return -1;
    }
    if (strcmp(argv[1] + strlen(argv[1]) - 4, ".txt")) {
        printf("Error: incompatible file extension.");
        return -1;
    }
    file* input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Error: could not open file.");
        return -1;
    }
    token_t* array = NULL;
    size_t array_size = 0;
    int error;
    if (lexical(&array, &array_size, input_file)) {
        for (int i = 0; i < array_size; i++) {
            if (array[i].id == ID_TOKEN) printf("token %i: token type = %i, name = %s\n", i + 1, ID_TOKEN, array[i].attribut.name);
            else if (array[i].id == NB_TOKEN) printf("token %i: token type = %i, value = %llu\n", i + 1, NB_TOKEN, array[i].attribut.value);
            else if (array[i].id == OPREL_TOKEN) printf("token %i: token type = %i, op = %i\n", i + 1, OPREL_TOKEN, array[i].attribut.op);
            else if (array[i].id == OPADD_TOKEN) printf("token %i: token type =  %i, op = %i\n", i + 1, OPADD_TOKEN, array[i].attribut.op);
            else if (array[i].id == OPMUL_TOKEN) printf("token %i: token type = %i, op = %i\n", i + 1, OPMUL_TOKEN, array[i].attribut.op);
            else printf("token %i: token type = %i\n", i + 1, array[i].id);
        }
        if ((error = syntax(array, array_size)) == -1) printf("Source code ready to compile.");
        else {
            printf("Error: syntax analysis error on token %i.", error);
            return -1;
        }
    }
    else {
        printf("Error: lexical analysis error.");
        return -1;
    }
}
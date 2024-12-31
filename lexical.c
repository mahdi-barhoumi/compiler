#include <lexical.h>

const char* key_words[] = {"program", "var", "integer", "char", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "readln", "writeln"};

bool lexical(token_t** array, size_t* array_size, file* file)
{
    token_t temp;
    bool key_word;
    char character;
    char* buffer = NULL;
    size_t buffer_size = 0;
    while ((character = fgetc(file)) != EOF) {
        if (isalpha(character)) {
            do {
                buffer = realloc(buffer, ++buffer_size * sizeof(char));
                buffer[buffer_size - 1] = character;
            } while (isalnum(character = fgetc(file)));
            ungetc(character, file);
            buffer = realloc(buffer, ++buffer_size * sizeof(char));
            buffer[buffer_size - 1] = '\0';
            key_word = false;
            for (int i = 0; i < 15; i++) {
                if (!strcmp(buffer, key_words[i])) {
                    key_word = true;
                    temp.id = (token) i;
                    temp.attribut.name = NULL;
                    break;
                }
            }
            if (!key_word) {
                temp.id = ID_TOKEN;
                temp.attribut.name = malloc(buffer_size * sizeof(char));
                strcpy(temp.attribut.name, buffer);
            }
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
            free(buffer);
            buffer = NULL;
            buffer_size = 0;
        }
        else if (isdigit(character)) {
            do {
                buffer = realloc(buffer, ++buffer_size * sizeof(char));
                buffer[buffer_size - 1] = character;
            } while (isdigit(character = fgetc(file)));
            if (isalpha(character)) {
                free(buffer);
                free(*array);
                *array_size = 0;
                *array = NULL;
                return false;
            }
            ungetc(character, file);
            buffer = realloc(buffer, ++buffer_size * sizeof(char));
            buffer[buffer_size - 1] = '\0';
            temp.id = NB_TOKEN;
            temp.attribut.value = atoll(buffer);
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
            free(buffer);
            buffer = NULL;
            buffer_size = 0;
        }
        else if (character == '=') {
            character = fgetc(file);
            if (character != '=') {
                free(*array);
                *array_size = 0;
                *array = NULL;
                return false;
            }
            else {
                temp.id = OPREL_TOKEN;
                temp.attribut.op = EQUAL;
                *array = realloc(*array, ++(*array_size) * sizeof(token_t));
                (*array)[*array_size - 1] = temp;
            }
        }
        else if (character == '<') {
            character = fgetc(file);
            temp.id = OPREL_TOKEN;
            if (character == '>') temp.attribut.op = NOT_EQUAL;
            else if (character == '=') temp.attribut.op = LESS_THAN_OR_EQUAL;
            else {
                ungetc(character, file);
                temp.attribut.op = LESS_THAN;
            }
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == '>') {
            character = fgetc(file);
            temp.id = OPREL_TOKEN;
            if (character == '=') temp.attribut.op = GREATER_THAN_OR_EQUAL;
            else {
                ungetc(character, file);
                temp.attribut.op = GREATER_THAN;
            }
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == '+') {
            temp.id = OPADD_TOKEN;
            temp.attribut.op = ADD;
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == '-') {
            temp.id = OPADD_TOKEN;
            temp.attribut.op = SUB;
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == '|') {
            character = fgetc(file);
            if (character != '|') {
                free(*array);
                *array_size = 0;
                *array = NULL;
                return false;
            }
            else {
                temp.id = OPADD_TOKEN;
                temp.attribut.op = OR;
                *array = realloc(*array, ++(*array_size) * sizeof(token_t));
                (*array)[*array_size - 1] = temp;
            }
        }
        else if (character == '*') {
            temp.id = OPMUL_TOKEN;
            temp.attribut.op = MUL;
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == '/') {
            temp.id = OPMUL_TOKEN;
            temp.attribut.op = DIV;
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == '%') {
            temp.id = OPMUL_TOKEN;
            temp.attribut.op = MOD;
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == '&') {
            character = fgetc(file);
            if (character != '&') {
                free(*array);
                *array_size = 0;
                *array = NULL;
                return false;
            }
            else {
                temp.id = OPMUL_TOKEN;
                temp.attribut.op = AND;
                *array = realloc(*array, ++(*array_size) * sizeof(token_t));
                (*array)[*array_size - 1] = temp;
            }
        }
        else if (character == ':') {
            character = fgetc(file);
            if (character == '=') temp.id = ASSIGN_TOKEN;
            else {
                ungetc(character, file);
                temp.id = COLON_TOKEN;
            }
            temp.attribut.name = NULL;
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == '.') {
            temp.id = PERIOD_TOKEN;
            temp.attribut.name = NULL;
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == ',') {
            temp.id = COMMA_TOKEN;
            temp.attribut.name = NULL;
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == ';') {
            temp.id = SEMICOLON_TOKEN;
            temp.attribut.name = NULL;
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
        else if (character == '(') {
            character = fgetc(file);
            if (character == '*') {
                while (character != EOF) {
                    character = fgetc(file);
                    if (character != '*') continue;
                    character = fgetc(file);
                    if (character == ')') break;
                }
            }
            else {
                ungetc(character, file);
                temp.id = OPENING_BRACKET_TOKEN;
                temp.attribut.name = NULL;
                *array = realloc(*array, ++(*array_size) * sizeof(token_t));
                (*array)[*array_size - 1] = temp;
            }
        }
        else if (character == ')') {
            temp.id = CLOSING_BRACKET_TOKEN;
            temp.attribut.name = NULL;
            *array = realloc(*array, ++(*array_size) * sizeof(token_t));
            (*array)[*array_size - 1] = temp;
        }
    }
}
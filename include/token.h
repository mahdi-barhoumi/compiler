#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

typedef enum {
    PROGRAM_TOKEN = 0,              // program
    VAR_TOKEN = 1,                  // var
    INTEGER_TOKEN = 2,              // integer
    CHAR_TOKEN = 3,                 // char
    BEGIN_TOKEN = 4,                // begin
    END_TOKEN = 5,                  // end
    IF_TOKEN = 6,                   // if
    THEN_TOKEN = 7,                 // then
    ELSE_TOKEN = 8,                 // else
    WHILE_TOKEN = 9,                // while
    DO_TOKEN = 10,                  // do
    READ_TOKEN = 11,                // read
    READLN_TOKEN = 12,              // readln
    WRITE_TOKEN = 13,               // write
    WRITELN_TOKEN = 14,             // writeln
    ID_TOKEN = 15,                  // id
    NB_TOKEN = 16,                  // nb
    OPREL_TOKEN = 17,               // oprel
    OPADD_TOKEN = 18,               // opadd
    OPMUL_TOKEN = 19,               // opmul
    ASSIGN_TOKEN = 20,              // :=
    COLON_TOKEN = 21,               // :
    PERIOD_TOKEN = 22,              // .
    COMMA_TOKEN = 23,               // ,
    SEMICOLON_TOKEN = 24,           // ;
    OPENING_BRACKET_TOKEN = 25,     // (
    CLOSING_BRACKET_TOKEN = 26      // )
} token;
typedef enum {
    EQUAL = 0,                      // ==
    NOT_EQUAL = 1,                  // <>
    LESS_THAN = 2,                  // <
    LESS_THAN_OR_EQUAL = 3,         // <=
    GREATER_THAN = 4,               // >
    GREATER_THAN_OR_EQUAL = 5,      // >=
    ADD = 6,                        // +
    SUB = 7,                        // -
    OR = 8,                         // ||
    MUL = 9,                        // *
    DIV = 10,                       // /
    MOD = 11,                       // %
    AND = 12                        // &&
} operation;
typedef struct {
    token id;
    union {
        char* name;
        size_t value;
        operation op;
    } attribut;
} token_t;

#endif
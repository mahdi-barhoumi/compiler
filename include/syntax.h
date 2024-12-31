#include <token.h>
#include <stdlib.h>
#include <stdbool.h>

int syntax(token_t* array, size_t array_size);
bool program(void);                                 // P
bool declare(void);                                 // Dcl
bool declare_fix(void);                             // Dcl'
bool id_list(void);                                 // Liste_id
bool id_list_fix(void);                             // Liste_id'
bool type(void);                                    // Type
bool composed_instruction(void);                    // Inst_composée
bool instruction(void);                             // Inst
bool instruction_list(void);                        // Liste_inst
bool instruction_list_fix(void);                    // Liste_inst'
bool simple_instruction(void);                      // I
bool expression(void);                              // Exp
bool expression_fix(void);                          // Exp'
bool simple_expression(void);                       // Exp_simple
bool simple_expression_fix(void);                   // Exp_simple'
bool term(void);                                    // Terme
bool term_fix(void);                                // Terme'
bool factor(void);                                  // Facteur
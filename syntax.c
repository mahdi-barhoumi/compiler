#include <syntax.h>

token_t* _array;
size_t _array_size;
size_t i = 0;

int syntax(token_t* array, size_t array_size)
{
    _array = array;
    _array_size = array_size;
    if (program()) return -1;
    else return i + 1;
}
bool validate(token id)
{
    if (i < _array_size && _array[i].id == id) {
        i++;
        return true;
    }
	else return false;
}
bool program(void)
{
    if (!validate(PROGRAM_TOKEN)) return false;
    if (!validate(ID_TOKEN)) return false;
    if (!validate(SEMICOLON_TOKEN)) return false;
    if (!declare()) return false;
    if (!composed_instruction()) return false;
    return validate(PERIOD_TOKEN);
}
bool declare(void)
{
	return declare_fix();
}
bool declare_fix(void)
{
    if (_array[i].id == VAR_TOKEN) {
        if (!validate(VAR_TOKEN)) return false;
        if (!id_list()) return false;
        if (!validate(COLON_TOKEN)) return false;
        if (!type()) return false;
        if (!validate(SEMICOLON_TOKEN)) return false;
        return declare_fix();
    }
    else return true;
}
bool id_list(void)
{
    if (!validate(ID_TOKEN)) return false;
    return id_list_fix();
}
bool id_list_fix(void)
{
    if (_array[i].id == COMMA_TOKEN) {
        if (!validate(COMMA_TOKEN)) return false;
        if (!validate(ID_TOKEN)) return false;
        return id_list_fix();
    }
    else return true;
}
bool type(void)
{
    if (_array[i].id == INTEGER_TOKEN) return validate(INTEGER_TOKEN);
    else return validate(CHAR_TOKEN);
}
bool composed_instruction(void)
{
    if (!validate(BEGIN_TOKEN)) return false;
    if (!instruction()) return false;
    return validate(END_TOKEN);
}
bool instruction(void)
{
    return instruction_list();
}
bool instruction_list(void)
{
    if (!simple_instruction()) return false;
    return instruction_list_fix();
}
bool instruction_list_fix(void)
{
    if (_array[i].id == SEMICOLON_TOKEN) {
        if (!validate(SEMICOLON_TOKEN)) return false;
        if (!simple_instruction()) return false;
        return instruction_list_fix();
    }
    else return true;
}
bool simple_instruction(void)
{
    switch (_array[i].id) {
        case ID_TOKEN:
            if (!validate(ID_TOKEN)) return false;
            if (!validate(ASSIGN_TOKEN)) return false;
            return simple_expression();
        break;
        case IF_TOKEN:
            if (!validate(IF_TOKEN)) return false;
            if (!expression()) return false;
            if (!validate(THEN_TOKEN)) return false;
            if (!simple_instruction()) return false;
            if (!validate(ELSE_TOKEN)) return false;
            return simple_instruction();
        break;
        case WHILE_TOKEN:
            if (!validate(WHILE_TOKEN)) return false;
            if (!expression()) return false;
            if (!validate(DO_TOKEN)) return false;
            return simple_instruction();
        break;
        case READ_TOKEN:
            if (!validate(READ_TOKEN)) return false;
            if (!validate(OPENING_BRACKET_TOKEN)) return false;
            if (!validate(ID_TOKEN)) return false;
            return validate(CLOSING_BRACKET_TOKEN);
        break;
        case WRITE_TOKEN:
            if (!validate(WRITE_TOKEN)) return false;
            if (!validate(OPENING_BRACKET_TOKEN)) return false;
            if (!validate(ID_TOKEN)) return false;
            return validate(CLOSING_BRACKET_TOKEN);
        break;
        case READLN_TOKEN:
            if (!validate(READLN_TOKEN)) return false;
            if (!validate(OPENING_BRACKET_TOKEN)) return false;
            if (!validate(ID_TOKEN)) return false;
            return validate(CLOSING_BRACKET_TOKEN);
        break;
        case WRITELN_TOKEN:
            if (!validate(WRITELN_TOKEN)) return false;
            if (!validate(OPENING_BRACKET_TOKEN)) return false;
            if (!validate(ID_TOKEN)) return false;
            return validate(CLOSING_BRACKET_TOKEN);
        break;
        default:
            return true;
        break;
    }
}
bool expression(void)
{
    if (!simple_expression()) return false;
    return expression_fix();
}
bool expression_fix(void)
{
    if (_array[i].id == OPREL_TOKEN) {
        if (!validate(OPREL_TOKEN)) return false;
        if (!simple_expression()) return false;
        return expression_fix();
    }
    else return true;
}
bool simple_expression(void)
{
    if (!term()) return false;
    return simple_expression_fix();
}
bool simple_expression_fix(void)
{
    if (_array[i].id == OPADD_TOKEN) {
        if (!validate(OPADD_TOKEN)) return false;
        if (!term()) return false;
        return simple_expression_fix();
    }
    else return true;
}
bool term(void)
{
    if (!factor()) return false;
    return term_fix();
}
bool term_fix(void)
{
    if (_array[i].id == OPMUL_TOKEN) {
        if (!validate(OPMUL_TOKEN)) return false;
        if (!factor()) return false;
        return term_fix();
    }
    else return true;
}
bool factor(void)
{
    switch (_array[i].id) {
        case ID_TOKEN:
            return validate(ID_TOKEN);
        break;
        case NB_TOKEN:
            return validate(NB_TOKEN);
        break;
        default:
            if (!validate(OPENING_BRACKET_TOKEN)) return false;
            if (!simple_expression()) return false;
            return validate(CLOSING_BRACKET_TOKEN);
    }
}
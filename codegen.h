

#ifndef CODEGEN_H
#define CODEGEN_H

#include "tabelaSimbolos.h"
#include "ast.h"

////////////////// ESTRUTURA TACS //////////////////
typedef enum {
    TAC_SYMBOL, TAC_MOVE, TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV,
    TAC_LABEL, TAC_BEGINFUN, TAC_ENDFUN, TAC_IFZ, TAC_JUMP, TAC_CALL, TAC_ARG, TAC_RET,
    TAC_PRINT, TAC_READ
} TACType;

typedef struct tac {
    TACType type;
    Symbol *res;
    Symbol *op1;
    Symbol *op2;
    struct tac *prev;
    struct tac *next;
} TAC;


TAC* tac_create(TACType type, Symbol *res, Symbol *op1, Symbol *op2);
void tac_print(TAC *tac);
TAC* tac_join(TAC *l1, TAC *l2);

///////////////////CRIAÇÃO DE SIMBOLOS TEMPORARIOS E LABELS /////////////////////

Symbol* make_temp();
Symbol* make_label();

//////////////Q ESTRUTURA AST /////////////
/////////////// GERAÇÃO CÓDIGO INTERMEDIÁRIO /////////////////////

TAC* generate_code(ASTNode *node);

#endif


#ifndef CODEGEN_H
#define CODEGEN_H

#include "tabelaSimbolos.h"
#include "ast.h"

////////////////////////////////// ESTRUTURAS TAC'S ///////////////////////////////////////

//ENUMERAÇÃO DOS TIPOS DE TAC'S
typedef enum {
    TAC_SYMBOL, TAC_MOVE, TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV,
    TAC_LABEL, TAC_BEGINFUN, TAC_ENDFUN, TAC_IFZ, TAC_JUMP, TAC_CALL, TAC_ARG, TAC_RET,
    TAC_PRINT, TAC_READ
} TACType;

//DEFININDO A ESTRUTURA DE DADOS PARA UM TAC
typedef struct tac {
    TACType type;
    Symbol *res;
    Symbol *op1;
    Symbol *op2;
    struct tac *prev;
    struct tac *next;
} TAC;

//DECLARAÇÕES DE FUNÇÕES TAC
TAC* criarTac(TACType type, Symbol *res, Symbol *op1, Symbol *op2);
TAC* uneTacs(TAC *l1, TAC *l2);

//DECLARAÇÕES DE FUNÇÕES AUXILIARES
Symbol* make_temp();
Symbol* make_label();


//DECLARAÇÕES DE FUNÇÕES GERAÇÃO DE CÓDIGO
TAC* gerarCodigo(ASTNode *node);
void printTacCode(TAC* tac) ;
void tacPrint(TAC* tac);
#endif

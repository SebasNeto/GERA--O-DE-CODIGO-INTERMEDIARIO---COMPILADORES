

#ifndef CODEGEN_H
#define CODEGEN_H

#include "tabelaSimbolos.h"

extern ASTNode* ast_root;

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

typedef enum {
    AST_ADD, AST_SUB, AST_MUL, AST_DIV, // Operadores aritméticos
    AST_LIT_INT, AST_LIT_REAL, AST_LIT_CHAR, // Literais
    AST_ID,AST_PROGRAM, AST_ASSIGN, // Identificador
    AST_LEQ, AST_LT, AST_GT, AST_GEQ, AST_EQ, AST_NEQ,
    AST_DECL_VAR
} ASTType;

typedef struct ASTNode {
    ASTType type;
    struct ASTNode *left;
    struct ASTNode *right;
    Symbol *symbol;
} ASTNode;



TAC* tac_create(TACType type, Symbol *res, Symbol *op1, Symbol *op2);
void tac_print(TAC *tac);
TAC* tac_join(TAC *l1, TAC *l2);

///////////////////CRIAÇÃO DE SIMBOLOS TEMPORARIOS E LABELS /////////////////////

Symbol* make_temp();
Symbol* make_label();

//////////////Q ESTRUTURA AST /////////////



ASTNode* ast_create_node(ASTType type, ASTNode *left, ASTNode *right, Symbol *symbol);
void ast_free(ASTNode *node);

/////////////// GERAÇÃO CÓDIGO INTERMEDIÁRIO /////////////////////

TAC* generate_code(ASTNode *node);

#endif

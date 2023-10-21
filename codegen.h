#ifndef CODEGEN_H
#define CODEGEN_H

#define TYPE_INT    1
#define TYPE_FLOAT  2

// Enumeraçõe
typedef enum {
    TAC_SYMBOL, TAC_MOVE, TAC_SUB, TAC_VAR, TAC_DIV, TAC_ADD, TAC_MUL, 
    TAC_LABEL, TAC_BEGINFUN, TAC_ENDFUN, TAC_IFZ, TAC_JUMP, 
    TAC_CALL, TAC_ARG, TAC_RET, TAC_PRINT, TAC_READ,
    TAC_LT, TAC_GT, TAC_LEQ, TAC_GEQ, TAC_EQ, TAC_NEQ, TAC_INPUT
} TAC_TYPE;

typedef enum {
    AST_MUL,
    AST_ATTR,
    AST_IF,
    AST_IF_ELSE,
    AST_WHILE,
} AST_TYPE;

// Estruturas
typedef struct tac {
    TAC_TYPE type;
    Symbol *res;
    Symbol *op1;
    Symbol *op2;
    struct tac *prev;
} TAC;

//arvores abstrata
typedef struct ast {
    AST_TYPE type;
    struct ast *left;
    struct ast *middle;
    struct ast *right;
    Symbol* symbol;
} AST;


extern int tempCounter;
extern int labelCounter;

Symbol* makeConstant(int type, void* value);


TAC* tac_create(TAC_TYPE type, Symbol* res, Symbol* op1, Symbol* op2);
TAC* concatCode(TAC* code1, TAC* code2);
TAC* tac_join(TAC *l1, TAC *l2);
extern TAC* lastTac;
void tac_print(TAC *tac);
Symbol* makeTemp();
Symbol* makeLabel();
TAC* generateCode(AST* node);


#endif 

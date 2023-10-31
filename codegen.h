#ifndef CODEGEN_H
#define CODEGEN_H

#define TYPE_INT    1
#define TYPE_FLOAT  2

#include "tabelaSimbolos.h"

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
    AST_PROGRAM,
    AST_OP_REL,
    AST_OP_SOMA,
    AST_OP_MULT,
    AST_VAR,
    AST_LISTA_DECL,
    AST_DECL,
    AST_COM_COMP,
    AST_LITERAL,
    AST_FUNC_CALL,
    AST_ARRAY_ACCESS,
    AST_ARGS,
    AST_LITERAL_INT,
    AST_LITERAL_REAL,
    AST_LITERAL_CHAR,
    AST_FUNC_DECL,
    AST_VAR_DECL,
    AST_PARAMS,
    AST_PARAMS_VOID,
    AST_PARAMS_EMPTY,
    AST_PARAM,
    AST_DECL_LOCAIS,
    AST_LISTA_COM,
    AST_EXPR_EMPTY,
    AST_RETURN
    

    

} AST_TYPE;

// Estrutura TAC - representa o código de 3 endereçõs 
typedef struct tac {
    TAC_TYPE type; //tipo representado por TAC_TYPE
    Symbol *res; //simbolo
    Symbol *op1; //simbolo
    Symbol *op2; //simbolo
    struct tac *tacAnterior; //ponteito para o tacAnterior 
} TAC;

//arvores sintatica abstrata 
typedef struct ast {
    AST_TYPE type; //tipo do nodo 
    struct ast *filhoAEsquerda; //a + b ; filhoAquerda-> a
    struct ast *filhoMeio;
    struct ast *filhoADireita; // a + b ; filhoADireita-> b
    Symbol* symbol;
} AST;


extern int tempCounter;
extern int labelCounter;
extern AST* root;


Symbol* makeConstant(int type, void* value);


TAC* tac_create(TAC_TYPE type, Symbol* res, Symbol* op1, Symbol* op2);
TAC* concatCode(TAC* code1, TAC* code2);
TAC* tac_join(TAC *l1, TAC *l2);
extern TAC* lastTac;
void tac_print(TAC *tac);
Symbol* makeTemp();
Symbol* makeLabel();
Symbol* makeConstant(int type, void* value);

AST* createASTNode(AST_TYPE type, Symbol* symbol, AST* left, AST* right, AST* middle) ;
TAC* generateCode(AST* node);

AST* getASTGenerated() ;

void printIntermediateCode(TAC* code) ;


#endif 

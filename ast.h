#ifndef AST_H
#define AST_H

typedef struct symbol Symbol;

//TIPOS POSSIVEIS DE NÓS PARA AST
//Operadores aritméticos, literais, identificadores, declarações, tipos, 
//comandos de controle de fluxo
typedef enum {
    AST_ADD, AST_SUB, AST_MUL, AST_DIV,
    AST_LIT_INT, AST_LIT_REAL, AST_LIT_CHAR, 
    AST_ID,AST_PROGRAM, AST_ASSIGN, 
    AST_LEQ, AST_LT, AST_GT, AST_GEQ, AST_EQ, AST_NEQ,
    AST_DECL_VAR, AST_LIST_DECL, AST_DECL,
    AST_TYPE_INT, AST_TYPE_REAL, AST_TYPE_VOID, 
    AST_FUNC_DECL, AST_LIST_COM, AST_EXPR,
    AST_EMPTY, AST_COMPOUND, AST_IF, AST_IF_ELSE,
    AST_WHILE, AST_RETURN, AST_SYMBOL
} ASTType;

//ESTRUTURA PARA ASTNoDE
typedef struct ASTNode {
    ASTType type;
    struct ASTNode *left;
    struct ASTNode *right;
    Symbol *symbol;
} ASTNode;

extern ASTNode* astRaiz; //usado para ligar a raiz em outro arquivo

//DECLARAÇÕES DAS FUNÇÕES PARA ÁRVORE SINTÁTICA ABSTRATA (AST)

ASTNode* criarNoAST(ASTType type, ASTNode *left, ASTNode *right, Symbol *symbol);
void freeAST(ASTNode *node);

#endif // AST_H

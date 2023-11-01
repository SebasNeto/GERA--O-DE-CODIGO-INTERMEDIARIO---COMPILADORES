
// ast.h
#ifndef AST_H
#define AST_H

typedef struct symbol Symbol;

typedef enum {
    AST_ADD, AST_SUB, AST_MUL, AST_DIV, // Operadores aritméticos
    AST_LIT_INT, AST_LIT_REAL, AST_LIT_CHAR, // Literais
    AST_ID,AST_PROGRAM, AST_ASSIGN, // Identificador
    AST_LEQ, AST_LT, AST_GT, AST_GEQ, AST_EQ, AST_NEQ,
    AST_DECL_VAR, AST_LIST_DECL, AST_DECL,
    AST_TYPE_INT, AST_TYPE_REAL, AST_TYPE_VOID, 
    AST_FUNC_DECL, AST_LIST_COM, AST_EXPR,
    AST_EMPTY, AST_COMPOUND, AST_IF, AST_IF_ELSE,
    AST_WHILE, AST_RETURN
} ASTType;

typedef struct ASTNode {
    ASTType type;
    struct ASTNode *left;
    struct ASTNode *right;
    Symbol *symbol;
} ASTNode;

extern ASTNode* ast_root;
ASTNode* ast_create_node(ASTType type, ASTNode *left, ASTNode *right, Symbol *symbol);
void ast_free(ASTNode *node);

#endif // AST_H

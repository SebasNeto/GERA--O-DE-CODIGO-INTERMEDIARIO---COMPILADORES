#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabelaSimbolos.h"
#include "ast.h"
#include "codegen.h"

//VARIÁVEL GLOBAL QUE ARMAZENA A RAIZ DA AST
ASTNode* astRaiz = NULL;

////////////////////////////////// ESTRUTURA AST ///////////////////////////////////////////

//FUNÇÃO QUE CRIA UM NÓ PARA AST
ASTNode* criarNoAST(ASTType type, ASTNode *left, ASTNode *right, Symbol *symbol) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->left = left;
    node->right = right;
    node->symbol = symbol;
    return node;
}

//FUNÇÃO RECURSIVA QUE LIBERA A MEMÓRIA PARA NÓS DA AST
void freeAST(ASTNode *node) {
    if (!node) return;
    freeAST(node->left);
    freeAST(node->right);
    free(node);
}
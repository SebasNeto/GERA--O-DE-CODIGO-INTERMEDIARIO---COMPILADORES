#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabelaSimbolos.h"
#include "ast.h"
#include "codegen.h"

//////////////Q ESTRUTURA AST /////////////

ASTNode* ast_create_node(ASTType type, ASTNode *left, ASTNode *right, Symbol *symbol) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->left = left;
    node->right = right;
    node->symbol = symbol;
    return node;
}

void ast_free(ASTNode *node) {
    if (!node) return;
    ast_free(node->left);
    ast_free(node->right);
    free(node);
}
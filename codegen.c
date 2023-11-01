
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabelaSimbolos.h"
#include "ast.h"
#include "codegen.h"

////////////////// ESTRUTURA TACS //////////////////

TAC* tac_create(TACType type, Symbol *res, Symbol *op1, Symbol *op2) {
    TAC *newtac = (TAC*)malloc(sizeof(TAC));
    newtac->type = type;
    newtac->res = res;
    newtac->op1 = op1;
    newtac->op2 = op2;
    newtac->prev = NULL;
    newtac->next = NULL;
    return newtac;
}

void tac_print(TAC *tac) {
    if (!tac) return;
    printf("TAC(%d): %s, %s, %s\n", tac->type,
           tac->res ? tac->res->identifier : "NULL",
           tac->op1 ? tac->op1->identifier : "NULL",
           tac->op2 ? tac->op2->identifier : "NULL");
}

TAC* tac_join(TAC *l1, TAC *l2) {
    TAC *p;
    if (!l1) return l2;
    if (!l2) return l1;

    for (p = l2; p->prev; p = p->prev)
        ;
    p->prev = l1;
    return l2;
}

///////////////////CRIAÇÃO DE SIMBOLOS TEMPORARIOS E LABELS /////////////////////

static int tempCount = 0;
static int labelCount = 0;

Symbol* make_temp() {
    char tempName[20];
    sprintf(tempName, "__temp%d", tempCount++);
    return inserirSimbolo(SYMBOL_SCALAR, tempName);
}

Symbol* make_label() {
    char labelName[20];
    sprintf(labelName, "__label%d", labelCount++);
    return inserirSimbolo(SYMBOL_LABEL, labelName);
}


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

/////////////// GERAÇÃO CÓDIGO INTERMEDIÁRIO /////////////////////

TAC* generate_code(ASTNode *node) {
    if (!node) return NULL;

    TAC *codeLeft = generate_code(node->left);
    TAC *codeRight = generate_code(node->right);

    TAC *result = NULL;

    switch (node->type) {
        case AST_ADD: {
            Symbol *temp = make_temp();
            result = tac_create(TAC_ADD, temp, node->left->symbol, node->right->symbol);
            break;
        }
        case AST_SUB: {
            Symbol *temp = make_temp();
            result = tac_create(TAC_SUB, temp, node->left->symbol, node->right->symbol);
            break;
        }
        case AST_MUL: {
            Symbol *temp = make_temp();
            result = tac_create(TAC_MUL, temp, node->left->symbol, node->right->symbol);
            break;
        }
        case AST_DIV: {
            Symbol *temp = make_temp();
            result = tac_create(TAC_DIV, temp, node->left->symbol, node->right->symbol);
            break;
        }
        case AST_LIT_INT:
        case AST_LIT_REAL:
        case AST_LIT_CHAR:
        case AST_ID: {
            result = tac_create(TAC_SYMBOL, node->symbol, NULL, NULL);
            break;
        }
    }

    return tac_join(tac_join(codeLeft, codeRight), result);
}
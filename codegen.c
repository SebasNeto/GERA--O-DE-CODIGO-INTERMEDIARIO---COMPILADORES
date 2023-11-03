
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabelaSimbolos.h"
#include "ast.h"
#include "codegen.h"

///////////////////////////////// ESTRUTURAS TACS //////////////////////////////////////

//FUNÇÃO QUE CRIA UM NOVO CÓDIGO DE 3 ENDEREÇOS
TAC* criarTac(TACType type, Symbol *res, Symbol *op1, Symbol *op2) {
    TAC *novoTac = (TAC*)malloc(sizeof(TAC));
    novoTac->type = type;
    novoTac->res = res;
    novoTac->op1 = op1;
    novoTac->op2 = op2;
    novoTac->prev = NULL;
    novoTac->next = NULL;
    return novoTac;
}

//FUNÇÃO QUE UNE DUAS LISTAS TAC'S 
TAC* uneTacs(TAC *l1, TAC *l2) {
    TAC *p;
    if (!l1) return l2;
    if (!l2) return l1;

    for (p = l2; p->prev; p = p->prev)
        ;
    p->prev = l1;
    return l2;
}


///////////////////// CRIAÇÃO DE SIMBOLOS TEMPORARIOS E LABELS /////////////////////

static int tempCount = 0;
static int labelCount = 0;

//FUNÇÃO QUE CRIA UM SIMBOLO TEMPORÁRIO COM UM NOME ÚNICO
Symbol* make_temp() {
    char tempName[20];
    sprintf(tempName, "__temp%d", tempCount++);
    return inserirSimbolo(SYMBOL_SCALAR, tempName);
}

//FUNÇÃO QUE CRIA UM NOVO ROTULO COM UM NOME ÚNICO
Symbol* make_label() {
    char labelName[20];
    sprintf(labelName, "__label%d", labelCount++);
    return inserirSimbolo(SYMBOL_LABEL, labelName);
}


/////////////////////////// ESTRUTURAS PARA GERAÇÃO DO CÓDIGO INTERMEDIÁRIO //////////////////////////////////

//FUNÇÃO RESPONSÁVEL POR GERAR O CÓDIGO INTERMEDIÁRIO
TAC* gerarCodigo(ASTNode *node) {

    if (!node){
        fprintf(stderr,"Erro: Nó vazio!\n");
        return NULL;
    }

    TAC *code1, *code2, *result;
    Symbol *label, *temp;

    switch (node->type) {
        case AST_PROGRAM:
            code1 = gerarCodigo(node->left);
            code2 = gerarCodigo(node->right);
            return uneTacs(code1, code2);

        case AST_DECL_VAR:
            return criarTac(TAC_SYMBOL, node->symbol, NULL, NULL);

        case AST_ID:
            return criarTac(TAC_SYMBOL, node->symbol, NULL, NULL);

        case AST_LIT_INT:
            temp = make_temp();
            return criarTac(AST_LIT_INT, temp, node->symbol, NULL);

        case AST_LIT_REAL:
            temp = make_temp();
            return criarTac(AST_LIT_REAL, temp, node->symbol, NULL);

        case AST_LIT_CHAR:
            temp = make_temp(); 
            return criarTac(AST_LIT_CHAR, temp, node->symbol, NULL);
        
        case AST_ASSIGN:
            code1 = gerarCodigo(node->left);
            code2 = gerarCodigo(node->right);
            result = criarTac(TAC_MOVE, code1->res, code2->res, NULL);
            return uneTacs(uneTacs(code1, code2), result);

        case AST_SYMBOL:
            printf("Depuração: Nó AST_SYMBOL encontrado.\n");
            if (!node->symbol) return NULL;
            return criarTac(TAC_SYMBOL, node->symbol, NULL, NULL);

        case AST_ADD:
            printf("Depuração: Nó AST_ADD encontrado.\n");
            code1 = gerarCodigo(node->left);
            code2 = gerarCodigo(node->right);
            if (!code1 || !code2) return NULL;
            result = criarTac(TAC_ADD, make_temp(), code1 ? code1->res : NULL, code2 ? code2->res : NULL);
            return uneTacs(uneTacs(code1, code2), result);

        case AST_SUB:
             printf("Depuração: Nó AST_SUB encontrado.\n");
            code1 = gerarCodigo(node->left);
            code2 = gerarCodigo(node->right);
            if (!code1 || !code2) return NULL;
            result = criarTac(TAC_SUB, make_temp(), code1 ? code1->res : NULL, code2 ? code2->res : NULL);
            return uneTacs(uneTacs(code1, code2), result);
        
        case AST_MUL:
            code1 = gerarCodigo(node->left);
            code2 = gerarCodigo(node->right);
            result = criarTac(TAC_MUL, make_temp(), code1->res, code2->res);
            return uneTacs(uneTacs(code1, code2), result);

        case AST_DIV:
            code1 = gerarCodigo(node->left);
            code2 = gerarCodigo(node->right);
            result = criarTac(TAC_DIV, make_temp(), code1->res, code2->res);
            return uneTacs(uneTacs(code1, code2), result);

        case AST_IF:
            printf("Depuração: Nó AST_IF encontrado.\n");
            code1 = gerarCodigo(node->left);
            code2 = gerarCodigo(node->right);
            if (!code1 || !code2) return NULL;
            Symbol *label = make_label();
            TAC *jumpIfFalse = criarTac(TAC_IFZ, label, code1 ? code1->res : NULL, NULL);
            TAC *labelTac = criarTac(TAC_LABEL, label, NULL, NULL);
            return uneTacs(uneTacs(uneTacs(code1, jumpIfFalse), code2), labelTac);
        
        default:
            printf("Tipo de nó AST não reconhecido: %d\n", node->type);
            printf("Endereço do símbolo não reconhecido: %p\n", (void*)node->symbol);
            return NULL;
    }
}

//FUNÇÃO QUE ITERA NA LISTA DE TACS'S E IMPRIME
void printTacCode(TAC* tac) {
    printf("Código Intermediário TAC:\n");
    while (tac != NULL) {
        tacPrint(tac);
        tac = tac->next;
    }
}

//FUNÇÃO RESPONSÁVEL POR IMPRIMIR TAC'S DISPÓNIVEIS 
void tacPrint(TAC* tac) {
    if (!tac) return;

    printf("TAC: ");

    switch (tac->type) {
        case TAC_SYMBOL: printf("TAC_SYMBOL, "); break;
        case TAC_MOVE: printf("TAC_MOVE, "); break;
        case TAC_ADD: printf("TAC_ADD, "); break;
        case TAC_SUB: printf("TAC_SUB, "); break;
        case TAC_MUL: printf("TAC_MUL, "); break;
        case TAC_DIV: printf("TAC_DIV, "); break;
        case TAC_LABEL: printf("TAC_LABEL, "); break;
        case TAC_BEGINFUN: printf("TAC_BEGINFUN, "); break;
        case TAC_ENDFUN: printf("TAC_ENDFUN, "); break;
        case TAC_IFZ: printf("TAC_IFZ, "); break;
        case TAC_JUMP: printf("TAC_JUMP, "); break;
        case TAC_CALL: printf("TAC_CALL, "); break;
        case TAC_ARG: printf("TAC_ARG, "); break;
        case TAC_RET: printf("TAC_RET, "); break;
        case TAC_PRINT: printf("TAC_PRINT, "); break;
        case TAC_READ: printf("TAC_READ, "); break;
        default: printf("UNKNOWN, ");
    }

    // Imprimir o resultado
    if (tac->res) printf("Resultado: %s, ", tac->res->identifier);

    // Imprimir os operandos
    if (tac->op1) printf("Operando 1: %s, ", tac->op1->identifier);
    if (tac->op2) printf("Operando 2: %s, ", tac->op2->identifier);

    printf("\n");
}

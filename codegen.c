#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "tabelaSimbolos.h"
#include "codegen.h"

TAC* lastTac = NULL;

TAC* tac_create(TAC_TYPE type, Symbol* res, Symbol* op1, Symbol* op2) {
    TAC *novoTac = (TAC*) malloc(sizeof(TAC));
    novoTac->type = type;
    novoTac->res = res;
    novoTac->op1 = op1;
    novoTac->op2 = op2;
    novoTac->prev = NULL;
    return novoTac;
}

TAC* concatCode(TAC* code1, TAC* code2) {
    if (!code1) return code2;
    if (!code2) return code1;

    TAC* pointer = code2;
    while (pointer->prev) {
        pointer = pointer->prev;
    }
    pointer->prev = code1;
    lastTac = code2;

    return code2;
}

TAC* tac_join(TAC *l1, TAC *l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    TAC *tac = l2;
    while (tac->prev) {
        tac = tac->prev;
    }
    tac->prev = l1;
    return l2;
}

void tac_print(TAC *tac) {
    if (!tac) return;
    char* op1 = tac->op1 ? tac->op1->identifier : "";
    char* op2 = tac->op2 ? tac->op2->identifier : "";
    char* res = tac->res ? tac->res->identifier : "";

    switch (tac->type) {
        case TAC_SYMBOL:
            printf("(SYMBOL, , , %s)\n", res);
            break;
        case TAC_MOVE:
            printf("(=, %s, , %s)\n", op1, res);
            break;
        case TAC_ADD:
            printf("(+, %s, %s, %s)\n", op1, op2, res);
            break;
        case TAC_SUB:
            printf("(-, %s, %s, %s)\n", op1, op2, res);
            break;
        case TAC_MUL:
            printf("(*, %s, %s, %s)\n", op1, op2, res);
            break;
        case TAC_DIV:
            printf("(/, %s, %s, %s)\n", op1, op2, res);
            break;
        case TAC_LT:
            printf("(<, %s, %s, %s)\n", op1, op2, res);
            break;
        case TAC_GT:
            printf("(>, %s, %s, %s)\n", op1, op2, res);
            break;
        case TAC_LEQ:
            printf("(<=, %s, %s, %s)\n", op1, op2, res);
            break;
        case TAC_GEQ:
            printf("(>=, %s, %s, %s)\n", op1, op2, res);
            break;
        case TAC_EQ:
            printf("(==, %s, %s, %s)\n", op1, op2, res);
            break;
        case TAC_NEQ:
            printf("(!=, %s, %s, %s)\n", op1, op2, res);
            break;
        case TAC_INPUT:
            printf("(INPUT, , , %s)\n", res);
            break;
        case TAC_IFZ:
            printf("(IFZ, %s, , %s)\n", op1, res);
            break;
        case TAC_JUMP:
            printf("(JUMP, , , %s)\n", res);
            break;
        case TAC_LABEL:
            printf("(LABEL, , , %s)\n", res);
            break;
        case TAC_BEGINFUN:
            printf("(BEGINFUN, , , %s)\n", res);
            break;
        case TAC_ENDFUN:
            printf("(ENDFUN, , , %s)\n", res);
            break;
        default:
            printf("(UNKNOWN)\n");
            break;
    }
}


int tempCounter = 0;
int labelCounter = 0;

Symbol* makeTemp() {
    char buffer[256];
    sprintf(buffer, "__temp%d", tempCounter++);
    return inserirSimbolo(buffer, SYMBOL_SCALAR);
}

// Função para criar uma nova label
Symbol* makeLabel() {
    char buffer[256];
    sprintf(buffer, "__label%d", labelCounter++);
    return inserirSimbolo(buffer, SYMBOL_LABEL);
}

Symbol* makeConstant(int type, void* value) {
    char buffer[32];
    
    if (type == TYPE_INT) {
        int intValue = *(int*)value;
        snprintf(buffer, sizeof(buffer), "%d", intValue);
    } else if (type == TYPE_FLOAT) {
        float floatValue = *(float*)value;
        snprintf(buffer, sizeof(buffer), "%.2f", floatValue); 
    } else {

        return NULL;
    }

    Symbol* sym = retornaSimbolo(buffer);
    if (!sym) {
        sym = inserirSimbolo(buffer, SYMBOL_SCALAR);  
    }
    
    return sym;
}


TAC* generateCode(AST* node) {
    if (!node) return NULL;

    TAC* code[3], *result;
    Symbol* novoSimbolo;
    Symbol* labelBegin, *labelEnd;

    switch (node->type) {
        case AST_MUL:  // Multiplicação
            code[0] = generateCode(node->left);
            code[1] = generateCode(node->right);
            novoSimbolo = makeTemp();
            result = tac_create(TAC_MUL, novoSimbolo, node->left->symbol, node->right->symbol);
            return concatCode(concatCode(code[0], code[1]), result);

        case AST_ATTR:  // Atribuição
            code[0] = generateCode(node->right);
            result = tac_create(TAC_MOVE, node->left->symbol, node->right->symbol, NULL);
            return concatCode(code[0], result);

        case AST_IF:  // If sem else
            code[0] = generateCode(node->left);  // Condição
            code[1] = generateCode(node->right);  // Corpo do if
            labelEnd = makeLabel();
            result = tac_create(TAC_IFZ, labelEnd, node->left->symbol, NULL);
            return concatCode(concatCode(concatCode(code[0], result), code[1]), tac_create(TAC_LABEL, labelEnd, NULL, NULL));

        case AST_IF_ELSE:  // If com else
            code[0] = generateCode(node->left);  // Condição
            code[1] = generateCode(node->middle);  // Corpo do if
            code[2] = generateCode(node->right);  // Corpo do else
            labelEnd = makeLabel();
            Symbol* labelElse = makeLabel();
            result = tac_create(TAC_IFZ, labelElse, node->left->symbol, NULL);
            return concatCode(concatCode(concatCode(concatCode(concatCode(code[0], result), code[1]), tac_create(TAC_JUMP, labelEnd, NULL, NULL)), tac_create(TAC_LABEL, labelElse, NULL, NULL)), code[2]);

        case AST_WHILE:  // Loop while
            code[0] = generateCode(node->left);  // Condição
            code[1] = generateCode(node->right);  // Corpo do loop
            labelBegin = makeLabel();
            labelEnd = makeLabel();
            result = tac_create(TAC_IFZ, labelEnd, node->left->symbol, NULL);
            return concatCode(concatCode(concatCode(concatCode(concatCode(tac_create(TAC_LABEL, labelBegin, NULL, NULL), code[0]), result), code[1]), tac_create(TAC_JUMP, labelBegin, NULL, NULL)), tac_create(TAC_LABEL, labelEnd, NULL, NULL));

        default:
            return NULL;
    }
}

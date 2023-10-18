#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "tabelaSimbolos.h"

typedef enum {
    TAC_SYMBOL, TAC_MOVE, TAC_ADD, TAC_MUL, 
    TAC_LABEL, TAC_BEGINFUN, TAC_ENDFUN, TAC_IFZ, TAC_JUMP, 
    TAC_CALL, TAC_ARG, TAC_RET, TAC_PRINT, TAC_READ
    // Adicione outros tipos conforme necessário
} TAC_TYPE;

typedef struct tac {
    TAC_TYPE type;
    Symbol *res;  // Resultado
    Symbol *op1;  // Operando 1
    Symbol *op2;  // Operando 2
    struct tac *prev;  // TAC anterior
} TAC;

// Função para criar uma nova instrução TAC
TAC* tac_create(TAC_TYPE type, struct hash_node *res, struct hash_node *op1, struct hash_node *op2) {
    TAC *newtac = (TAC*) malloc(sizeof(TAC));
    newtac->type = type;
    newtac->res = res;
    newtac->op1 = op1;
    newtac->op2 = op2;
    newtac->prev = NULL;
    return newtac;
}

TAC* concatCode(TAC* code1, TAC* code2) {
    if (!code1) return code2;
    if (!code2) return code1;

    TAC* pointer = code2;
    while (pointer->prev) {
        pointer = pointer->prev;
    }
    pointer->prev = code1;
    return code2;
}


// Função para juntar duas listas de TACs
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


// Função para imprimir uma lista de TACs (para depuração)
void tac_print(TAC *tac) {
    if (!tac) {
        printf("Empty TAC list\n");
        return;
    }

    while (tac) {
        switch (tac->type) {
            case TAC_SYMBOL:
                printf("TAC (SYMBOL): %s\n", tac->res->identifier);
                break;
            case TAC_MOVE:
                printf("TAC (MOVE): %s = %s\n", tac->res->identifier, tac->op1->identifier);
                break;
            case TAC_ADD:
                printf("TAC (ADD): %s = %s + %s\n", tac->res->identifier, tac->op1->identifier, tac->op2->identifier);
                break;
            case TAC_MUL:
                printf("TAC (MUL): %s = %s * %s\n", tac->res->identifier, tac->op1->identifier, tac->op2->identifier);
                break;
            case TAC_LABEL:
                printf("TAC (LABEL): %s\n", tac->res->identifier);
                break;
            case TAC_BEGINFUN:
                printf("TAC (BEGINFUN): %s\n", tac->res->identifier);
                break;
            case TAC_ENDFUN:
                printf("TAC (ENDFUN): %s\n", tac->res->identifier);
                break;
            case TAC_IFZ:
                printf("TAC (IFZ): IF %s == 0 GOTO %s\n", tac->op1->identifier, tac->res->identifier);
                break;
            case TAC_JUMP:
                printf("TAC (JUMP): GOTO %s\n", tac->res->identifier);
                break;
            // ... Adicione cases para outros tipos conforme necessário
            default:
                printf("Unknown TAC type\n");
                break;
        }
        tac = tac->prev;
    }
}

int tempCounter = 0;
int labelCounter = 0;

// Função para criar um novo símbolo temporário na tabela de símbolos (hash)
struct hash_node* makeTemp() {
    char buffer[256];
    sprintf(buffer, "__temp%d", tempCounter++);
    return inserirSimbolo(buffer, SYMBOL_SCALAR);  // Supondo que você tenha uma função hashInsert para inserir na tabela de símbolos
}

// Função para criar uma nova label
struct hash_node* makeLabel() {
    char buffer[256];
    sprintf(buffer, "__label%d", labelCounter++);
    return inserirSimbolo(buffer, SYMBOL_LABEL); // Supondo que você tenha uma função hashInsert para inserir na tabela de símbolos
}

typedef enum {
    AST_MUL,
    AST_ATTR,
    AST_IF,
    AST_IF_ELSE,
    AST_WHILE,
} AST_TYPE;

typedef struct ast {
    AST_TYPE type;
    struct ast *left;
    struct ast *middle;
    struct ast *right;
    Symbol* symbol;  // se você estiver armazenando símbolos associados ao nodo
} AST;

TAC* generateCode(AST* node) {
    if (!node) return NULL;

    TAC* code[3], *result;
    Symbol* newSymbol;
    Symbol* labelBegin, *labelEnd;

    switch (node->type) {
        case AST_MUL:  // Multiplicação
            code[0] = generateCode(node->left);
            code[1] = generateCode(node->right);
            newSymbol = makeTemp();
            result = createTAC(TAC_MUL, newSymbol, node->left->symbol, node->right->symbol);
            return concatCode(concatCode(code[0], code[1]), result);

        case AST_ATTR:  // Atribuição
            code[0] = generateCode(node->right);
            result = createTAC(TAC_MOVE, node->left->symbol, node->right->symbol, NULL);
            return concatCode(code[0], result);

        case AST_IF:  // If sem else
            code[0] = generateCode(node->left);  // Condição
            code[1] = generateCode(node->right);  // Corpo do if
            labelEnd = makeLabel();
            result = createTAC(TAC_IFZ, labelEnd, node->left->symbol, NULL);
            return concatCode(concatCode(concatCode(code[0], result), code[1]), createTAC(TAC_LABEL, labelEnd, NULL, NULL));

        case AST_IF_ELSE:  // If com else
            code[0] = generateCode(node->left);  // Condição
            code[1] = generateCode(node->middle);  // Corpo do if
            code[2] = generateCode(node->right);  // Corpo do else
            labelEnd = makeLabel();
            Symbol* labelElse = makeLabel();
            result = createTAC(TAC_IFZ, labelElse, node->left->symbol, NULL);
            return concatCode(concatCode(concatCode(concatCode(concatCode(code[0], result), code[1]), createTAC(TAC_JUMP, labelEnd, NULL, NULL)), createTAC(TAC_LABEL, labelElse, NULL, NULL)), code[2]);

        case AST_WHILE:  // Loop while
            code[0] = generateCode(node->left);  // Condição
            code[1] = generateCode(node->right);  // Corpo do loop
            labelBegin = makeLabel();
            labelEnd = makeLabel();
            result = createTAC(TAC_IFZ, labelEnd, node->left->symbol, NULL);
            return concatCode(concatCode(concatCode(concatCode(concatCode(createTAC(TAC_LABEL, labelBegin, NULL, NULL), code[0]), result), code[1]), createTAC(TAC_JUMP, labelBegin, NULL, NULL)), createTAC(TAC_LABEL, labelEnd, NULL, NULL));

        // ... Outros casos para diferentes nodos

        default:
            return NULL;
    }
}

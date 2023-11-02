// simboloTabela.c

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tabelaSimbolos.h"
#include "codegen.h" 

Symbol* simboloTabela[TABLE_SIZE];

/////////////////////////////////////////////////// ESTRUTURA TABELA DE SIMBOLOS /////////////////////////////////////////////////


//FUNÇÃO RESPONSÁVEL POR INICIAR A TABELA DE SIMBOLOS - CHAMADA NA MAIN
void iniciarTabela() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        simboloTabela[i] = NULL;
    }
}

//FUNÇÃO QUE CALCULA UM VALOR DE HASH PARA UM IDENTIFICADOR
unsigned int hash(char* key) {
    unsigned int valor = 0;
    for (char* p = key; *p != '\0'; p++) {
        valor = valor * 37 + *p;
    }
    return valor % TABLE_SIZE;
}

//FUNÇÃO QUE INSERE UM NOVO SIMBOLO NA TABELA 
Symbol* inserirSimbolo( int type, char* identifier) {

    unsigned int slot = hash(identifier);
    Symbol* novoSimbolo = (Symbol*) malloc(sizeof(Symbol));
    novoSimbolo->identifier = strdup(identifier);
    novoSimbolo->type = type;
    novoSimbolo->scope = 0;  
    novoSimbolo->offset = 0; 
    novoSimbolo->nParams = 0;
    novoSimbolo->paramsList = NULL;
    novoSimbolo->label = NULL;
    novoSimbolo->tempReg = NULL;
    novoSimbolo->next = NULL;

    // Se o slot estiver vazio, insira diretamente
    if (simboloTabela[slot] == NULL) {
        simboloTabela[slot] = novoSimbolo;
    } else {
        // Caso contrário, anexe ao final da lista no slot
        Symbol* linhaCorrente = simboloTabela[slot];
        while (linhaCorrente->next != NULL) {
            linhaCorrente = linhaCorrente->next;
        }
        linhaCorrente->next = novoSimbolo;
    }

    printf("Símbolo inserido: %s\n", identifier);
    //printf("type: %d\n", type);

    return novoSimbolo;
}

//FUNÇÃO QUE PROCURA UM SIMBOLO NA TABELA USANDO UM ID
Symbol* retornaSimbolo(char* identifier) {
    unsigned int slot = hash(identifier);
    Symbol* linhaCorrente = simboloTabela[slot];
    while (linhaCorrente != NULL) {
        if (strcmp(linhaCorrente->identifier, identifier) == 0) {
            return linhaCorrente;
        }
        linhaCorrente = linhaCorrente->next;
    }
    return NULL;
}

//FUNÇÃO QUE REMOVE UM SIBOLO ESPECIFICO DA TABELA DE SIMBOLOS
void removerSimbolo(char* identifier) {
    unsigned int slot = hash(identifier);
    Symbol* anterior = NULL;
    Symbol* linhaCorrente = simboloTabela[slot];

    while (linhaCorrente && strcmp(linhaCorrente->identifier, identifier)) {
        anterior = linhaCorrente;
        linhaCorrente = linhaCorrente->next;
    }

    if (linhaCorrente) {
        if (anterior) {
            anterior->next = linhaCorrente->next;
        } else {
            simboloTabela[slot] = linhaCorrente->next;
        }
        free(linhaCorrente->identifier);
        free(linhaCorrente);
    }
}

//FUNÇÃO QUE IMPRIME O CONTEÚDO DA TABELA DE SIMBOLOS
void print_simboloTabela() {
    printf("Tabela de Símbolos:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol* linhaCorrente = simboloTabela[i];
        while (linhaCorrente != NULL) {
            printf("Slot %d: ID = %s, Tipo = %d\n", i, linhaCorrente->identifier, linhaCorrente->type);
            linhaCorrente = linhaCorrente->next;
        }
    }
}

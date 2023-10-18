// simboloTabela.c

#include "tabelaSimbolos.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Symbol* simboloTabela[TABLE_SIZE];

void iniciarTabela() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        simboloTabela[i] = NULL;
    }
}

unsigned int hash(char* key) {
    unsigned int valor = 0;
    for (char* p = key; *p != '\0'; p++) {
        valor = valor * 37 + *p;
    }
    return valor % TABLE_SIZE;
}

Symbol* inserirSimbolo(char* identifier, int type) {
    unsigned int slot = hash(identifier);
    Symbol* novoSimbolo = (Symbol*) malloc(sizeof(Symbol));
    novoSimbolo->identifier = strdup(identifier);
    novoSimbolo->type = type;
    novoSimbolo->scope = 0;  // padrão para global; altere conforme necessário
    novoSimbolo->offset = 0; // a ser determinado posteriormente
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

    return novoSimbolo;
}

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


#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "codegen.h"

#define SYMBOL_SCALAR 1
#define SYMBOL_LABEL  2
#define TABLE_SIZE 100

typedef struct ASTNode ASTNode;

//ESTRUTURA QUE REPRESENTA UM SIMBOLO NA TABELA DE SIMBOLOS
typedef struct symbol {
    char* identifier;
    int type;
    int scope;  
    int offset; 
    int nParams; 
    struct symbol* paramsList; 
    char* label; 
    char* tempReg; 
    struct symbol* next;
} Symbol;


//DEFINIÇÃO DAS FUNÇÕES PRESENTE NA TABELA DE SIMBOLOS

void iniciarTabela();
unsigned int hash(char* key);
Symbol* inserirSimbolo( int type, char* identifier);
Symbol* retornaSimbolo(char* identifier);
void removerSimbolo(char* identifier);
void print_simboloTabela();
void print_simboloTabela() ;

#endif
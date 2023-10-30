%{

#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"
#include "tabelaSimbolos.h"
#include "codegen.h"

extern int yylex();
extern char* yytext;
extern int yylineno;

int getLineNumber(void);
void yyerror(const char *s);

%}

//tipos de dados dos simbolos terminais e nao terminais
%union {
    int intValue;
    float floatValue;
    char* strValue;
    Symbol* symbolEntry;
    TAC* tac;        
}

//%type - tipo de dado de um simbolo nao terminal
%token <strValue> ID
%type<tac> comando
%type<tac> init_val
%type<intValue> op_relac
%type<tac> exp_simples
%type<intValue> espec_tipo
%type<strValue> var
%token<intValue> LIT_INT
%token<floatValue> LIT_REAL
%type<tac> decl_var com_atrib com_selecao com_repeticao exp exp_soma exp_mult
%token INT VOID
%token LIT_CHAR
%token LOOP
%token INPUT
%token IF ELSE WHILE RETURN
%token EQ LEQ LT GT GEQ NEQ PLUS MINUS TIMES DIV MOD
%token<intValue> KW_CHAR KW_INT KW_REAL
%start programa

%%

programa: lista_decl lista_com;

lista_decl: lista_decl decl
          | decl
          ;

decl: decl_var
    | decl_func
    ;

decl_func: /* Temporário */
    ID '(' ')' ';' 
    ;

decl_var: espec_tipo var '=' init_val ';'
{
    Symbol* sym = retornaSimbolo($2);
    if (sym) {
        yyerror("Variable already declared");
        exit(1);
    } else {
        inserirSimbolo($2, $1);
    }
    $$ = concatCode($4, tac_create(TAC_MOVE, retornaSimbolo($2), NULL, $4->res));
}
| espec_tipo var ';'
{
    Symbol* sym = retornaSimbolo($2);
    if (sym) {
        yyerror("Variable already declared");
        exit(1);
    } else {
        inserirSimbolo($2, $1);
    }
    $$ = NULL;
}
;


init_val: LIT_INT 
    { 
        $$ = tac_create(TAC_MOVE, makeTemp(), makeConstant(TYPE_INT, &$1), NULL); 
    }
    | LIT_REAL
    {
        $$ = tac_create(TAC_MOVE, makeTemp(), makeConstant(TYPE_FLOAT, &$1), NULL);
    }
    | INPUT '(' espec_tipo ')' 
    { 
        $$ = tac_create(TAC_INPUT, makeTemp(), NULL, NULL); 
    }
;

var: ID { $$ = $1; } ;

espec_tipo: KW_INT { $$ = 1; }
          | KW_CHAR { $$ = 2; }
          ;

lista_com: lista_com comando
| comando
;


com_atrib: var '=' exp ';'
{
    $$ = concatCode($3, tac_create(TAC_MOVE, retornaSimbolo($1), NULL, $3->res));
};

comando:
    '{' lista_com '}'  
|   com_atrib          
|   com_selecao        
|   com_repeticao      
;

com_selecao: IF '(' exp ')' comando
{
    Symbol* newLabel = makeLabel();
    $$ = concatCode($3, tac_create(TAC_IFZ, $3->res, newLabel, NULL));
    $$ = tac_join($$, $5);
    $$ = concatCode($$, tac_create(TAC_LABEL, newLabel, NULL, NULL));
}
| IF '(' exp ')' comando ELSE comando
{
    Symbol* elseLabel = makeLabel();
    Symbol* endLabel = makeLabel();
    $$ = concatCode($3, tac_create(TAC_IFZ, $3->res, elseLabel, NULL));
    $$ = tac_join($$, $5);
    $$ = concatCode($$, tac_create(TAC_JUMP, endLabel, NULL, NULL));
    $$ = concatCode($$, tac_create(TAC_LABEL, elseLabel, NULL, NULL));
    $$ = tac_join($$, $7);
    $$ = concatCode($$, tac_create(TAC_LABEL, endLabel, NULL, NULL));
}
;

com_repeticao: WHILE '(' exp ')' comando
{
    Symbol* beginLabel = makeLabel();
    Symbol* endLabel = makeLabel();
    $$ = tac_create(TAC_LABEL, beginLabel, NULL, NULL);
    $$ = concatCode($$, $3);
    $$ = concatCode($$, tac_create(TAC_IFZ, $3->res, endLabel, NULL));
    $$ = tac_join($$, $5);
    $$ = concatCode($$, tac_create(TAC_JUMP, beginLabel, NULL, NULL));
    $$ = concatCode($$, tac_create(TAC_LABEL, endLabel, NULL, NULL));
}
;

exp: exp_soma op_relac exp_soma
{
    int tacType;
    switch($2) {
        case LT: tacType = TAC_LT; break;
        case GT: tacType = TAC_GT; break;
        case LEQ: tacType = TAC_LEQ; break;
        case GEQ: tacType = TAC_GEQ; break;
        case EQ: tacType = TAC_EQ; break;
        case NEQ: tacType = TAC_NEQ; break;
        default: yyerror("Invalid relational operator"); exit(1);
    }
    $$ = concatCode($1, $3);
    $$ = concatCode($$, tac_create(tacType, makeTemp(), $1->res, $3->res));
}
| exp_soma
{
    $$ = $1;
}
;

op_relac:
    EQ { $$ = TAC_EQ; }
|   NEQ { $$ = TAC_NEQ; }
|   LT { $$ = TAC_LT; }
|   GT { $$ = TAC_GT; }
|   LEQ { $$ = TAC_LEQ; }
|   GEQ { $$ = TAC_GEQ; }
;

exp_soma: exp_soma '+' exp_mult
{
    $$ = concatCode($1, $3);
    $$ = concatCode($$, tac_create(TAC_ADD, makeTemp(), $1->res, $3->res));
}
| exp_soma '-' exp_mult
{
    $$ = concatCode($1, $3);
    $$ = concatCode($$, tac_create(TAC_SUB, makeTemp(), $1->res, $3->res));
}
| exp_mult
{
    $$ = $1;
}
;

exp_mult: exp_mult '*' exp_simples
{
    $$ = concatCode($1, $3);
    $$ = concatCode($$, tac_create(TAC_MUL, makeTemp(), $1->res, $3->res));
}
| exp_mult '/' exp_simples
{
    $$ = concatCode($1, $3);
    $$ = concatCode($$, tac_create(TAC_DIV, makeTemp(), $1->res, $3->res));
}
| exp_simples
{
    $$ = $1;
}
;

exp_simples: 
    LIT_INT 
    { 
        Symbol* temp = makeTemp();
        $$ = tac_create(TAC_MOVE, temp, makeConstant(TYPE_INT, &$1), NULL);
    }
    | LIT_REAL
    {
        Symbol* temp = makeTemp();
        $$ = tac_create(TAC_MOVE, temp, makeConstant(TYPE_FLOAT, &$1), NULL);
    }
    | ID 
    { 
        $$ = tac_create(TAC_VAR, retornaSimbolo($1), NULL, NULL); 
    }
    | '(' exp ')' 
    { 
        $$ = $2; 
    }
;

%%



int getLineNumber(void) {
    return yylineno;
}

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático na linha %d, próximo ao token '%s': %s\n", yylineno, yytext, s);
}


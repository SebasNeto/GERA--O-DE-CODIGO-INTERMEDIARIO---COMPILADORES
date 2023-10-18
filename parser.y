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

%union {
    int intValue;
    char* strValue;
    TAC* tac;        // Instrução TAC
}

%token <strValue> ID
%type<intValue> espec_tipo
%type<strValue> var
%type<tac> decl_var com_atrib com_selecao com_repeticao exp

%token INT VOID
%token LIT_INT LIT_REAL LIT_CHAR
%token NUM
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

decl_var: espec_tipo var '=' init_val ';'
{
    Symbol* sym = retornaSimbolo($2);
    if (sym) {
        sym->type = $1; 
    } else {
        inserirSimbolo($2,$1);
    }
    $$ = joinTAC($4, makeTAC(TAC_MOVE, findSymbol($2), NULL, $4->res));
}

com_atrib: var '=' exp ';'
{
    $$ = joinTAC($3, makeTAC(TAC_MOVE, findSymbol($1), NULL, $3->res));
};

com_selecao: IF '(' exp ')' comando
{
    Label* newLabel = makeLabel();
    $$ = joinTAC($3, makeTAC(TAC_IFZ, $3->res, newLabel, NULL));
    $$ = joinTAC($$, $5);
    $$ = joinTAC($$, makeTAC(TAC_LABEL, newLabel, NULL, NULL));
}
| IF '(' exp ')' comando ELSE comando
{
    Label* elseLabel = makeLabel();
    Label* endLabel = makeLabel();
    $$ = joinTAC($3, makeTAC(TAC_IFZ, $3->res, elseLabel, NULL));
    $$ = joinTAC($$, $5);
    $$ = joinTAC($$, makeTAC(TAC_JUMP, endLabel, NULL, NULL));
    $$ = joinTAC($$, makeTAC(TAC_LABEL, elseLabel, NULL, NULL));
    $$ = joinTAC($$, $7);
    $$ = joinTAC($$, makeTAC(TAC_LABEL, endLabel, NULL, NULL));
}
;

com_repeticao: WHILE '(' exp ')' comando
{
    Label* beginLabel = makeLabel();
    Label* endLabel = makeLabel();
    $$ = makeTAC(TAC_LABEL, beginLabel, NULL, NULL);
    $$ = joinTAC($$, $3);
    $$ = joinTAC($$, makeTAC(TAC_IFZ, $3->res, endLabel, NULL));
    $$ = joinTAC($$, $5);
    $$ = joinTAC($$, makeTAC(TAC_JUMP, beginLabel, NULL, NULL));
    $$ = joinTAC($$, makeTAC(TAC_LABEL, endLabel, NULL, NULL));
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
        default: yyerror("Invalid relational operator"); return;
    }
    $$ = joinTAC($1, $3);
    $$ = joinTAC($$, makeTAC(tacType, $1->res, $3->res, makeTemp()));
}
| exp_soma
{
    $$ = $1;
}
| INPUT '(' espec_tipo ')'
{
    $$ = makeTAC(TAC_INPUT, NULL, NULL, makeTemp());
}
;

exp_soma: exp_soma '+' exp_mult
{
    $$ = joinTAC($1, $3);
    $$ = joinTAC($$, makeTAC(TAC_ADD, $1->res, $3->res, makeTemp()));
}
| exp_soma '-' exp_mult
{
    $$ = joinTAC($1, $3);
    $$ = joinTAC($$, makeTAC(TAC_SUB, $1->res, $3->res, makeTemp()));
}
| exp_mult
{
    $$ = $1;
}
;

exp_mult: exp_mult '*' exp_simples
{
    $$ = joinTAC($1, $3);
    $$ = joinTAC($$, makeTAC(TAC_MUL, $1->res, $3->res, makeTemp()));
}
| exp_mult '/' exp_simples
{
    $$ = joinTAC($1, $3);
    $$ = joinTAC($$, makeTAC(TAC_DIV, $1->res, $3->res, makeTemp()));
}
| exp_simples
{
    $$ = $1;
}
;

// [Rest of the grammar rules...]

%%

int getLineNumber(void) {
    return yylineno;
}

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático na linha %d, próximo ao token '%s': %s\n", getLineNumber(), yytext, s);
    exit(3);
}

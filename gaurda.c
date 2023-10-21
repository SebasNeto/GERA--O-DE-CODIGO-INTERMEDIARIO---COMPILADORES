


#include <stdio.h>
#include "parser.tab.h"
#include "tabelaSimbolos.h"
#include "codegen.h"  // Inclua o header do código intermediário.

extern int yydebug;
extern FILE *yyin;
extern FILE *yyout;

int main(int argc, char **argv)
{
    iniciarTabela();
    
    FILE *file;
    yyin = file;
    yyout = fopen("symbol_table.lex", "w+");

    int yydebug = 1;
    file = fopen(argv[1], "r");
    yyin= file;
    yyparse();
    print_simboloTabela();
    tac_print();
  
    return 0;
}

#############################################3


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
    float floatValue;
    char* strValue;
    Symbol* symbolEntry;
    TAC* tac;        
}

%token <strValue> ID
%token<intValue> NUM
%type<tac> comando
%type<tac> init_val
%type<intValue> op_relac
%type<tac> exp_simples
%type<intValue> espec_tipo init_val
%type<strValue> var
%type<tac> decl_var com_atrib com_selecao com_repeticao exp exp_soma exp_mult
%token INT VOID
%token LIT_INT LIT_REAL LIT_CHAR
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

init_val: NUM { 
    $$ = tac_create(TAC_MOVE, makeTemp(), retornaSimbolo($1.intValue), NULL); 
}
| INPUT '(' espec_tipo ')' { 
    $$ = tac_create(TAC_INPUT, makeTemp(), NULL, NULL); 
}
;

var: ID { $$ = $1; } ;

espec_tipo: KW_INT { $$ = 1; }
          | KW_CHAR { $$ = 2; }
          ;

lista_com: /* Temporário */
    com_atrib
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
    NUM { 
        Symbol* temp = makeTemp();
        $$ = tac_create(TAC_MOVE, temp, retornaSimbolo($1.intValue), NULL);
    }
|   ID { 
      Symbol* sym = retornaSimbolo($1);
      if (!sym) {
          yyerror("Variable not declared");
          exit(1);
      }
      $$ = tac_create(TAC_VAR, sym, NULL, NULL); 
    }
|   '(' exp ')' { $$ = $2; }
;

%%

#############

void tac_print(TAC *tac) {
    while (tac) {
        switch (tac->type) {
            case TAC_SYMBOL:
                if (tac->res) {
                    printf("TAC (SYMBOL): %s\n", tac->res->identifier);
                }
                break;

            case TAC_MOVE:
                if (tac->res && tac->op1) {
                    printf("TAC (MOVE): %s = %s\n", tac->res->identifier, tac->op1->identifier);
                }
                break;

            case TAC_ADD:
                if (tac->res && tac->op1 && tac->op2) {
                    printf("TAC (ADD): %s = %s + %s\n", tac->res->identifier, tac->op1->identifier, tac->op2->identifier);
                }
                break;

            case TAC_MUL:
                if (tac->res && tac->op1 && tac->op2) {
                    printf("TAC (MUL): %s = %s * %s\n", tac->res->identifier, tac->op1->identifier, tac->op2->identifier);
                }
                break;

            case TAC_LABEL:
                if (tac->res) {
                    printf("TAC (LABEL): %s\n", tac->res->identifier);
                }
                break;

            case TAC_IFZ:
                if (tac->res && tac->op1) {
                    printf("TAC (IFZ): IF %s == 0 GOTO %s\n", tac->op1->identifier, tac->res->identifier);
                }
                break;

            case TAC_JUMP:
                if (tac->res) {
                    printf("TAC (JUMP): GOTO %s\n", tac->res->identifier);
                }
                break;

            case TAC_LT:
                if (tac->res && tac->op1 && tac->op2) {
                    printf("TAC (LT): IF %s < %s GOTO %s\n", tac->op1->identifier, tac->op2->identifier, tac->res->identifier);
                }
                break;

            case TAC_GT:
                if (tac->res && tac->op1 && tac->op2) {
                    printf("TAC (GT): IF %s > %s GOTO %s\n", tac->op1->identifier, tac->op2->identifier, tac->res->identifier);
                }
                break;

            case TAC_LEQ:
                if (tac->res && tac->op1 && tac->op2) {
                    printf("TAC (LEQ): IF %s <= %s GOTO %s\n", tac->op1->identifier, tac->op2->identifier, tac->res->identifier);
                }
                break;

            case TAC_GEQ:
                if (tac->res && tac->op1 && tac->op2) {
                    printf("TAC (GEQ): IF %s >= %s GOTO %s\n", tac->op1->identifier, tac->op2->identifier, tac->res->identifier);
                }
                break;

            case TAC_EQ:
                if (tac->res && tac->op1 && tac->op2) {
                    printf("TAC (EQ): IF %s == %s GOTO %s\n", tac->op1->identifier, tac->op2->identifier, tac->res->identifier);
                }
                break;

            case TAC_NEQ:
                if (tac->res && tac->op1 && tac->op2) {
                    printf("TAC (NEQ): IF %s != %s GOTO %s\n", tac->op1->identifier, tac->op2->identifier, tac->res->identifier);
                }
                break;
            
            case TAC_BEGINFUN:
                if (tac->res) {
                    printf("TAC (BEGINFUN): %s\n", tac->res->identifier);
                }
                break;

            case TAC_ENDFUN:
                if (tac->res) {
                    printf("TAC (ENDFUN): %s\n", tac->res->identifier);
                }
                break;

            case TAC_INPUT:
                if (tac->res) {
                    printf("TAC (INPUT): INPUT %s\n", tac->res->identifier);
                }
                break;

            default:
                printf("Unknown TAC type\n");
                break;
        }
        tac = tac->prev;
    }
}
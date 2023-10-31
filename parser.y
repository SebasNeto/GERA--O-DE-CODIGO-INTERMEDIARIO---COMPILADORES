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

%token KW_INT KW_REAL VOID
%token IF ELSE WHILE LOOP INPUT RETURN
%token EQ LEQ LT GT GEQ NEQ
%token LIT_INT LIT_REAL LIT_CHAR
%token ID

%union {
    int intValue;
    float floatValue;
    char *strValue;
    Symbol *symbolEntry;
    int tipo;
}

%type <intValue> LIT_INT
%type <floatValue> LIT_REAL
%type <strValue> LIT_CHAR
%type <symbolEntry> ID
%type <tipo> espec_tipo

%type <symbolEntry> var
%type <symbolEntry> exp

%%

programa: 
    lista_decl lista_com
    ;

lista_decl:
    lista_decl decl
    | decl
    ;

decl:
    decl_var
    | decl_func
    ;

decl_var:
    espec_tipo ID {
        Symbol* entry = inserirSimbolo($1, $2->identifier);
    } ';'  // Permite declarações sem inicialização
    | espec_tipo ID {
        Symbol* entry = inserirSimbolo($1, $2->identifier);
    } '=' literais ';'  // Permite declarações com inicialização
    ;


espec_tipo:
    KW_INT { $$ = SYMBOL_SCALAR; }
    | KW_REAL { $$ = SYMBOL_SCALAR; }
    | VOID { $$ = SYMBOL_SCALAR; }
    ;

decl_func:
    espec_tipo ID '(' params ')' com_comp
    ;

params:
    lista_param
    | VOID
    | /* vazio */
    ;

lista_param:
    lista_param ',' param
    | param
    ;

param:
    espec_tipo var
    ;

decl_locais:
    decl_locais decl_var
    | /* vazio */
    ;

lista_com:
    comando lista_com
    | /* vazio */
    ;

comando:
    com_expr
    | com_atrib
    | com_comp
    | com_selecao
    | com_repeticao
    | com_retorno
    ;

com_expr:
    exp ';'
    | ';'
    ;

com_atrib:
    var '=' exp ';' {
        Symbol* varEntry = retornaSimbolo($1->identifier);
        if (!varEntry) {
            yyerror("Variável não declarada");
        }else{
            //generateCode
        }
    }
    ;

com_comp:
    '{' decl_locais lista_com '}'
    ;

com_selecao:
    IF '(' exp ')' comando
    | IF '(' exp ')' com_comp ELSE comando
    ;

com_repeticao:
    WHILE '(' exp ')' comando
    ;

com_retorno:
    RETURN ';'
    | RETURN exp ';'
    ;

exp:
    exp_soma op_relac exp_soma
    | exp_soma
    ;

op_relac:
    LEQ
    | LT
    | GT
    | GEQ
    | EQ
    | NEQ
    ;

exp_soma:
    exp_soma op_soma exp_mult
    | exp_mult
    ;

op_soma:
    '+'
    | '-'
    ;

exp_mult:
    exp_mult op_mult exp_simples
    | exp_simples
    ;

op_mult:
    '*'
    | '/'
    | '%'
    ;

exp_simples:
    '(' exp ')'
    | var
    | cham_func
    | literais
    ;

literais:
    LIT_INT
    | LIT_REAL
    | LIT_CHAR
    ;

cham_func:
    ID '(' args ')'
    ;

var:
    ID {
        $$ = retornaSimbolo($1->identifier);
        if (!$$) {
            yyerror("Variável não declarada");
        }
    }
    | ID '[' LIT_INT ']' {
        // Tratamento de arrays, se necessário
    }
    ;

args:
    lista_arg
    | /* vazio */
    ;

lista_arg:
    lista_arg ',' exp
    | exp
    ;

%%

int getLineNumber(void) {
    return yylineno;
}

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático na linha %d, próximo ao token '%s': %s\n", yylineno, yytext, s);
}

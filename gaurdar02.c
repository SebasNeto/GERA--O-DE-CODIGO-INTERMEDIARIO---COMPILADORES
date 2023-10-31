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

///////////////////////////////q

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
    AST* astNode;
}

%type <intValue> LIT_INT
%type <floatValue> LIT_REAL
%type <strValue> LIT_CHAR
%type <symbolEntry> ID
%type <tipo> espec_tipo

%type <symbolEntry> var
%type <symbolEntry> exp

%type <symbolEntry> lista_com

%type <astNode> exp
%type <astNode> com_atrib
%type <astNode> com_selecao


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
    } ';'
    | espec_tipo ID{
        Symbol* entry = inserirSimbolo($1, $2->identifier);
    }
    '=' literais ';' 
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
            AST* astNode = createASTNode(AST_ATTR, varEntry, $3, NULL);
            TAC* tacCode = generateCode(astNode);
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

////////////////////

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

AST* root = NULL;

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

    AST* astNode;

}

%type <intValue> LIT_INT
%type <floatValue> LIT_REAL
%type <strValue> LIT_CHAR
%type <symbolEntry> ID
%type <tipo> espec_tipo

%type <symbolEntry> var
%type <symbolEntry> exp
%type <astNode> exp 

%type <symbolEntry> lista_com



%type <astNode> com_atrib
%type <astNode> com_selecao


%%

programa: 
    lista_decl lista_com{
        root = createASTNode(AST_PROGRAM, NULL, $1, $2, NULL);
    }
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
    } ';'
    | espec_tipo ID{
        Symbol* entry = inserirSimbolo($1, $2->identifier);
    }
    '=' literais ';' 
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
            $$ = createASTNode(AST_ATTR, varEntry, $3.ast, NULL, NULL);

        }
    }
    ;

com_comp:
    '{' decl_locais lista_com '}'
    ;

com_selecao:
    IF '(' exp   ')' comando{
        $$ = createASTNode(AST_IF, NULL, $3.ast, $5, NULL);
    }
    | IF '(' exp  ')' com_comp ELSE comando{
        $$ = createASTNode(AST_IF_ELSE, NULL, $3.ast, $5, $7);
    }
    ;

com_repeticao:
    WHILE '(' exp ')' comando
    ;

com_retorno:
    RETURN ';'
    | RETURN exp ';'
    ;

exp:
    exp_soma op_relac exp_soma{
        $$ = createASTNode(AST_OP_REL, NULL, $1, $3, NULL);
    }
    | exp_soma{
        $$ = $1;
    }
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
    | var{
        $$ = $1;
    }
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

///////////////////q

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

AST* root = NULL;

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

    AST* astNode;

}

%type <intValue> LIT_INT
%type <floatValue> LIT_REAL
%type <strValue> LIT_CHAR
%type <symbolEntry> ID
%type <tipo> espec_tipo

%type <astNode> exp 

%type <astNode> decl
%type <astNode> decl_var
%type <astNode> decl_func
%type <astNode> lista_param
%type <astNode> param
%type <astNode> params
%type <astNode> decl_locais
%type <astNode> com_expr
%type <astNode> com_repeticao
%type <astNode> com_retorno
%type <astNode> literais
%type <astNode> lista_arg

%type <astNode> lista_com
%type <astNode> comando
%type <astNode> exp_soma
%type <astNode> exp_mult
%type <astNode> exp_simples

%type <astNode> lista_decl
%type <astNode> com_comp
%type <astNode> var
%type <astNode> cham_func
%type <astNode> args


%type <astNode> com_atrib
%type <astNode> com_selecao


%%

programa: 
    lista_decl lista_com{
        root = createASTNode(AST_PROGRAM, NULL, $1, $2, NULL);
    }
    ;

lista_decl:
    lista_decl decl {
        $$ = createASTNode(AST_LISTA_DECL, NULL, $1, $2, NULL);
    }
    | decl {
        $$ = createASTNode(AST_DECL, NULL, $1, NULL, NULL);
    }
    ;

decl:
    decl_var
    | decl_func
    ;


decl_var:
    espec_tipo ID ';' {
        Symbol* entry = inserirSimbolo($1, $2->identifier);
        $$ = createASTNode(AST_VAR_DECL, entry, NULL, NULL, NULL);
    }
    | espec_tipo ID '=' literais ';' {
        Symbol* entry = inserirSimbolo($1, $2->identifier);
        $$ = createASTNode(AST_VAR_DECL, entry, NULL, NULL, NULL);
    }
    ;

espec_tipo:
    KW_INT { $$ = SYMBOL_SCALAR; }
    | KW_REAL { $$ = SYMBOL_SCALAR; }
    | VOID { $$ = SYMBOL_SCALAR; }
    ;
    
decl_func:
    espec_tipo ID '(' params ')' com_comp {
        Symbol* entry = inserirSimbolo($1, $2->identifier);
        $$ = createASTNode(AST_FUNC_DECL, entry, $4, $6, NULL);
    }
    ;

params:
    lista_param {
        $$ = createASTNode(AST_PARAMS, NULL, $1, NULL, NULL);
    }
    | VOID {
        $$ = createASTNode(AST_PARAMS_VOID, NULL, NULL, NULL, NULL);
    }
    | /* vazio */ {
        $$ = createASTNode(AST_PARAMS_EMPTY, NULL, NULL, NULL, NULL);
    }
    ;

lista_param:
    lista_param ',' param
    | param
    ;

param:
    espec_tipo var {
        $$ = createASTNode(AST_PARAM, $1, $2, NULL, NULL);
    }
    ;

decl_locais:
    decl_locais decl_var {
        $$ = createASTNode(AST_DECL_LOCAIS, NULL, $1, $2, NULL);
    }
    | /* vazio */ {
        $$ = createASTNode(AST_DECL_LOCAIS_EMPTY, NULL, NULL, NULL, NULL);
    }
    ;

lista_com:
    comando lista_com {
        $$ = createASTNode(AST_LISTA_COM, NULL, $1, $2, NULL);
    }
    | /* vazio */ {
        $$ = createASTNode(AST_LISTA_COM_EMPTY, NULL, NULL, NULL, NULL);
    }
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
    exp ';' {
        $$ = $1;
    }
    | ';' {
        $$ = createASTNode(AST_EXPR_EMPTY, NULL, NULL, NULL, NULL);
    }
    ;

com_atrib:
    var '=' exp ';' {
        Symbol* varEntry = retornaSimbolo($1->identifier);
        if (!varEntry) {
            yyerror("Variável não declarada");
        }else{
            $$ = createASTNode(AST_ATTR, varEntry, $3, NULL, NULL);

        }
    }
    ;

com_comp:
    '{' decl_locais lista_com '}' {
        $$ = createASTNode(AST_COM_COMP, NULL, $2, $3, NULL);
    }
    ;

com_selecao:
    IF '(' exp ')' comando{
        $$ = createASTNode(AST_IF, NULL, $3, $5, NULL);
    }
    | IF '(' exp  ')' com_comp ELSE comando{
        $$ = createASTNode(AST_IF_ELSE, NULL, $3, $5, $7);
    }
    ;

com_repeticao:
    WHILE '(' exp ')' comando {
        $$ = createASTNode(AST_WHILE, NULL, $3, $5, NULL);
    }
    ;


com_retorno:
    RETURN ';' {
        $$ = createASTNode(AST_RETURN, NULL, NULL, NULL, NULL);
    }
    | RETURN exp ';' {
        $$ = createASTNode(AST_RETURN, NULL, $2, NULL, NULL);
    }
    ;


exp:
    exp_soma op_relac exp_soma{
        $$ = createASTNode(AST_OP_REL, NULL, $1, $3, NULL);
    }
    | exp_soma{
        $$ = $1;
    }
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
    exp_soma op_soma exp_mult {
        $$ = createASTNode(AST_OP_SOMA, NULL, $1, $3, NULL);
    }
    | exp_mult {
        $$ = $1;
    }
    ;

op_soma:
    '+'
    | '-'
    ;

exp_mult:
    exp_mult op_mult exp_simples {
        $$ = createASTNode(AST_OP_MULT, NULL, $1, $3, NULL);
    }
    | exp_simples {
        $$ = $1;
    }
    ;

op_mult:
    '*'
    | '/'
    | '%'
    ;

exp_simples:
    '(' exp ')' {
        $$ = $2;
    }
    | var {
        $$ = createASTNode(AST_VAR, $1, NULL, NULL, NULL);
    }
    | cham_func {
        $$ = $1;
    }
    | literais {
        $$ = createASTNode(AST_LITERAL, NULL, NULL, NULL, $1);
    }
    ;


literais:
    LIT_INT {
        $$ = createASTNode(AST_LITERAL_INT, NULL, NULL, NULL, (void*)$1);
    }
    | LIT_REAL {
        $$ = createASTNode(AST_LITERAL_REAL, NULL, NULL, NULL, (void*)$1);
    }
    | LIT_CHAR {
        $$ = createASTNode(AST_LITERAL_CHAR, NULL, NULL, NULL, (void*)$1);
    }
    ;
    
cham_func:
    ID '(' args ')' {
        Symbol* symbol = retornaSimbolo($1);
        if (!symbol) {
            yyerror("Função não declarada");
        }
        $$ = createASTNode(AST_FUNC_CALL, symbol, $3, NULL, NULL);
    }
    ;

var:
    ID {
        Symbol* symbol = retornaSimbolo($1);
        if (!symbol) {
            yyerror("Variável não declarada");
        }
        $$ = createASTNode(AST_VAR, symbol, NULL, NULL, NULL);
    }
    | ID '[' LIT_INT ']' {
        Symbol* symbol = retornaSimbolo($1);
        if (!symbol) {
            yyerror("Variável não declarada");
        }
        $$ = createASTNode(AST_ARRAY_ACCESS, symbol, createASTNode(AST_LITERAL_INT, NULL, NULL, NULL, (void*)$3), NULL, NULL);
    }
    ;

cham_func:
    ID '(' args ')' {
        Symbol* symbol = retornaSimbolo($1);
        if (!symbol) {
            yyerror("Função não declarada");
        }
        $$ = createASTNode(AST_FUNC_CALL, symbol, $3, NULL, NULL);
    }
    ;

args:
    lista_arg {
        $$ = createASTNode(AST_ARGS, NULL, $1, NULL, NULL);
    }
    | /* vazio */ {
        $$ = NULL; // Ou crie um nó AST específico para uma lista de argumentos vazia
    }
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

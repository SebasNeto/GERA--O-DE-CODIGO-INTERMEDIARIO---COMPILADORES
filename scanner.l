%{

#include <stdio.h>

#include "tabelaSimbolos.h"
#include "ast.h"
#include "codegen.h"

#include "parser.tab.h"


void yyerror(const char *s);
%}

%option yylineno
%option noyywrap

%x COMMENT

%%

"int"                { printf("TOKEN: KW_INT\n"); return KW_INT; }
"real"               { printf("TOKEN: KW_REAL\n"); return KW_REAL; }
"void"               { printf("TOKEN: VOID\n"); return VOID; }
"if"                 { printf("TOKEN: IF\n"); return IF; }
"else"               { printf("TOKEN: ELSE\n"); return ELSE; }
"while"              { printf("TOKEN: WHILE\n"); return WHILE; }
"loop"               { printf("TOKEN: LOOP\n"); return LOOP; }
"input"              { printf("TOKEN: INPUT\n"); return INPUT; }
"return"             { printf("TOKEN: KW_RETURN\n"); return RETURN; }
"=="                 { printf("TOKEN: EQ\n"); return EQ; }
"<="                 { printf("TOKEN: LEQ\n"); return LEQ; }
"<"                  { printf("TOKEN: LT\n"); return LT; }
">"                  { printf("TOKEN: GT\n"); return GT; }
">="                 { printf("TOKEN: GEQ\n"); return GEQ; }
"!="                 { printf("TOKEN: NEQ\n");return NEQ; }
";"                 { printf("TOKEN: %c\n", yytext[0]);return yytext[0]; }
"+"|"-"|"*"|"/"|"<"|"="|";"|","|"("|")"|"["|"]"|"{"|"}"|">"|"!"|"&" { printf("TOKEN: %c\n", yytext[0]);  return yytext[0]; }

"/*"                 { BEGIN(COMMENT); }
<COMMENT>"*/"        { BEGIN(INITIAL); }
<COMMENT>.|\n        { /* ignora qualquer caractere dentro de um comentário */ }

[0-9]+               {
   yylval.intValue = atoi(yytext);
   printf("TOKEN: LIT_INT %s\n", yytext); 
   return LIT_INT; 
}

[0-9]+[.][0-9]+ {
   yylval.floatValue = atof(yytext); 
   printf("TOKEN: LIT_REAL %s\n", yytext); 
   return LIT_REAL; 
}

'\''[^\']'\'' { 
   yylval.strValue = strdup(&yytext[1]);
   printf("TOKEN: LIT_CHAR %c\n", yytext[1]); 
   return LIT_CHAR; 
}


[a-zA-Z_][a-zA-Z_0-9]* {
   Symbol* entry = retornaSimbolo(yytext); 
   if (!entry) {
      entry = inserirSimbolo(0, yytext);
   }
   yylval.symbolEntry = entry; 
   printf("ID: %s\n", yytext);
   return ID;
}


"//"[^"\n"]*          { /* Ignora comentários de uma linha */ }

[ \t\r\n]+           { /* Ignora espaços em branco e quebras de linha */ }
.                    { yyerror("Caractere inválido"); }

%%
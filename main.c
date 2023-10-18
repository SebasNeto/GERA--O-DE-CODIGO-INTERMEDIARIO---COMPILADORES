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

    // Imprimir o código intermediário gerado.
    // Considerando que você tem uma função printTAC() que faz isso.
    printTAC(); 

    return 0;
}

#include <stdio.h>
#include "tabelaSimbolos.h"
#include "codegen.h"
#include "parser.tab.h"
 

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
    tac_print(lastTac);
  
    return 0;
}

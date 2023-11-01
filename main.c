#include <stdio.h>

#include "tabelaSimbolos.h"
#include "ast.h"
#include "codegen.h"

#include "parser.tab.h"

extern int yydebug;
extern FILE *yyin;
extern FILE *yyout;

int main(int argc, char **argv)
{
    iniciarTabela();
    
    FILE *file;
    yyout = fopen("symbol_table.lex", "w+");

    int yydebug = 1;
    file = fopen(argv[1], "r");
    yyin= file;
    yyparse();
    print_simboloTabela();


    if (ast_root != NULL) {
        generate_code(ast_root);  // Chama a função de geração de código
    }

  
    return 0;
}

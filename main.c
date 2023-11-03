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
    FILE *saida;

    yyout = fopen("symbol_table.lex", "w+");

    int yydebug = 1;
    file = fopen(argv[1], "r");

    yyin= file;
    yyparse();
    print_simboloTabela();


    if (astRaiz != NULL) {
        printf("AST construída com sucesso. Gerando código intermediário...\n");
        TAC* code = gerarCodigo(astRaiz);
        printTacCode(code);
        tacPrint(code);
    }else{
        printf("Erro na compilação do AST.\n");
    }

    fclose(file);
    fclose(yyout);
  
    return 0;
}

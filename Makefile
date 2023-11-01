etapa2: lex.yy.o parser.tab.o main.o tabelaSimbolos.o codegen.o ast.o
	gcc -o etapa2 lex.yy.o parser.tab.o main.o tabelaSimbolos.o codegen.o ast.o

main.o: main.c ast.h tabelaSimbolos.h codegen.h
	gcc -c main.c

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c lex.yy.h: scanner.l parser.tab.h
	flex --header-file=lex.yy.h scanner.l

lex.yy.o: lex.yy.c ast.h tabelaSimbolos.h codegen.h
	gcc -c lex.yy.c

parser.tab.o: parser.tab.c ast.h tabelaSimbolos.h codegen.h
	gcc -c parser.tab.c

tabelaSimbolos.o: tabelaSimbolos.c tabelaSimbolos.h ast.h
	gcc -c tabelaSimbolos.c

codegen.o: codegen.c codegen.h ast.h
	gcc -c codegen.c

ast.o: ast.c ast.h
	gcc -c ast.c

clean:
	rm -f *.o lex.yy.c etapa2 parser.tab.c parser.tab.h lex.yy.h


 # -------------------------------------------------------------------
 #            Arquivo: Makefile
 # -------------------------------------------------------------------
 #              Autor: Bruno Müller Junior
 #               Data: 08/2007
 #      Atualizado em: [09/08/2020, 19h:01m]
 #
 # -------------------------------------------------------------------

$DEPURA=1

compilador: lex.yy.c compilador.tab.c compilador.o ./lib/compilador.h
	gcc lex.yy.c ./build/compilador.tab.c ./bin/compilador.o -o compilador -ll -ly -lc

lex.yy.c: ./src/compilador.l ./lib/compilador.h
	flex ./src/compilador.l

compilador.tab.c: ./src/compilador.y ./lib/compilador.h
	bison ./src/compilador.y -d -v -o ./build/compilador.tab.c

compilador.o : ./lib/compilador.h ./src/compiladorF.c
	gcc -c ./src/compiladorF.c -o ./bin/compilador.o

clean :
	rm -f ./build/* lex.yy.c ./bin/compilador.o compilador

run: 
	./compilador ./test/teste1.pas && cat MEPA

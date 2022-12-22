
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/compilador.h"
#include "../lib/tableValues.h"
#include "../lib/queue.h"

#define STACKSIZE 32768		/* tamanho das pilhas*/

int numberVariables = 0, lexicalLevel = 0, offset = 0;
tableVariable_t *variablesQueue = NULL, *newVariable = NULL;

%}

%token PROGRAM VAR T_BEGIN T_END
%token ATRIBUICAO PONTO_E_VIRGULA DOIS_PONTOS VIRGULA
%token PONTO ABRE_PARENTESES FECHA_PARENTESES MAIOR
%token MENOR WHILE DO IF
%token THEN ELSE FUNCTION PROCEDURE
%token LABEL TYPE ARRAY OF
%token GOTO NOT IDENT NUMERO

%%

programa    :{
               geraCodigo (NULL, "INPP");
             }
             PROGRAM IDENT
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
               geraCodigo (NULL, "PARA");
             }
;

bloco       :
              parte_declara_vars
              {
              }

              comando_composto
              ;




parte_declara_vars:  var
;


var         : { } VAR declara_vars
            |
;

declara_vars: declara_vars declara_var
            | declara_var
;

declara_var : { }
              lista_id_var DOIS_PONTOS
              tipo
              { 
                  printf("\n\ntoken = %s\n\n", token);
                  printf("\n\numberVariables = %d\n\n", numberVariables);

                  char amem[1000];
                  sprintf(amem, "AMEM %d", numberVariables);
                  geraCodigo (NULL, amem);
              }
              PONTO_E_VIRGULA
;

tipo        : IDENT
;

lista_id_var: lista_id_var VIRGULA IDENT
            { 
               newVariable = createVariable(0, lexicalLevel, offset, -1, -1);
               queue_append((queue_t **) &variablesQueue, (queue_t*) newVariable);
               //queue_print("saida da fila", (queue_t*) variablesQueue, print_elem);

               numberVariables++;
            }
            | IDENT {
               newVariable = createVariable(0, lexicalLevel, offset, -1, -1);
               queue_append((queue_t **) &variablesQueue, (queue_t*) newVariable);
               // queue_print("saida da fila", (queue_t*) variablesQueue, print_elem);
               // printf("\n\ntamanho fila = %d\n\n", queue_size((queue_t*) variablesQueue));

               offset++;
               numberVariables++;
            }
;

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;


comando_composto: T_BEGIN comandos T_END

comandos:
;


%%

int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de Simbolos
 * ------------------------------------------------------------------- */
   yyin=fp;
   yyparse();

   return 0;
}

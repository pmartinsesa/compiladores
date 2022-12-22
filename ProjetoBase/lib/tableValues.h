#ifndef __TABLE_VALUES__
#define __TABLE_VALUES__

#include "queue.h"

#define INTEGER = 0;
#define BOOLEAN = 1;

typedef struct tableVariable_t {
  struct tableVariable_t *prev,  *next ;  // aponta para o elemento anterior na fila

  short int typeInTable;
  int lexicalLevel;
  int offset;
  short int type;
  short int isReference;
} tableVariable_t;

tableVariable_t* createVariable(short int typeInTable, int lexicalLevel, int offset, short int type, short int isReference);
void print_elem (void *ptr);

#endif
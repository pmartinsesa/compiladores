#include <stdlib.h>
#include <stdio.h>
#include "../lib/tableValues.h"

tableVariable_t* createVariable(short int typeInTable, int lexicalLevel, int offset, short int type, short int isReference) {
  tableVariable_t* newVariable;

  newVariable = (tableVariable_t*) malloc (sizeof (tableVariable_t)) ;
  newVariable->prev = newVariable->next = NULL;
  
  newVariable->typeInTable = typeInTable;
  newVariable->lexicalLevel = lexicalLevel;
  newVariable->offset = offset;
  newVariable->type = type;
  newVariable->isReference = isReference;

  return newVariable;
}

void print_elem (void *ptr)
{
   tableVariable_t *elem = ptr ;

   if (!elem)
      return ;

   elem->prev ? printf ("%d, %d", elem->lexicalLevel, elem->offset) : printf ("*") ;
   printf ("<%d, %d>", elem->lexicalLevel, elem->offset) ;
   elem->next ? printf ("%d, %d", elem->lexicalLevel, elem->offset) : printf ("*") ;
}

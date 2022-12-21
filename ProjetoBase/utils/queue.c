#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void queue_append (queue_t **queue, queue_t *elem)
{
	queue_t* andador;
	
	//andador (variavel responsavel por se movimentar na fila)  = primeiro elemento
	andador = *queue;

	// - a fila deve existir
	// - o elemento deve existir
	if ((queue == NULL) || elem == NULL)
	{
		printf("ERRO, FILA OU ELEMENTO NAO ENCONTRADO, FAVOR VERIFICAR A INSERCAO\n");
	}
	// - o elemento nao deve estar em outra fila
	else if (elem->next != NULL) 
	{
		printf("ERRO, ELEMENTO PERTENCE A OUTRA FILA, FAVOR VERIFICAR INSERCAO\n");
	}
	else if (queue_size(*queue) == 0)
	{
		andador = elem;
		andador->prev = elem;
		andador->next = elem;
		*queue = andador;
	}
	else
	{	
		andador = andador->prev;			//anda até o ultimo elemento
		andador->next = elem;		
		elem->prev = andador;		
		elem->next = *queue;				//liga ultimo elemento com o primeiro
		(*queue)->prev = elem;				//liga primeiro elemento com o ultimo
	}

}

queue_t *queue_remove (queue_t **queue, queue_t *elem)
{
	queue_t* sentinela = *queue;	//guarda o primeiro elemento
	queue_t* andador = *queue;		
	
	// - a fila deve existir
	// - a fila nao deve estar vazia
	if (queue == NULL || *queue == NULL)
	{
		printf ("ERRO, FILA NÃO EXISTE OU ESTA VAZIA, FAVOR VERIFICAR REMOCAO\n");
		elem = NULL;
	}
	//remove primeiro elemento
	else if (andador == elem)
	{
		if (queue_size(*queue) > 1)
		{
			(*queue)->next->prev = (*queue)->prev;
			(*queue)->prev->next = (*queue)->next;
			*queue = (*queue)->next;
			elem->prev = NULL;
			elem->next = NULL;
		}
		else
		{
			elem->prev = NULL;
			elem->next = NULL;
			*queue = NULL;
		}
		
	} 	
	//remove ultimo elemento
	else if (andador->prev == elem)
	{
		*queue = andador->prev;
		
		(*queue)->next->prev = (*queue)->prev;
		(*queue)->prev->next = (*queue)->next;
		*queue = sentinela;
		elem->prev = NULL;
		elem->next = NULL;
	}
	//elemento no meio
	else
	{				
		andador = andador->next;
		//analisa se o elemento existe na fila
		// - o elemento deve existir
		// - o elemento deve pertencer a fila indicada		
		while (andador != elem)
		{  
			andador = andador->next;
			//caso não exista...
			if (andador == sentinela)
			{
				elem = NULL;
				printf ("ERRO, ELEMENTO NÃO EXISTE OU PERTENCE A OUTRA FILA, FAVOR VERIFICAR REMOCAO\n");
				break;
			}
		}
		//caso exista...
		if (elem != NULL)
		{	
			*queue = andador;
			(*queue)->next->prev = (*queue)->prev;
			(*queue)->prev->next = (*queue)->next;
			*queue = sentinela;
			elem->prev = NULL;
			elem->next = NULL;
		}
	}
		
	return(elem);
}

int queue_size (queue_t *queue)
{
	int tamanho = 0;
	queue_t* sentinela = queue;

	if (queue != NULL)
	{
		tamanho++;
		//comparando enderecos de memoria
		while (sentinela != queue->next)
		{
			tamanho++;
			queue = queue->next;
		}
	}
	
	queue = sentinela;	
	
	return tamanho;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*))
{
	short int filaVazia = 0;
	int tam = queue_size(queue);
	
	//analisa se a fila é vazia
	if (tam == 0)
		filaVazia = 1;
	
	//Formatação da saida
	printf("%s: [", name); 

	for (int i = 0; i < tam; i++)
	{ 
		print_elem(queue);
		queue = queue->next;
		printf(" ");
	}
	/*caso não seja vazia apagar o espaço a mais 
	criado no for acima*/ 
	if (!filaVazia)
		printf("\b");
	
	printf("]\n");
}

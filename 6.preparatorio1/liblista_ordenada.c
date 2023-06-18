#include <stdio.h>
#include <stdlib.h>
#include "liblista_ordenada.h"

/*
typedef struct elemento {
    int chave;  
   
} elemento_t;

typedef struct nodo {
    elemento_t *elemento;
    struct nodo *prox;
} nodo_t;


typedef struct lista {
    nodo_t *ini;
} lista_t;
*/

lista_t *lista_cria ()
{
    lista_t *nova_lista;
    
    if(!(nova_lista = (lista_t *)malloc(sizeof(lista_t))))
        return NULL;

    nova_lista->ini = NULL;
    return nova_lista;
}

void lista_destroi(lista_t **l)
{
    nodo_t *auxiliar;
    nodo_t *seguinte;

    auxiliar = (*l)->ini;

    while (auxiliar != NULL)
    {
        seguinte = auxiliar->prox;
        free(auxiliar->elemento);
        free(auxiliar);
        auxiliar = seguinte;
    }
    free(*l);
}

int lista_insere_ordenado(lista_t *l, elemento_t *elemento)
{
    
    nodo_t *novo;
    nodo_t *auxiliar;

    if (!(novo = (nodo_t *)malloc(sizeof(nodo_t))))
        return 0;
    
    novo->elemento = elemento;
    auxiliar = l->ini;

    /* Primeiro elemento a ser iinserido. */
    if (l->ini == NULL)
    {
        novo->prox = NULL;
        l->ini = novo;
    }/* Se lista já tem um elemen->chave. */
    else if (elemento->chave < l->ini->elemento->chave)
    {
        novo->prox = l->ini;
        l->ini = novo;
    }/* Se o elemento a ser inserido é o maior valor(último da lista). */
    else
    {   /* aux->prox != NULL. */
        while (auxiliar->prox && auxiliar->prox->elemento->chave < elemento->chave)
            auxiliar = auxiliar->prox;

        novo->prox = auxiliar->prox;
        auxiliar->prox = novo;
    }
    return 1;
}


int lista_remove_ordenado (lista_t *l, elemento_t *elemento)
{
    nodo_t *remover, *auxiliar;

    /* Lista não é vazia. */
    if(l->ini != NULL)
    {   
        /* Se o elemento a ser reovido é o primeiro da lista. */
        if(l->ini->elemento->chave == elemento->chave)
        {
            remover = l->ini;
            l->ini = remover->prox;
            free(remover->elemento);
            free(remover);
            return 1;
        }
        auxiliar = l->ini;
        /* aux->prox e diferente de null(existe) && */
        while(auxiliar->prox && auxiliar->prox->elemento->chave != elemento->chave)
            auxiliar = auxiliar->prox;
            
        /* Se a lista chegou no fim, mas não achou a chave. */
        if(!auxiliar->prox)
            return 0;

        /* Se o valor do próximo é o valor a ser removido. */
        remover = auxiliar->prox;
        auxiliar->prox = remover->prox;
        free(remover->elemento);
        free(remover);
        return 1;
    }
    return 0;
}

int lista_vazia(lista_t *l)
{
    if (l == NULL || l->ini->prox == l->ini) 
        return 1; /* Lista vazia. */ 
    
    return 0; /* Lista não vazia. */ 
    
}
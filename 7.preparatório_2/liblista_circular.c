#include "liblista_circular.h"
#include <stdio.h>
#include <stdlib.h>


lista_t *lista_cria()
{
    lista_t *criar_lista;
    nodo_t *sentinela;

    if (!(criar_lista = malloc(sizeof(lista_t))))
        return NULL;

    if (!(sentinela = malloc(sizeof(nodo_t))))
    {   /* Se o sentinela não foi alocado, também libera a lista. */
        free(criar_lista);
        return NULL;
    }
    sentinela->elemento = NULL;
    sentinela->prox = sentinela;
    sentinela->prev = sentinela;
    criar_lista->ini = sentinela;
    return criar_lista;
}

int lista_insere_ordenado(lista_t *l, elemento_t *elemento)
{
    if (l == NULL || elemento == NULL)
        return 0;

    nodo_t *novo, *atual;

    if (!(novo = malloc(sizeof(nodo_t))))
        return 0;

    novo->elemento = elemento;
    atual = l->ini->prox;

    if (atual == l->ini || elemento->chave < atual->elemento->chave) {
        novo->prox = atual;
        novo->prev = l->ini;
        l->ini->prox = novo;
        atual->prev = novo;
        return 1;
    }

    while (atual != l->ini && atual->prox != l->ini && atual->prox->elemento->chave < elemento->chave)
        atual = atual->prox;

    novo->prox = atual->prox;
    novo->prev = atual;
    atual->prox->prev = novo;
    atual->prox = novo;

    return 1;
}



int lista_remove_ordenado(lista_t *l, elemento_t *elemento)
{
    nodo_t *atual;
    atual = l->ini->prox;

    if(lista_vazia(l))
        return 0;

    while (atual != l->ini && atual->elemento->chave != elemento->chave)
        atual = atual->prox;

    if (atual == l->ini)
        return 0;

    atual->prev->prox = atual->prox;
    atual->prox->prev = atual->prev;

    free(atual->elemento);
    free(atual);
    return 1;
}

int lista_vazia(lista_t *l)
{
    if (l == NULL || l->ini->prox == l->ini)
        return 1;
    return 0;
}

void lista_destroi(lista_t **l)
{
    nodo_t *sentinela, *atual;

    sentinela = (*l)->ini;
    atual = sentinela->prox;

    while (atual != sentinela)
    {
        nodo_t *proximo = atual->prox;
        free(atual->elemento);
        free(atual);
        atual = proximo;
    }
    free(sentinela);
    free(*l);
    *l = NULL;
}


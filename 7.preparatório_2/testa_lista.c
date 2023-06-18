#include "liblista_circular.h"
#include <stdio.h>
#include <stdlib.h>

elemento_t *criar_elemento(int chave)
{
    elemento_t *elemento = malloc(sizeof(elemento_t));
    if (elemento == NULL)
        return NULL;
    
    elemento->chave = chave;
    /*  Outros campos do elemento, se houver. */
    
    return elemento;
}

void imprimir_lista(lista_t *l)
{
    nodo_t *atual;
    atual = l->ini->prox;

    if (lista_vazia(l))
    {
        printf("\nA lista está vazia.\n");
        return;
    }
    
    printf("\n\tLista: ");
    while (atual != l->ini)
    {
        printf("%d ", atual->elemento->chave);
        /* Imprimir outros campos do elemento, se houver. */ 
        atual = atual->prox;
    }
    printf(".\n");
}

int main()
{
    lista_t *lista = lista_cria();
    int opcao = 0;

        while (opcao != 4)
    {
        printf("\nMenu:\n");
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Imprimir lista\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1)
        {
            /*  Limpar o buffer de entrada.*/
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                continue;

            printf("\nOpção inválida. Tente novamente.\n");
            continue;
        }

        switch (opcao)
        {
        case 1:
        {
            int chave;
            printf("Digite a chave do elemento a ser inserido: ");
            scanf("%d", &chave);
            elemento_t *elemento = criar_elemento(chave);
            
            if (lista_insere_ordenado(lista, elemento))
                printf("\nElemento inserido com sucesso.\n");
            else
                printf("\nFalha ao inserir o elemento.\n");
            
            break;
        }
        case 2:
        {
            if (lista_vazia(lista))
            {
                printf("\nA lista está vazia.\n");
                break;
            }
            
            int chave;
            printf("\nDigite a chave do elemento a ser removido: ");
            scanf("%d", &chave);
            elemento_t *elemento = criar_elemento(chave);
            
            if (lista_remove_ordenado(lista, elemento))
                printf("\nElemento removido com sucesso.\n");
            else
                printf("\nFalha ao remover o elemento.\n");
            
            free(elemento);
            break;
        }
        case 3:
            imprimir_lista(lista);
            break;
        case 4:
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
        }
    }
    printf("\nFim do programa.\n\n");
    lista_destroi(&lista);
    return 0;
}

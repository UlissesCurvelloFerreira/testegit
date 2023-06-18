#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libagenda.h"


agenda_t* cria_agenda()
{
    agenda_t* nova_agenda = (agenda_t*)malloc(sizeof(agenda_t));
    if (nova_agenda == NULL)
        return NULL;

    nova_agenda->mes_atual = 1;

    nova_agenda->ptr_mes_atual = (mes_t*)malloc(sizeof(mes_t));
    if (nova_agenda->ptr_mes_atual == NULL) {
        free(nova_agenda);
        return NULL;
    }

    nova_agenda->ptr_mes_atual->mes = 1;
    nova_agenda->ptr_mes_atual->dias = NULL;
    nova_agenda->ptr_mes_atual->prox = nova_agenda->ptr_mes_atual;
    nova_agenda->ptr_mes_atual->ant = nova_agenda->ptr_mes_atual;

    return nova_agenda;
}

compromisso_t* cria_compromisso(horario_compromisso_t hc, int id, const char* descricao)
{
    compromisso_t* novo_compromisso = (compromisso_t*)malloc(sizeof(compromisso_t));
    if (novo_compromisso == NULL)
        return NULL;

    novo_compromisso->id = id;
    novo_compromisso. = hc;
    novo_compromisso->prox = NULL;
    strncpy(novo_compromisso->descricao, descricao, sizeof(novo_compromisso->descricao) - 1);
    novo_compromisso->descricao[sizeof(novo_compromisso->descricao) - 1] = '\0';

    return novo_compromisso;
}

void destroi_agenda(agenda_t* agenda)
{
    if (agenda == NULL)
        return;

    mes_t* mes_atual = agenda->ptr_mes_atual;
    mes_t* mes_prox;

    while (mes_atual != NULL && mes_atual->mes != agenda->mes_atual) {
        mes_atual = mes_atual->prox;
    }

    if (mes_atual == NULL)
        return;

    mes_prox = mes_atual->prox;

    while (mes_atual != NULL) {
        dia_t* dia_atual = mes_atual->dias;
        dia_t* dia_prox;

        while (dia_atual != NULL) {
            compromisso_t* compromisso_atual = dia_atual->comprs;
            compromisso_t* compromisso_prox;

            while (compromisso_atual != NULL) {
                compromisso_prox = compromisso_atual->prox;
                free(compromisso_atual);
                compromisso_atual = compromisso_prox;
            }

            dia_prox = dia_atual->prox;
            free(dia_atual);
            dia_atual = dia_prox;
        }

        mes_prox = mes_atual->prox;
        free(mes_atual);
        mes_atual = mes_prox;
    }

    free(agenda);
}

void insere_compromisso(agenda_t* agenda, horario_compromisso_t hc, int id, const char* descricao)
{
    if (agenda == NULL)
        return;

    mes_t* mes_atual = agenda->ptr_mes_atual;

    while (mes_atual != NULL && mes_atual->mes != agenda->mes_atual) {
        mes_atual = mes_atual->prox;
    }

    if (mes_atual == NULL)
        return;

    dia_t* dia_atual = mes_atual->dias;
    dia_t* dia_anterior = NULL;

    while (dia_atual != NULL && dia_atual->dia < hc.ini_h) {
        dia_anterior = dia_atual;
        dia_atual = dia_atual->prox;
    }

    if (dia_atual == NULL || dia_atual->dia != hc.ini_h) {
        dia_t* novo_dia = (dia_t*)malloc(sizeof(dia_t));
        if (novo_dia == NULL)
            return;

        novo_dia->dia = hc.ini_h;
        novo_dia->comprs = NULL;
        novo_dia->prox = dia_atual;

        if (dia_anterior != NULL) {
            dia_anterior->prox = novo_dia;
        } else {
            mes_atual->dias = novo_dia;
        }

        dia_atual = novo_dia;
    }

    compromisso_t* novo_compromisso = cria_compromisso(hc, id, descricao);
    if (novo_compromisso == NULL)
        return;

    compromisso_t* compromisso_atual = dia_atual->comprs;
    compromisso_t* compromisso_anterior = NULL;

    while (compromisso_atual != NULL && compromisso_atual->horario.ini_m < hc.ini_m) {
        compromisso_anterior = compromisso_atual;
        compromisso_atual = compromisso_atual->prox;
    }

    if (compromisso_atual != NULL && compromisso_atual->horario.ini_m == hc.ini_m) {
        free(novo_compromisso);
        return;
    }

    if (compromisso_anterior != NULL) {
        compromisso_anterior->prox = novo_compromisso;
    } else {
        dia_atual->comprs = novo_compromisso;
    }

    novo_compromisso->prox = compromisso_atual;
}

void imprime_agenda_mes(const agenda_t* agenda)
{
    if (agenda == NULL)
        return;

    mes_t* mes_atual = agenda->ptr_mes_atual;

    while (mes_atual != NULL && mes_atual->mes != agenda->mes_atual) {
        mes_atual = mes_atual->prox;
    }

    if (mes_atual == NULL)
        return;

    printf("Agenda para o mes %d:\n", mes_atual->mes);

    dia_t* dia_atual = mes_atual->dias;

    while (dia_atual != NULL) {
        printf("Dia %d:\n", dia_atual->dia);

        compromisso_t* compromisso_atual = dia_atual->comprs;

        while (compromisso_atual != NULL) {
            printf("ID: %d\n", compromisso_atual->id);
            printf("Horario: %02d:%02d - %02d:%02d\n", compromisso_atual->horario.ini_h, compromisso_atual->horario.ini_m,
                   compromisso_atual->horario.fim_h, compromisso_atual->horario.fim_m);
            printf("Descricao: %s\n", compromisso_atual->descricao);

            compromisso_atual = compromisso_atual->prox;
        }

        dia_atual = dia_atual->prox;
    }
}

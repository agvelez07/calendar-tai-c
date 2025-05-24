#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala.h"
#include "agenda.h"

struct sala {
    char nome[MAX_NOME];
    NodeEvento eventos;
};

Sala iniciarSala(void) {
    Sala sala = malloc(sizeof(struct sala));
    if (sala != NULL) {
        sala->nome[0] = '\0';
        sala->eventos = NULL;
    }
    return sala;
}

void criarSala(Sala sala, const char *nome) {
    if (sala && nome) {
        strncpy(sala->nome, nome, MAX_NOME - 1);
        sala->nome[MAX_NOME - 1] = '\0';
        sala->eventos = NULL;
    }
}

int existeSala(Sala sala) {
    return sala != NULL && sala->nome[0] != '\0';
}

int procurarSala(Sala sala, const char *nome) {
    if (!sala || !nome) return 0;
    return strcmp(getNomeSala(sala), nome) == 0;
}

const char *getNomeSala(Sala sala) {
    return (sala != NULL) ? sala->nome : NULL;
}

NodeEvento getEventos(Sala sala) {
    return (sala != NULL) ? sala->eventos : NULL;
}

void setEventos(Sala sala, NodeEvento lista) {
    if (sala != NULL) sala->eventos = lista;
}

void eliminarSala(Sala sala) {
    if (sala) {
        destruirListaEventos(getEventos(sala));
        free(sala);
    }
}

void criarSalaOrdenada(const char *nome, Agenda agenda) {
    if (getNumSalas(agenda) >= MAX_SALAS) return;

    Sala nova = iniciarSala();
    criarSala(nova, nome);

    int i = getNumSalas(agenda) - 1;
    while (i >= 0 && strcmp(getNomeSala(getSala(agenda, i)), nome) > 0) {
        deslocarSalasDireita(agenda, i + 1);
        i--;
    }

    setSala(agenda, i + 1, nova);
    incrementarNumSalas(agenda);
}

int verificarEspacoSala(Sala sala, Evento novoEvento) {
    if (!sala || !novoEvento) return 0;

    Data novoInicio = getDataInicio(novoEvento);
    Data novoFim = getDataFim(novoEvento);

    printf("VERIFICAR sala %s\n", getNomeSala(sala));

    NodeEvento atual = getEventos(sala);
    if (!atual) {
        printf("? Sala ainda sem eventos. OK para inserir.\n");
        return 1;
    }
    while (atual != NULL) {
        Evento existente = getEvento(atual);
        Data inicioExistente = getDataInicio(existente);
        Data fimExistente = getDataFim(existente);

        int comecaAntesDoFim = compararDatas(novoInicio, fimExistente) < 0;
        int terminaDepoisDoInicio = compararDatas(novoFim, inicioExistente) > 0;

        printf("Comparar evento [%02d:%02d ? %02d:%02d] com [%02d:%02d ? %02d:%02d]\n",
               getHora(novoInicio), getMin(novoInicio), getHora(novoFim), getMin(novoFim),
               getHora(inicioExistente), getMin(inicioExistente), getHora(fimExistente), getMin(fimExistente));

        if (comecaAntesDoFim && terminaDepoisDoInicio) {
            return 0;  // Há sobreposição
        }

        atual = getProximoEvento(atual);
    }

    return 1; // Não há conflitos
}

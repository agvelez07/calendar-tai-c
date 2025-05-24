#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"
#include "evento.h"

#define BUFFER_SIZE 2048
char buffer[BUFFER_SIZE];

struct agenda {
    Sala salas[MAX_SALAS];
    int numSalas;
};

Agenda inicializarAgenda(void) {
    Agenda agenda = malloc(sizeof(struct agenda));
    if (agenda != NULL) {
        agenda->numSalas = 0;
    }
    return agenda;
}

int getNumSalas(Agenda agenda) {
    return (agenda != NULL) ? agenda->numSalas : 0;
}

Sala getSala(Agenda agenda, int i) {
    if (agenda == NULL || i < 0 || i >= getNumSalas(agenda)) return NULL;
    return agenda->salas[i];
}

void setSala(Agenda agenda, int pos, Sala sala) {
    if (agenda != NULL && pos >= 0 && pos < MAX_SALAS) {
        agenda->salas[pos] = sala;
    }
}

void deslocarSalasDireita(Agenda agenda, int ateIndice) {
    for (int i = getNumSalas(agenda) - 1; i >= ateIndice; i--) {
        setSala(agenda, i + 1, getSala(agenda, i));
    }
}

void incrementarNumSalas(Agenda agenda) {
    if (agenda != NULL && agenda->numSalas < MAX_SALAS) {
        agenda->numSalas++;
    }
}

int verificarEspacoAgenda(Agenda agenda, const char *nomeSala, Evento e) {
    int i = procurarSala(nomeSala, agenda);

    if (i != -1) {
        Sala sala = getSala(agenda, i);
        return verificarEspacoSala(sala, e);
    } else {
        return (getNumSalas(agenda) < MAX_SALAS) ? 1 : -1;
    }
}

void inserirNaAgenda(Agenda agenda, const char* nomeSala, Evento evento) {
    if (agenda == NULL || nomeSala == NULL || evento == NULL) {
        printf("ERRO: Parâmetros inválidos em inserirNaAgenda\n");
        return;
    }

    int i = procurarSala(nomeSala, agenda);
    if (i == -1) {
        criarSalaOrdenada(nomeSala, agenda);
        i = procurarSala(nomeSala, agenda);
    }

    Sala sala = getSala(agenda, i);

    NodeEvento novo = criarNodeEvento(evento);
    if (novo == NULL) {
        printf("Erro ao criar nodo para evento.\n");
        destruirEvento(evento);
        return;
    }

    setProximoEvento(novo, getEventos(sala));
    setEventos(sala, novo);
}

void lerAgenda(FILE* file, Agenda agenda) {
    int numEventos, numSalas;
    fscanf(file, "%d %d\n", &numEventos, &numSalas);

    for (int i = 0; i < numEventos; i++) {
        char linha[2048];
        if (!fgets(linha, sizeof(linha), file)) continue;

        int ano, mes, dia, hora, min, duracao;
        char resto[512];

        if (sscanf(linha, "%d %d %d %d %d %d %[^\n]", &ano, &mes, &dia, &hora, &min, &duracao, resto) != 7) {
            printf("Linha mal formatada (%d): %s\n", i + 1, linha);
            continue;
        }

        char *sala = strtok(resto, ":");
        char *uc = strtok(NULL, ":");
        char *docente = strtok(NULL, ":");

        if (!sala || !uc || !docente) {
            printf("Erro ao extrair campos na linha %d\n", i + 1);
            continue;
        }

        while (*sala == ' ') sala++;
        while (*uc == ' ') uc++;
        while (*docente == ' ') docente++;

        Data inicio = criarData(ano, mes, dia, hora, min);
        int fimHora = hora + (min + duracao) / 60;
        int fimMin = (min + duracao) % 60;
        Data fim = criarData(ano, mes, dia, fimHora, fimMin);

        printf("Lido evento %d:\n", i + 1);
        printf("  Sala: %s\n", sala);
        printf("  UC: %s\n", uc);
        printf("  Docente: %s\n", docente);
        printf("  Início: %02d:%02d → Fim: %02d:%02d\n",
               getHora(inicio), getMin(inicio),
               getHora(fim), getMin(fim));

        Evento evento = criarEvento(uc, docente, inicio, fim);
        if (!evento) {
            printf("Erro ao criar evento!\n");
            destruirData(inicio);
            destruirData(fim);
            continue;
        }

        inserirNaAgenda(agenda, sala, evento);
    }
}

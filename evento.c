#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"
#include "data.h"
#include "agenda.h"

struct evento {
    char uc[MAX_NOME];
    char docente[MAX_NOME];
    Data dataInicio;
    Data dataFim;
};

typedef struct nodeEvento {
    Evento evento;
    struct nodeEvento *proximo;
} *NodeEvento;

Evento criarEvento(const char *uc, const char *docente, Data inicio, Data fim) {
    if (uc == NULL || docente == NULL || inicio == NULL || fim == NULL) return NULL;

    Evento e = malloc(sizeof(struct evento));
    if (e == NULL) return NULL;

    strncpy(e->uc, uc, MAX_NOME - 1);
    e->uc[MAX_NOME - 1] = '\0';

    strncpy(e->docente, docente, MAX_NOME - 1);
    e->docente[MAX_NOME - 1] = '\0';

    e->dataInicio = inicio;
    e->dataFim = fim;

    return e;
}

void destruirEvento(Evento e) {
    if (e == NULL) return;
    destruirData(e->dataInicio);
    destruirData(e->dataFim);
    free(e);
}

NodeEvento criarNodeEvento(Evento e) {
    if (e == NULL) return NULL;

    NodeEvento node = malloc(sizeof(struct nodeEvento));
    if (node == NULL) return NULL;

    node->evento = e;
    node->proximo = NULL;
    return node;
}

void destruirListaEventos(NodeEvento lista) {
    NodeEvento atual;
    while (lista != NULL) {
        atual = lista;
        lista = getProximoEvento(lista);
        destruirEvento(getEvento(atual));
        free(atual);
    }
}

Data getDataInicio(Evento e) {
    if (e == NULL) return NULL;
    return e->dataInicio;
}

Data getDataFim(Evento e) {
    if (e == NULL) return NULL;
    return e->dataFim;
}

const char *getUC(Evento e) {
    if (e == NULL) return NULL;
    return e->uc;
}

const char *getDocente(Evento e) {
    if (e == NULL) return NULL;
    return e->docente;
}

NodeEvento getProximoEvento(NodeEvento n) {
    if (n == NULL) return NULL;
    return n->proximo;
}

Evento getEvento(NodeEvento n) {
    if (n == NULL) return NULL;
    return n->evento;
}

void setProximoEvento(NodeEvento n, NodeEvento proximo) {
    if (n != NULL) n->proximo = proximo;
}

NodeEvento espacoLivreEntreEventos(NodeEvento lista, Evento novoEvento) {
    Data inicioNovo = getDataInicio(novoEvento);
    Data fimNovo = getDataFim(novoEvento);

    NodeEvento atual = lista;
    NodeEvento anterior = NULL;

    while (atual != NULL) {
        Data inicioAtual = getDataInicio(getEvento(atual));
        if (anterior == NULL) {
            if (compararDatas(fimNovo, inicioAtual) <= 0) {
                return NULL; // Inserir no início
            }
        } else {
            Data fimAnterior = getDataFim(getEvento(anterior));
            if (compararDatas(fimAnterior, inicioNovo) <= 0 &&
                compararDatas(fimNovo, inicioAtual) <= 0) {
                return anterior; // Inserir entre anterior e atual
            }
        }
        anterior = atual;
        atual = getProximoEvento(atual);
    }

    // Se chegou ao fim, insere no fim (depois do último)
    return anterior;
}

void inserirNovoEvento(Agenda agenda, const char* nomeSala, Evento evento) {
    if (agenda == NULL || nomeSala == NULL || evento == NULL) {
        printf("ERRO: Parâmetros inválidos\n");
        return;
    }

    int i = procurarSala(nomeSala, agenda);
    if (i == -1) {
        criarSalaOrdenada(nomeSala, agenda);
        i = procurarSala(nomeSala, agenda);
    }

    Sala sala = getSala(agenda, i);
    NodeEvento lista = getEventos(sala);
    NodeEvento novo = criarNodeEvento(evento);

    if (novo == NULL) {
        printf("Erro ao criar nodo para evento.\n");
        destruirEvento(evento);
        return;
    }

    NodeEvento anterior = espacoLivreEntreEventos(lista, evento);

    if (anterior == NULL) {
        // Inserir no início
        setProximoEvento(novo, lista);
        setEventos(sala, novo);
    } else {
        // Inserir entre anterior e o seguinte
        setProximoEvento(novo, getProximoEvento(anterior));
        setProximoEvento(anterior, novo);
    }
}


void lerEvento(FILE* file, Agenda agenda) {
    int numEventos;
    fscanf(file, "%d\n", &numEventos);

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

        inserirNovoEvento(agenda, sala, evento);
    }
}
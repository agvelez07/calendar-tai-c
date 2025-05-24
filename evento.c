#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"
#include "data.h"

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

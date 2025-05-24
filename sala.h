#ifndef SALA_H
#define SALA_H

#include <stdio.h>
#include <stdlib.h>
#include "evento.h"

#define MAX_NOME 100

// Forward declaration, evita dependência circular
typedef struct agenda *Agenda;

typedef struct sala *Sala;

// Criação e gestão da sala
Sala iniciarSala(void);
void criarSala(Sala sala, const char *nome);
int existeSala(Sala sala);
int procurarSala(Sala sala, const char *nome);

const char *getNomeSala(Sala sala);
NodeEvento getEventos(Sala sala);
void setEventos(Sala sala, NodeEvento lista);

int verificarEspacoSala(Sala sala, Evento novoEvento);
void eliminarSala(Sala sala);

void criarSalaOrdenada(const char *nome, Agenda agenda);

#endif

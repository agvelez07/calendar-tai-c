#ifndef AGENDA_H
#define AGENDA_H

#include "sala.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SALAS 100

typedef struct agenda *Agenda;

Agenda inicializarAgenda(void);
void lerAgenda(FILE* file, Agenda agenda);

int getNumSalas(Agenda agenda);
Sala getSala(Agenda agenda, int i);

void setSala(Agenda agenda, int pos, Sala sala);
void deslocarSalasDireita(Agenda agenda, int ateIndice);
void incrementarNumSalas(Agenda agenda);

int verificarEspacoAgenda(Agenda agenda, const char *nomeSala, Evento e);
void inserirNaAgenda(Agenda agenda, const char* nomeSala, Evento e);

#endif

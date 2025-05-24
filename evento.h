#ifndef EVENTO_H
#define EVENTO_H

#include <stdio.h>
#include <stdlib.h>
#include "data.h"

#define MAX_NOME 100

typedef struct evento *Evento;
typedef struct nodeEvento *NodeEvento;

Evento criarEvento(const char *uc, const char *docente, Data inicio, Data fim);
void destruirEvento(Evento e);

 NodeEvento criarNodeEvento(Evento e);
void destruirListaEventos(NodeEvento lista);

Data getDataInicio(Evento e);
Data getDataFim(Evento e);
const char *getUC(Evento e);
const char *getDocente(Evento e);

NodeEvento getProximoEvento(NodeEvento n);
Evento getEvento(NodeEvento n);
void setProximoEvento(NodeEvento n, NodeEvento proximo);

#endif

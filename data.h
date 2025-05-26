#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct data *Data;

 Data criarData(int ano, int mes, int dia, int hora, int min);
void destruirData(Data data);

int compararDatas(Data d1, Data d2);
int compararDataFim(Data d1, Data d2);
int compararDataDeInicio(Data d1, Data d2);

int getAno(Data data);
int getMes(Data data);
int getDia(Data data);
int getHora(Data data);
int getMin(Data data);

#endif

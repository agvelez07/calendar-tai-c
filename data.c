#include <stdio.h>
#include <stdlib.h>
#include "data.h"

struct data {
    int ano;
    int mes;
    int dia;
    int hora;
    int min;
};

Data criarData(int ano, int mes, int dia, int hora, int min) {
    Data novaData = malloc(sizeof(struct data));
    if (novaData != NULL) {
        novaData->ano = ano;
        novaData->mes = mes;
        novaData->dia = dia;
        novaData->hora = hora;
        novaData->min = min;
    }
    return novaData;
}

void destruirData(Data data) {
    if (data != NULL) {
        free(data);
    }
}

int compararDatas(Data d1, Data d2) {
    if (d1->ano != d2->ano) return d1->ano - d2->ano;
    if (d1->mes != d2->mes) return d1->mes - d2->mes;
    if (d1->dia != d2->dia) return d1->dia - d2->dia;
    return d1->min - d2->min;
}

int compararDataDeInicio(Data d1, Data d2) {
    if(d1->ano != d2->ano || d1->mes != d2->mes || d1->dia != d2->dia) return 0;
    if(d1->hora > d2->hora) return 1;
    if(d1->hora == d2->hora && d1->min > d2->min) return 1;
    return 0;
}

int compararDataFim(Data d1, Data d2) {
    if(d1->ano != d2->ano || d1->mes != d2->mes || d1->dia != d2->dia) return 0;
    if(d1->hora < d2->hora) return 1;
    if(d1->hora == d2->hora && d1->min < d2->min) return 1;
    return 0;
}



/*
int getAno(Data data) {
    return (data != NULL) ? data->ano : -1;
}

int getMes(Data data) {
    return (data != NULL) ? data->mes : -1;
}

int getDia(Data data) {
    return (data != NULL) ? data->dia : -1;
}

int getHora(Data data) {
    return (data != NULL) ? data->hora : -1;
}

int getMin(Data data) {
    return (data != NULL) ? data->min : -1;
}
*/
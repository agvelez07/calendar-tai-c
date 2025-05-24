/*
*   AED 2024/2025 -
*
*   Trabalho 2
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"
#include "sala.h"
#include "evento.h"
#include "data.h"

void imprimirAgenda(Agenda agenda) {
    for (int i = 0; i < getNumSalas(agenda); i++) {
        Sala sala = getSala(agenda, i);
        if (!existeSala(sala)) continue;

        printf("Sala %s:\n", getNomeSala(sala));
        NodeEvento lista = getEventos(sala);

        while (lista != NULL) {
            Evento e = getEvento(lista);
            Data inicio = getDataInicio(e);
            Data fim = getDataFim(e);

            printf("  [%04d-%02d-%02d %02d:%02d → %02d:%02d] %s - %s\n",
                   getAno(inicio), getMes(inicio), getDia(inicio),
                   getHora(inicio), getMin(inicio),
                   getHora(fim), getMin(fim),
                   getUC(e), getDocente(e));

            lista = getProximoEvento(lista);
        }
        printf("\n");
    }
}

int main(void) {
    FILE *ficheiro = fopen("agenda.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro agenda.txt\n");
        return 1;
    }

    Agenda agenda = inicializarAgenda();
    if (agenda == NULL) {
        printf("Erro ao criar a agenda\n");
        fclose(ficheiro);
        return 1;
    }

    lerAgenda(ficheiro, agenda);
    fclose(ficheiro);

    imprimirAgenda(agenda);


    return 0;
}

/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "agenda.h"

#define BUFFER_SIZE 2048

// Buffer geral para ler string.
char buffer[BUFFER_SIZE];



// Ler a informa??o de uma linha de eventos
static void leLinhaEventos(FILE* fic, Sala sala)
{
	int numEventos, numSalas, linha;
    fscanf(fic, "%d %d\n", &numEventos, &numSalas);

    while (linha < numSalas) {
        int ano, mes, dia, hora, min, duracao;
        char* nomeSala, nomeEvento, nomeResponsavel;

        if (scanf(linha, "%d %d %d %d %d %d %[^\n]",
            &ano, &mes, &dia, &hora, &min, &duracao, &nomeSala, &nomeEvento, &nomeResponsavel) != 7) {
            printf("Linha mal formatada: %s\n", linha);
        }

        if (!existeSala(sala) && sala != NULL) {
            criarSala(nomeSala, sala);
        }
        else if (!existeSala(sala) && sala == NULL) {
            printf("Erro ao criar sala.\n");
            return;
        }
        linha++;

    }
}

int main(int argc, char* argv[])
{

    FILE* fagenda;
    FILE* feventos;

    Agenda minhaAgenda = inicializarAgenda();


    int d, m, a;
    int i;
    int nUtl;
    int nEventos;
    int nSalas;


    // Verificar se o programa ? chamado com o n?mero correto de argumento
    if (argc != 3) {
        printf("Numero de argumentos errados! %i \n", argc);
        exit(0);
    }

    // Verificar se os 2 ficheiros s?o abertos corretamente
    fagenda = fopen(argv[1], "r");
    if (fagenda == NULL) {
        printf("Ficheiro agenda n?o encontrado.\n");
        exit(0);
    }
    feventos = fopen(argv[2], "r");
    if (feventos == NULL) {
        printf("Ficheiro eventos n?o encontrado.\n");
        exit(0);
    }

    // **** Processar o ficheiro da agenda ****

    printf("\nConteudo do ficheiro AGENDA\n");

    // Ler o n?mero de eventos e o n?mero de salas no ficheiro agenda (note o espa?o depois do %i)
    fscanf(fagenda, "%i%i ", &nEventos, &nSalas);
    printf("N?mero de Eventos: %i\n", nEventos);
    printf("N?mero de Salas: %i\n", nSalas);

    // Ler todos os eventos da Agenda
    for (i = 0; i < nEventos; i++)
        leLinhaEventos(fagenda);



    // **** Processar o ficheiro da eventos ****

    printf("\nConteudo do ficheiro EVENTOS\n");
    // Ler o n?mero de eventos no ficheiro eventos (note o espa?o depois do %i)
    fscanf(feventos, "%i ", &nEventos);
    printf("N?mero de Eventos: %i\n", nEventos);

    // Ler todos os eventos
    for (i = 0; i < nEventos; i++)
        leLinhaEventos(feventos);

    // Fechar os ficheiro quando n?o foremnecess?rios
    fclose(fagenda);
    fclose(feventos);

}*/
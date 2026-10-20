#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HeaderEvento.h"
#include "HeaderAgenda.h"
#include "HeaderLista.h"
#include "HeaderUtils.h"

//Definição da estrutura Evento
typedef struct Evento {

    int ano, mes, dia;

    int hora, minutos;

    int duracao;

    char* Sala;

    char* Atividade;

    char* Docente;

} Evento;

// Função para criar um novo evento
ptrEvento criarEvento(int ano, int mes, int dia, int hora, int minutos, int duracao, char* Sala, char* Atividade, char* Docente) {

    ptrEvento Evento = (ptrEvento)malloc(sizeof(struct Evento));            // Aloca memória para um novo evento

    // Verifica se a alocação de memória foi bem-sucedida
    if (Evento != NULL) {

        Evento->ano = ano;

        Evento->mes = mes;

        Evento->dia = dia;

        Evento->hora = hora;

        Evento->minutos = minutos;

        Evento->duracao = duracao;

        Evento->Sala = (char*)malloc(sizeof(char) * (strlen(mystrcopyTrim(Sala)) + 1));                 // Aloca memória

        strcpy(Evento->Sala, Sala);                                                                     // Copia a string da sala

        Evento->Atividade = (char*)malloc(sizeof(char) * (strlen(mystrcopyTrim(Atividade)) + 1));       // Aloca memória

        strcpy(Evento->Atividade, Atividade);                                                           // Copia a string da atividade

        Evento->Docente = (char*)malloc(sizeof(char) * (strlen(mystrcopyTrim(Docente)) + 1));           // Aloca memória

        strcpy(Evento->Docente, Docente);                                                               //Copia a string do docente

        return Evento;
    }
    return NULL;                                                                                        // Retorna NULL se a alocação de memória falhar
}

// listar os detalhes de um evento
void ListarEvento(ptrEvento Evento) {

    printf("\nEvento na sala |%s|: %i-%i-%i %i:%i %ihora -> |%s|%s|\n",
        Evento->Sala, Evento->ano, Evento->mes, Evento->dia,
        Evento->hora, Evento->minutos, Evento->duracao,
        Evento->Atividade, Evento->Docente);
}

// apagar um evento e liberar a memória alocada
void ApagarEvento(ptrEvento Evento) {

    free(Evento->Sala);
    free(Evento->Atividade);
    free(Evento->Docente);
    free(Evento);
}

int getAno(ptrEvento Evento) { return Evento->ano; }

int getMes(ptrEvento Evento) { return Evento->mes; }

int getDia(ptrEvento Evento) { return Evento->dia; }

int getHora(ptrEvento Evento) { return Evento->hora; }

int getMinutos(ptrEvento Evento) { return Evento->minutos; }

int getDuracao(ptrEvento Evento) { return Evento->duracao; }

char* getSala(ptrEvento Evento) { return Evento->Sala; }

char* getAtividade(ptrEvento Evento) { return Evento->Atividade; }

char* getDocente(ptrEvento Evento) { return Evento->Docente; }


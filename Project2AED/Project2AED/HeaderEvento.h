#ifndef HEADER_EVENTO_H
#define HEADER_EVENTO_H

#include <stdio.h>
#include <string.h>

typedef struct Evento* ptrEvento;

ptrEvento criarEvento(int ano, int mes, int dia, int hora, int minutos, int duracao, char* Sala, char* Atividade, char* docente);

void ListarEvento(ptrEvento evento);

void ApagarEvento(ptrEvento evento);

int getAno(ptrEvento);
int getMes(ptrEvento);
int getDia(ptrEvento);
int getHora(ptrEvento);
int getMinutos(ptrEvento);
int getDuracao(ptrEvento);
char* getSala(ptrEvento);
char* getAtividade(ptrEvento);
char* getDocente(ptrEvento);

#endif // !HEADER_EVENTO_H



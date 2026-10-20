#ifndef HEADERAGENDA_H
#define HEADERAGENDA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HeaderEvento.h"
#include "HeaderLista.h"

typedef struct Agenda* ptrAgenda;

typedef struct Sala* ptrSala;

ptrAgenda criarAgenda(int);

int adicionarSala(ptrAgenda, char*);

void printAgenda(ptrAgenda);

void liberarAgenda(ptrAgenda);

ptrSala obterSala(ptrAgenda, char*);

link obterEventos(ptrSala);

void adicionarEventoASala(ptrSala, ptrEvento);

void definirEventos(ptrSala, link);

int ErroEspacoTempoOcupado(ptrAgenda, ptrEvento);

void listarEventosSala(ptrAgenda);

void listarProximosEventos(ptrAgenda);

void listarEventosData(ptrAgenda);

void listarEventosEntreDatas(ptrAgenda);

void apagarEvento(ptrAgenda);

void apagarEventosAnteriores(ptrAgenda);

ptrEvento* coletarEventosFuturos(ptrAgenda, int, int, int, int);

int ArmazenaTodosEventos(ptrAgenda, ptrEvento*);

void escreverEventosOrdenadosNoArquivo(ptrAgenda, FILE*);





#endif // !HEADERAGENDA_H

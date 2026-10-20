#ifndef HEADER_LISTA_H
#define HEADER_LISTA_H
#include "HeaderEvento.h"


typedef struct nodeLista* link;


void printItem(ptrEvento);

link newNode(ptrEvento, link);

void freeNode(link);

link next(link);

void setNext(link, link);

void insertNext(link, link);

ptrEvento getEvento(link);

link inserirInicio(link, ptrEvento);

link apagarInicio(link);

void printLista(link);

link InserirOrdenadoLista(link, ptrEvento);

#endif // !HEADER_LISTA_H





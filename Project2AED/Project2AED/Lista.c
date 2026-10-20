#include <stdio.h>
#include <stdlib.h>
#include "HeaderAgenda.h"
#include "HeaderEvento.h"
#include "HeaderLista.h"
#include "HeaderMergesort.h"

// Definição de tipos e estrutura para a lista ligada

typedef ptrEvento Item;                         //Definição de Item como um ponteiro para Evento

typedef struct nodeLista {

    Item Evento;                                

    link next;                                  // Ponteiro para o próximo nó na lista

} nodeLista;

//imprimir um evento
void printItem(ptrEvento Evento) {

    printf("%i %i %i %i %i %i %s:%s:%s\n",
        getAno(Evento), getMes(Evento),
        getDia(Evento), getHora(Evento),
        getMinutos(Evento), getDuracao(Evento),
        getSala(Evento), getAtividade(Evento),
        getDocente(Evento));
}

//criar um novo nó
link newNode(ptrEvento Evento, link l) {

    link no;

    no = (link)malloc(sizeof(struct nodeLista));

    no->Evento = Evento;

    no->next = l;

    return no;
}

//liberar a memória de um nó
void freeNode(link l) {
    free(l);
}

//obter o próximo nó na lista
link next(link l) {
    return l->next;
}

//definir o próximo nó
void setNext(link node, link nextNode) {
    node->next = nextNode;
}

// obter o evento de um nó
ptrEvento getEvento(link l) {
    return l->Evento;
}

//inserir um nó depois de outro nó
void insertNext(link x, link t) {
    t->next = x->next;
    x->next = t;
}

//inserir um evento no início da lista
link inserirInicio(link l, ptrEvento Evento) {
    l = newNode(Evento, l);
    return l;
}

//apagar o nó do início da lista
link apagarInicio(link l) {
    link aux = l;
    l = next(l);
    freeNode(aux);
    return l;
}

//imprimir todos os eventos da lista
void printLista(link l) {
    link aux;
    for (aux = l; aux != NULL; aux = next(aux))
        printItem(getEvento(aux));
    printf("\n");
}


//percorrer a lista e inserir um evento de forma ordenada
link InserirOrdenadoLista(link listaEventos, ptrEvento novoEvento) {

    // Verifica se a lista está vazia ou se o novo evento deve ser inserido no início

    if (listaEventos == NULL || compararEventos(novoEvento, getEvento(listaEventos)) < 0) {
        return inserirInicio(listaEventos, novoEvento);  // Insere no início
    }

    // Percorre a lista até encontrar a posição correta para inserir o novo evento
    link current = listaEventos;

    while (current->next != NULL && compararEventos(novoEvento, getEvento(current->next)) >= 0) {
        current = current->next;
    }

    // Insere o novo evento na posição correta
    link novo = newNode(novoEvento, current->next);

    current->next = novo;

    return listaEventos;
}




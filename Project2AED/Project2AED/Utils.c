#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HeaderEvento.h"
#include "HeaderAgenda.h"
#include "HeaderLista.h"

// Função para remover espaços em branco do início e do final de uma string
char* mystrcopyTrim(char* str) {
    int countLeft = 0;                      // Contador para espaços em branco à esquerda
    int countRight = 0;                     // Contador para espaços em branco à direita
    int i;
    int tam = strlen(str);                  // Comprimento da string original

    // Conta os espaços em branco à esquerda
    for (i = 0; i < tam; i++)
        if (str[i] == ' ')
            countLeft++;
        else
            break;

    // Conta os espaços em branco à direita
    for (i = tam - 1; i >= 0; i--)
        if (str[i] == ' ')
            countRight++;
        else
            break;

    // Calcula o novo tamanho da string, removendo os espaços em branco
    tam = tam - countLeft - countRight;
    tam = tam < 0 ? 0 : tam;                // Garante que o tamanho não seja negativo

    // Aloca memória para a nova string
    char* s2 = malloc(sizeof(char) * (tam + 1));

    // Copia a parte útil da string original para a nova string
    if (tam > 0)
        strncpy(s2, str + countLeft, tam);
    s2[tam] = '\0';                         // Adiciona o caractere nulo ao final da nova string

    return s2;
}

// Função para comparar dois eventos
int compararEventos(ptrEvento evento1, ptrEvento evento2) {
    // Compara os anos
    if (getAno(evento1) < getAno(evento2)) {
        return -1;
    }
    else if (getAno(evento1) > getAno(evento2)) {
        return 1;
    }
    // Compara os meses
    else if (getMes(evento1) < getMes(evento2)) {
        return -1;
    }
    else if (getMes(evento1) > getMes(evento2)) {
        return 1;
    }
    // Compara os dias
    else if (getDia(evento1) < getDia(evento2)) {
        return -1;
    }
    else if (getDia(evento1) > getDia(evento2)) {
        return 1;
    }
    // Compara as horas
    else if (getHora(evento1) < getHora(evento2)) {
        return -1;
    }
    else if (getHora(evento1) > getHora(evento2)) {
        return 1;
    }
    // Compara os minutos
    else if (getMinutos(evento1) < getMinutos(evento2)) {
        return -1;
    }
    else if (getMinutos(evento1) > getMinutos(evento2)) {
        return 1;
    }
    // Se todos os campos anteriores são iguais, compara as salas
    else {
        return strcmp(getSala(evento1), getSala(evento2));
    }
}

// Função auxiliar para comparar duas datas
int diferencaDatas(int ano1, int mes1, int dia1, int ano2, int mes2, int dia2) {
    if (ano1 != ano2)
        return ano1 - ano2;
    if (mes1 != mes2)
        return mes1 - mes2;
    return dia1 - dia2;
}

// Função para verificar se um evento ocorre entre duas datas
int dataEntreDatas(ptrEvento evento, int ano1, int mes1, int dia1, int ano2, int mes2, int dia2) {
    // Verifica se o evento ocorre após a primeira data e antes da segunda data

    if ((getAno(evento) > ano1 || (getAno(evento) == ano1 && getMes(evento) > mes1) || (getAno(evento) == ano1 && getMes(evento) == mes1 && getDia(evento) >= dia1)) &&
        (getAno(evento) < ano2 || (getAno(evento) == ano2 && getMes(evento) < mes2) || (getAno(evento) == ano2 && getMes(evento) == mes2 && getDia(evento) <= dia2))) {
        return 1;                               // O evento ocorre entre as duas datas
    }

    return 0;                                   // O evento não ocorre entre as duas datas
}

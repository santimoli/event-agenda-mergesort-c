#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HeaderEvento.h"
#include "HeaderAgenda.h"
#include "HeaderLista.h"
#include "HeaderMergesort.h"
#include "HeaderUtils.h"

// Definição da estrutura Sala
typedef struct Sala {

    char* nomesala;                                             // Nome da sala

    link EventosDeLista;                                        // link para os eventos associados à sala

} Sala;

// Definição da estrutura Agenda
typedef struct Agenda {

    int numSalas;                                               // Número de salas

    ptrSala* salas;                                             // Array de ponteiros para salas

} Agenda;

// Função para criar uma nova agenda com um número inicial de salas
ptrAgenda criarAgenda(int numSalas) {

    ptrAgenda agenda = (ptrAgenda)malloc(sizeof(Agenda));       // Alocação de memória para a agenda

    agenda->numSalas = 2 * numSalas;                            // Define o número de salas como o dobro para depois o utilizador poder inserir mais eventos

    agenda->salas = (ptrSala*)malloc(agenda->numSalas * sizeof(ptrSala));  // Alocação de memória para o array de salas

    for (int i = 0; i < agenda->numSalas; i++) {
        agenda->salas[i] = NULL;                                // Inicializa cada posição do array de salas com NULL
    }

    return agenda;                                              // Retorna a agenda criada
}

// Função para adicionar uma nova sala à agenda
int adicionarSala(ptrAgenda agenda, char* nomeSala) {

    for (int i = 0; i < agenda->numSalas; i++) {

        if (agenda->salas[i] == NULL) {                         // Encontra a primeira posição livre no array de salas

            ptrSala sala = (ptrSala)malloc(sizeof(Sala));       // Aloca memória para a nova sala

            nomeSala[strcspn(nomeSala, "\n")] = '\0';           // Remove o caractere de nova linha, se existir

            sala->nomesala = strdup(nomeSala);                  // Duplica a string do nome da sala retornando um ponteiro para essa sequência de carateres

            sala->EventosDeLista = NULL;                        // Inicializa a lista de eventos da sala com NULL

            agenda->salas[i] = sala;                            // Adiciona a nova sala à agenda

            printf("\nSala '%s' adicionada na posicao %i.\n", nomeSala, i);

            return 1;                                           // Retorna 1 com sucesso
        }
    }
    printf("\nNumero maximo de salas atingido para adicionar a sala '%s'!!!\n", nomeSala);

    return 0;                                                   // Retorna 0 se o número máximo de salas foi atingido
}

//listar todas as salas e os seus eventos na agenda
void printAgenda(ptrAgenda agenda) {

    for (int i = 0; i < agenda->numSalas; i++) {

        if (agenda->salas[i] != NULL) {                         // Verifica se a sala não é NULL

            printf("Sala: %s\n", agenda->salas[i]->nomesala);   // Imprime o nome da sala

            printLista(agenda->salas[i]->EventosDeLista);       // Imprime a lista de eventos da sala
        }
    }
}

// liberar a memória de uma agenda e suas salas
void liberarAgenda(ptrAgenda agenda) {

    for (int i = 0; i < agenda->numSalas; i++) {

        if (agenda->salas[i] != NULL) {

            free(agenda->salas[i]->nomesala);                   // Libera a memória do nome da sala

            link l = agenda->salas[i]->EventosDeLista;          // Obtém a lista de eventos da sala

            while (l != NULL) {
                l = apagarInicio(l);                            // Libera a memória de cada nó da lista de eventos
            }

            free(agenda->salas[i]);                             // Libera a memória da estrutura da sala
        }
    }
    free(agenda->salas);                                        // Libera a memória do array de salas
    free(agenda);                                               // Libera a memória da estrutura da agenda
}

// Função para obter uma sala da agenda pelo nome
ptrSala obterSala(ptrAgenda agenda, char* nomeSala) {

    for (int i = 0; i < agenda->numSalas; i++) {

        if ((agenda->salas[i] != NULL) && (strcmp(agenda->salas[i]->nomesala, nomeSala) == 0)) {
            return agenda->salas[i];                            // Retorna a sala se o nome coincidir
        }
    }
    return NULL;                                                // Retorna NULL se a sala não for encontrada
}

//obter a lista de eventos de uma sala
link obterEventos(ptrSala sala) {
    return sala->EventosDeLista;
}

//definir a lista de eventos de uma sala
void definirEventos(ptrSala sala, link eventos) {
    sala->EventosDeLista = eventos;
}


//verificar se há conflitos de tempo e espaço para um novo evento na agenda
int ErroEspacoTempoOcupado(ptrAgenda agenda, ptrEvento novoEvento) {

    for (int i = 0; i < agenda->numSalas; i++) {

        if (agenda->salas[i] != NULL) {

            link noAtual = agenda->salas[i]->EventosDeLista;

            while (noAtual != NULL) {
                ptrEvento eventoAtual = getEvento(noAtual);

                // Verifica se há sobreposição de tempo entre o novo evento e os eventos existentes
                if (strcmp(getSala(novoEvento), getSala(eventoAtual)) == 0 &&
                    getAno(novoEvento) == getAno(eventoAtual) &&
                    getMes(novoEvento) == getMes(eventoAtual) &&
                    getDia(novoEvento) == getDia(eventoAtual) &&
                    ((getHora(novoEvento) * 60 + getMinutos(novoEvento) >= getHora(eventoAtual) * 60 + getMinutos(eventoAtual) &&
                        getHora(novoEvento) * 60 + getMinutos(novoEvento) < getHora(eventoAtual) * 60 + getMinutos(eventoAtual) + getDuracao(eventoAtual) * 60) ||
                        (getHora(eventoAtual) * 60 + getMinutos(eventoAtual) >= getHora(novoEvento) * 60 + getMinutos(novoEvento) &&
                            getHora(eventoAtual) * 60 + getMinutos(eventoAtual) < getHora(novoEvento) * 60 + getMinutos(novoEvento) + getDuracao(novoEvento) * 60))) {
                    return 0; // Espaço e tempo ocupado
                }

                noAtual = next(noAtual);
            }
        }
    }
    return 1;                                                   // Espaço e tempo disponível
}

// listar todos os eventos de uma sala específica
void listarEventosSala(ptrAgenda agenda) {

    char nomesala[2048];

    printf("Digite o nome da sala: ");

    scanf("%s", nomesala);

    ptrSala sala = obterSala(agenda, nomesala);                 // Obtém a sala pelo nome

    if (sala == NULL) {

        printf("\nSala '%s' nao encontrada.\n", nomesala);

        return;

    }

    link eventos = obterEventos(sala);                          // Obtém a lista de eventos da sala

    if (eventos == NULL) {

        printf("\nNao ha eventos na sala '%s'.\n", nomesala);

        return;
    }
    printf("\nEventos na sala '%s':\n", nomesala);

    printLista(eventos);                                        // Imprime a lista de eventos da sala
}

//listar os próximos n eventos na agenda
void listarProximosEventos(ptrAgenda agenda) {
    int n;

    printf("Indique os proximos eventos que queira que sejam listados: ");

    scanf("%i", &n);

    //Cria um array para armazenar todos os eventos
    int totalEventos = agenda->numSalas * n;            // Máximo de eventos possíveis

    ptrEvento* todosEventos = (ptrEvento*)malloc(totalEventos * sizeof(ptrEvento));

    if (todosEventos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    int count = 0;

    // Itera sobre todas as salas

    for (int i = 0; i < agenda->numSalas; i++) {

        ptrSala sala = agenda->salas[i];

        if (sala != NULL) {

            link eventos = obterEventos(sala);

            // Itera sobre os eventos da sala e adiciona ao array

            int salaCount = 0;

            while (eventos != NULL && salaCount < n) {

                todosEventos[count++] = getEvento(eventos);

                eventos = next(eventos);

                salaCount++;
            }
        }
    }

    mergesort(todosEventos, 0, count - 1);              // Ordena todos os eventos coletados

    // Lista os próximos n eventos
    printf("Proximos %i eventos:\n", n);

    for (int i = 0; i < count && i < n; i++) {
        ListarEvento(todosEventos[i]);
    }

    free(todosEventos);
}

void listarEventosData(ptrAgenda agenda) {
    int ano, mes, dia;

    printf("Digite a data no formato 'ano mes dia': ");

    scanf("%i%i%i", &ano, &mes, &dia);

    int encontrou = 0;

    // Iterar sobre todas as salas na agenda
    for (int i = 0; i < agenda->numSalas; i++) {

        ptrSala sala = agenda->salas[i];

        if (sala != NULL) {

            link eventos = obterEventos(sala);

            // Iterar sobre todos os eventos da sala

            while (eventos != NULL) {

                ptrEvento evento = getEvento(eventos);

                // Verificar se o evento ocorre na data especificada
                if (getAno(evento) == ano && getMes(evento) == mes && getDia(evento) == dia) {

                    ListarEvento(evento);
                    encontrou = 1;
                }
                eventos = next(eventos);
            }
        }
    }

    if (!encontrou) {
        printf("Nenhum evento encontrado para a data especificada.\n");
    }
}
void listarEventosEntreDatas(ptrAgenda agenda) {

    int ano1, mes1, dia1;
    int ano2, mes2, dia2;

    printf("Digite a primeira data no formato 'ano mes dia': ");

    scanf("%i%i%i", &ano1, &mes1, &dia1);

    printf("Digite a segunda data no formato 'ano mes dia': ");

    scanf("%i%i%i", &ano2, &mes2, &dia2);

    int encontrou = 0;
    int numEventos = 0;

    // Garante que a primeira data seja anterior à segunda data
    if (ano1 > ano2 || (ano1 == ano2 && mes1 > mes2) || (ano1 == ano2 && mes1 == mes2 && dia1 > dia2)) {
        printf("Erro: A primeira data deve ser anterior a segunda data.\n");
        return;
    }

    // Itera sobre todas as salas para contar quantos eventos estão entre as datas
    int count = 0;

    for (int i = 0; i < agenda->numSalas; i++) {

        ptrSala sala = agenda->salas[i];

        if (sala != NULL) {

            link eventos = obterEventos(sala);

            // Itera sobre os eventos da sala
            while (eventos != NULL) {

                ptrEvento evento = getEvento(eventos);

                // Verifica se o evento ocorre dentro do intervalo de datas especificado
                if (dataEntreDatas(evento, ano1, mes1, dia1, ano2, mes2, dia2)) {
                    count++;
                    encontrou = 1;
                }
                eventos = next(eventos);
            }
        }
    }

    // Se não houver eventos
    if (!encontrou) {
        printf("Nenhum evento encontrado para o intervalo de datas especificado.\n");
        return;
    }

    // Cria um array para armazenar os eventos encontrados
    ptrEvento* eventosEntreDatas = (ptrEvento*)malloc(count * sizeof(ptrEvento));

    if (eventosEntreDatas == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    count = ArmazenaEventosArrayEntreDatas(agenda, eventosEntreDatas, ano1, mes1, dia1, ano2, mes2, dia2);

    mergesort(eventosEntreDatas, 0, count - 1);


    // Lista os eventos encontrados
    printf("Eventos entre %i %i %i e %i %i %i:\n", dia1, mes1, ano1, dia2, mes2, ano2);

    for (int i = 0; i < count; i++) {
        ListarEvento(eventosEntreDatas[i]);
    }

    // Libera a memória alocada para o array de eventos
    free(eventosEntreDatas);
}

void apagarEvento(ptrAgenda agenda) {
    int ano, mes, dia, hora, min;
    char sala[2048];

    printf("Digite a data e hora de inicio do evento no formato 'ano mes dia hora min': ");

    scanf("%i%i%i%i%i", &ano, &mes, &dia, &hora, &min);

    getchar();                                  //Limpa o buffer de entrada

    printf("Digite a sala: ");

    fgets(sala, 2048, stdin);

    sala[strlen(sala) - 1] = '\0';              // Remove o caractere de nova linha

    // Procura a sala na agenda
    ptrSala Sala = obterSala(agenda, sala);

    if (Sala == NULL) {
        printf("Sala nao encontrada.\n");
        return;
    }

    // Procura o evento na lista de eventos da sala
    link eventos = obterEventos(Sala);

    link prev = NULL;

    link atual = eventos;
    while (atual != NULL) {

        ptrEvento evento = getEvento(atual);

        if (getAno(evento) == ano && getMes(evento) == mes && getDia(evento) == dia &&
            getHora(evento) == hora && getMinutos(evento) == min) {
           
            if (prev == NULL) {
                Sala->EventosDeLista = next(atual);
            }
            else {
                setNext(prev, next(atual));
            }

            ApagarEvento(evento);

            free(atual);                        // Libera o nó da lista

            printf("Evento removido com sucesso.\n");

            return;
        }
        prev = atual;
        atual = next(atual);
    }

    printf("Evento nao encontrado.\n");
}

void apagarEventosAnteriores(ptrAgenda agenda) {

    int ano, mes, dia;

    printf("Digite a data no formato 'ano mes dia': ");

    scanf("%i %i %i", &ano, &mes, &dia);

    for (int i = 0; i < agenda->numSalas; i++) {

        if (agenda->salas[i] != NULL) {

            link prev = NULL;

            link atual = agenda->salas[i]->EventosDeLista;

            while (atual != NULL) {

                ptrEvento evento = getEvento(atual);

                if (diferencaDatas(getAno(evento), getMes(evento), getDia(evento), ano, mes, dia) < 0) {
                    
                    if (prev == NULL) {
                        agenda->salas[i]->EventosDeLista = next(atual);
                    }
                    else {
                        setNext(prev, next(atual));
                    }

                    link toDelete = atual;

                    atual = next(atual);

                    ApagarEvento(evento);

                    free(toDelete);                     // Libera o nó da lista
                }
                else {
                    prev = atual;
                    atual = next(atual);
                }
            }
        }
    }
    printf("Eventos anteriores a %i-%02i-%02i foram apagados.\n", ano, mes, dia);
}

// Função para contar os eventos futuros de uma sala específica
int ContaEventosFuturosSala(ptrSala sala, int ano, int mes, int dia) {

    int count = 0;

    link eventos = obterEventos(sala);

    while (eventos != NULL) {

        ptrEvento evento = getEvento(eventos);

        if (getAno(evento) > ano || (getAno(evento) == ano && getMes(evento) > mes) || (getAno(evento) == ano && getMes(evento) == mes && getDia(evento) >= dia)) {
            count++;
        }
        eventos = next(eventos);
    }
    return count;
}

ptrEvento* coletarEventosFuturos(ptrAgenda agenda, int ano, int mes, int dia, int n) {
    
    int totalEventos = 0;

    for (int i = 0; i < agenda->numSalas; i++) {

        ptrSala sala = agenda->salas[i];

        if (sala != NULL) {
            totalEventos += ContaEventosFuturosSala(sala, ano, mes, dia);
        }
    }

    // Alocar memória para armazenar os eventos futuros
    ptrEvento* eventosFuturos = (ptrEvento*)malloc(totalEventos * sizeof(ptrEvento));

    if (eventosFuturos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    //Armazena os eventos futuros de todas as salas
    int count = 0;
    for (int i = 0; i < agenda->numSalas; i++) {

        ptrSala sala = agenda->salas[i];

        if (sala != NULL) {

            link eventos = obterEventos(sala);

            while (eventos != NULL) {

                ptrEvento evento = getEvento(eventos);

                if (getAno(evento) > ano || (getAno(evento) == ano && getMes(evento) > mes) || (getAno(evento) == ano && getMes(evento) == mes && getDia(evento) >= dia)) {
                    eventosFuturos[count++] = evento;
                }
                eventos = next(eventos);
            }
        }
    }

    // Ordenar os eventos futuros
    mergesort(eventosFuturos, 0, totalEventos - 1);

    return eventosFuturos;
}



int ArmazenaEventosArrayEntreDatas(ptrAgenda agenda, ptrEvento* eventosEntreDatas, int ano1, int mes1, int dia1, int ano2, int mes2, int dia2) {
   
    int index = 0;

    for (int i = 0; i < agenda->numSalas; i++) {

        ptrSala sala = agenda->salas[i];

        if (sala != NULL) {

            link eventos = obterEventos(sala);
            // Itera sobre os eventos da sala

            while (eventos != NULL) {

                ptrEvento evento = getEvento(eventos);
                // Verifica se o evento ocorre dentro do intervalo de datas especificado
                if (dataEntreDatas(evento, ano1, mes1, dia1, ano2, mes2, dia2)) {
                    eventosEntreDatas[index++] = evento;
                }
                eventos = next(eventos);
            }
        }
    }
    return index;
}




int ArmazenaTodosEventos(ptrAgenda agenda, ptrEvento* eventos) {
    int numEventos = 0;

    for (int i = 0; i < agenda->numSalas; i++) {

        if (agenda->salas[i] != NULL) {

            link eventoList = obterEventos(agenda->salas[i]);

            while (eventoList != NULL) {
                eventos[numEventos++] = getEvento(eventoList);
                eventoList = next(eventoList);
            }
        }
    }
    return numEventos;
}


void escreverEventosOrdenadosNoArquivo(ptrAgenda agenda, FILE* file) {

    int numEventos = 0;
    // Primeiro, contamos o número total de eventos
    for (int i = 0; i < agenda->numSalas; i++) {

        if (agenda->salas[i] != NULL) {

            link eventoList = obterEventos(agenda->salas[i]);

            while (eventoList != NULL) {
                numEventos++;
                eventoList = next(eventoList);
            }
        }
    }

    if (numEventos == 0) {
        printf("Nenhum evento para escrever no arquivo.\n");
        return;
    }


    // Alocamos memória para armazenar todos os eventos
    ptrEvento* eventos = (ptrEvento*)malloc(numEventos * sizeof(ptrEvento));

    if (eventos == NULL) {
        printf("Erro ao alocar memória para os eventos.\n");
        return;
    }

    //Armazenamos todos os eventos em um array 

    numEventos = ArmazenaTodosEventos(agenda, eventos);

    // Ordenamos o array de eventos
    mergesort(eventos, 0, numEventos - 1);

    // Escrevemos os eventos ordenados no arquivo
    FILE* arquivo = fopen(file, "a");

    if (arquivo == NULL) {

        printf("Erro ao abrir o arquivo %s para escrita.\n", file);

        free(eventos);

        return;
    }

    for (int i = 0; i < numEventos; i++) {

        ptrEvento evento = eventos[i];

        fprintf(arquivo, "%i %i %i %i %i %i %s : %s : %s\n", getAno(evento), getMes(evento),
            getDia(evento), getHora(evento), getMinutos(evento), getDuracao(evento),
            getSala(evento), getAtividade(evento), getDocente(evento));
    }

    fclose(arquivo);
    free(eventos);
}



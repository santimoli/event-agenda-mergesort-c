#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HeaderEvento.h"
#include "HeaderAgenda.h"
#include "HeaderLista.h"
#include "HeaderUtils.h"
#include "HeaderMergesort.h"

void escreveLinhaEventosErro(ptrEvento);

#define BUFFER_SIZE 2048


char buffer[BUFFER_SIZE];                                                       // Buffer geral para ler string.


// Fun��o para mostrar o menu ao utilizador
int menu() {
    int opcao;

    printf("\n\n  *** MENU ***\n\n");

    printf("1 -> Criar Evento\n");
    printf("2 -> Listar os eventos de uma sala\n");
    printf("3 -> Listar os eventos de uma sala para um determinado dia.\n");
    printf("4 -> Listar os proximos n eventos.\n");
    printf("5 -> Listar os proximos n eventos a partir de uma determinada data.\n");
    printf("6 -> Listar todos eventos de um determinado dia.\n");
    printf("7 -> Listar os eventos entre 2 datas.\n");
    printf("8 -> Apagar evento (indicando o inicio do evento e a sala).\n");
    printf("9 -> Apagar todos os eventos anteriores a uma determinada data.\n");
    printf("10 ->Listar Agenda (Opcao para verificar).\n");
    printf("0 -> Sair do menu\n");

    printf("\n-> Indique a sua opcao: ");
    scanf("%i", &opcao);

    return opcao;
}

//criar um evento a partir de informa��es fornecidas pelo usu�rio
void criarEventoPorUsuario(ptrAgenda agenda) {
    char* sala;
    char* uc;
    char* docente;
    int ano, mes, dia, hora, min, duracao;

    printf("\n\nDigite as informacoes do evento no formato 'ano mes dia hora min duracao sala : uc : docente':");

    fgets(buffer, BUFFER_SIZE, stdin);

    scanf("%i%i%i%i%i%i", &ano, &mes, &dia, &hora, &min, &duracao);           // Leitura dos dados do evento
    // Ler a string at� ao fim da linha
    fgets(buffer, BUFFER_SIZE, stdin);

    buffer[strlen(buffer) - 1] = '\0';

    // Separa a string nas 3 partes
    sala = mystrcopyTrim(strtok(buffer, ":"));
    uc = mystrcopyTrim(strtok(NULL, ":"));
    docente = mystrcopyTrim(strtok(NULL, ":"));

    ptrEvento Evento = criarEvento(ano, mes, dia, hora, min, duracao, sala, uc, docente); // Cria o novo evento

    // Verifica se n�o h� eventos sobrepostos
    if (!ErroEspacoTempoOcupado(agenda, Evento)) {

        printf("\nNao foi possivel adicionar o evento '%s'! Ja existe um evento a ocorrer durante esse periodo de tempo.\n", getAtividade(Evento));

        escreveLinhaEventosErro(Evento);                            //Escreve o evento no ficheiro ErroEventos.txt

        ApagarEvento(Evento);                                       // Libera a mem�ria alocada para o evento

        return;
    }

    // Obt�m a sala ou cria uma nova se n�o existir
    ptrSala NovaSala = obterSala(agenda, sala);

    if (NovaSala == NULL) {

        if (adicionarSala(agenda, sala) != 1) {                     //Se a fun��o retornar 0 , ent�o o n�mero maximo de salas foi atingido

            escreveLinhaEventosErro(Evento);                        //Escreve o evento no ficheiro ErroEventos.txt

            ApagarEvento(Evento);                                   // Libera a mem�ria alocada para o evento

            return;
        }
        NovaSala = obterSala(agenda, sala);                         //Cria uma nova sala
    }

    link eventos = obterEventos(NovaSala);                          //Obter a lista de eventos da sala

    eventos = InserirOrdenadoLista(eventos, Evento);                //Inserir o novo evento na lista de eventos da sala em ordem cronol�gica

    definirEventos(NovaSala, eventos);                              // Atualizar a lista de eventos da sala


}


//escrever Eventos com erro no ficheiro ErroEventos.txt
void escreveLinhaEventosErro(ptrEvento Evento) {

    FILE* feventos_erro;

    feventos_erro = fopen("eventos-erro.txt", "a");

    if (feventos_erro == NULL) {

        printf("Ficheiro eventos-erro nao encontrado.\n");

        exit(0);
    }

    fprintf(feventos_erro, "%i %i %i %i %i %i %s : %s : %s\n", getAno(Evento), getMes(Evento),

        getDia(Evento), getHora(Evento),
        getMinutos(Evento), getDuracao(Evento),
        getSala(Evento), getAtividade(Evento),
        getDocente(Evento));

    fclose(feventos_erro);
}

//Ler a informa��o de uma linha de eventos e adicionar � agenda
void leLinhaEventosAgenda(FILE* fic, ptrAgenda agenda) {
    char* sala;
    char* uc;
    char* docente;
    int ano, mes, dia, hora, min, duracao;

    // Ler a data, hora e dura��o
    fscanf(fic, "%i %i %i %i %i %i ", &ano, &mes, &dia, &hora, &min, &duracao);
    // Ler a string at� ao fim da linha

    fgets(buffer, BUFFER_SIZE, fic);

    buffer[strlen(buffer) - 1] = '\0';
    // Separa a string nas 2 partes
    sala = mystrcopyTrim(strtok(buffer, ":"));
    uc = mystrcopyTrim(strtok(NULL, ":"));
    docente = mystrcopyTrim(strtok(NULL, ":"));

    printf("\nSala '%s' : %i %i %i %i:%i %i : %s : %s\n", sala, ano, mes, dia, hora, min, duracao, uc, docente);

    ptrEvento Evento = criarEvento(ano, mes, dia, hora, min, duracao, sala, uc, docente);

    if (Evento != NULL) {
        printf("\nEvento criado com sucesso!!!"); 
    }

    if (!ErroEspacoTempoOcupado(agenda, Evento)) {

        printf("\nNao foi possivel adicionar o evento '%s'! Ja existe um evento a ocorrer durante esse periodo de tempo.\n", getAtividade(Evento));

        escreveLinhaEventosErro(Evento);                        //Escreve o evento no ficheiro ErroEventos.txt

        ApagarEvento(Evento);                                   // Libera a mem�ria alocada para o evento
    }
    else {

        ptrSala novaSala = obterSala(agenda, sala);             //Encontra a sala

        if (novaSala == NULL) {                                 //Se a sala n�o foi encontrada

            adicionarSala(agenda, sala);                        //Se a fun��o retornar 0 , ent�o j� n�o h� espa�o disponivel para criar uma sala

            novaSala = obterSala(agenda, sala);                 //Encontra a sala
        }
        link eventos = obterEventos(novaSala);                  //Retorna a lista

        eventos = InserirOrdenadoLista(eventos, Evento);        //Insere ordenadamente em rela��o � data

        definirEventos(novaSala, eventos);                      //Define o Evento
    }
}


// Listar os eventos de uma sala em um determinado dia
void listarEventosSalaDia(ptrAgenda agenda) {
    char* sala;
    int ano, mes, dia;

    printf("\n\nDigite a data e a sala no formato 'ano mes dia:sala':");

    scanf("%i%i%i", &ano, &mes, &dia);

    // Ler a string at� ao fim da linha
    fgets(buffer, BUFFER_SIZE, stdin);

    buffer[strlen(buffer) - 1] = '\0';

    sala = mystrcopyTrim(strtok(buffer, ":"));                 // Separa a string nas 2 partes

    // Obter a sala da agenda
    ptrSala Sala = obterSala(agenda, sala);

    if (Sala == NULL) {
        printf("Sala nao encontrada.\n");
        return;
    }

    // Obter os eventos da sala
    link eventos = obterEventos(Sala);

    if (eventos == NULL) {

        printf("Nenhum evento encontrado para a sala especificada.\n");

        return;
    }

    //Verifica e lista os eventos para a data espec�fica
    int encontrou = 0;

    link aux;

    for (aux = eventos; aux != NULL; aux = next(aux)) {

        ptrEvento evento = getEvento(aux);

        if (getAno(evento) == ano && getMes(evento) == mes && getDia(evento) == dia) {

            ListarEvento(evento);

            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum evento encontrado para a sala %s na data %i-%i-%i.\n", sala, dia, mes, ano);
    }
}


void listarProximosEventosAPartirData(ptrAgenda agenda) {
    int n;
    int ano, mes, dia;

    // Solicitar a data a partir da qual listar os eventos
    printf("Indique a data a partir da qual deseja listar os pr�ximos eventos (ano mes dia): ");

    scanf("%i %i %i", &ano, &mes, &dia);

    // Solicitar o n�mero de eventos que deseja listar
    printf("Indique o numero de eventos que deseja listar: ");

    scanf("%i", &n);


    ptrEvento* eventosFuturos = coletarEventosFuturos(agenda, ano, mes, dia, n);

    // Listar os pr�ximos n eventos a partir da data especificada
    printf("Proximos %i eventos a partir de %i-%i-%i:\n", n, ano, mes, dia);

    for (int i = 0; i < n; i++) {
        ListarEvento(eventosFuturos[i]);
    }

    free(eventosFuturos);

}

//MAIN__***************************************************************************************
int main(int argc, char* argv[]) {
    FILE* fagenda;
    FILE* feventos;
    int d, m, a;
    int i;
    int nUtl;
    int nEventos;
    int nSalas;

    if (argc != 3) {                                                    // Verificar se o programa � chamado com o n�mero correto de argumento
        printf("Numero de argumentos errados! %i \n", argc);
        exit(0);
    }

    fagenda = fopen(argv[1], "r");                                      // Verificar se os 2 ficheiros s�o abertos corretamente
    if (fagenda == NULL) {
        printf("Ficheiro agenda nao encontrado.\n");
        exit(0);
    }
    feventos = fopen(argv[2], "r");
    if (feventos == NULL) {
        printf("Ficheiro eventos nao encontrado.\n");
        exit(0);
    }

    // **** Processar o ficheiro da agenda ****
    printf("\nConteudo do ficheiro AGENDA\n");

    fscanf(fagenda, "%i %i ", &nEventos, &nSalas);                      // Ler o n�mero de eventos e o n�mero de salas no ficheiro agenda

    printf("Numero de Eventos: %i\n", nEventos);

    printf("Numero de Salas: %i\n", nSalas);

    ptrAgenda Agenda = criarAgenda(nSalas);

    for (i = 0; i < nEventos; i++)                                      // Ler todos os eventos da Agenda
        leLinhaEventosAgenda(fagenda, Agenda);

    // **** Processar o ficheiro da eventos ****
    printf("\n\nConteudo do ficheiro EVENTOS\n");

    fscanf(feventos, "%i ", &nEventos);                                 // Ler o n�mero de eventos no ficheiro eventos
    printf("Numero de Eventos: %i\n", nEventos);

    // Ler todos os eventos
    for (i = 0; i < nEventos; i++)
        leLinhaEventosAgenda(feventos, Agenda);

    int opcao;

    do {
        opcao = menu();
        switch (opcao) {
        case 0:
            escreverEventosOrdenadosNoArquivo(Agenda, "agenda-nova.txt");
            printf("Obrigado por utilizar este programa!");
            break;
        case 1:
            criarEventoPorUsuario(Agenda);
            break;
        case 2:
            listarEventosSala(Agenda);
            break;
        case 3:
            listarEventosSalaDia(Agenda);
            break;
        case 4:
            listarProximosEventos(Agenda);
            break;
        case 5:
            listarProximosEventosAPartirData(Agenda);
            break;
        case 6:
            listarEventosData(Agenda);
            break;
        case 7:
            listarEventosEntreDatas(Agenda);
            break;
        case 8:
            apagarEvento(Agenda);
            break;
        case 9:
            apagarEventosAnteriores(Agenda);
            break;
        case 10://serve s� para testar
            printAgenda(Agenda);
            break;
        default:
            printf("\n\nOpcao errada\n");
        }
    } while (opcao != 0);



    printf("\nEventos foram escritos no arquivo com sucesso.\n");
    fclose(fagenda); //Fecha corretamente o ficheiro agenda
    fclose(feventos);//Fecha corretamente o ficheiro eventos


    free(Agenda); //Libera a memoria da agenda


}

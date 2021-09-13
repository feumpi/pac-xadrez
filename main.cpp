/*#######################################################################
#                                                                       #
#   Universidade Federal do Espírito Santo                              #
#   INF09324 Programação Aplicada de Computadores 2021/1                #
#   Primeiro trabalho                                                   #
#                                                                       #
#   Aluno: 2020205193 Felipe Pereira Umpierre                           #
#   Professor: Rodrigo Martins de Siqueira Barbosa                      #
#   Entrega: 01/09/2021                                                 #
#                                                                       #
#   Como utilizar: USO.pdf ou USO.md                                    #
#   Sobre o desenvolvimento: DESENVOLVIMENTO.pdf ou DESENVOLVIMENTO.md  #
#                                                                       #
#######################################################################*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "interface.h"
#include "jogo.h"
#include "partida.h"

int main(int argc, char *argv[]) {
    std::string nomeArquivo;

    if (argc > 1) {
        nomeArquivo = argv[1];
    } else {
        std::cout << "Informe o nome de um arquivo PGN a ser lido. Ex: jogo01.pgn" << std::endl
                  << "Nome: ";

        std::cin >> nomeArquivo;
        std::cin.ignore();
    }

    //Inicializa a interface, imprime os dados do jogo e o tabuleiro inicial com legenda
    Interface interface;

    //Inicializa a partida com o nome do arquivo a ser lido
    Partida partida(nomeArquivo, &interface);

    interface.imprimirJogo(partida.getJogo());

    int entrada = interface.coletarEntrada();

    if (entrada == ENTRADA_SAIR) {
        interface.~Interface();
        exit(1);
    }

    clear();
    interface.imprimirTabuleiro(partida.getTabuleiro(), true);
    interface.imprimirInformacao("Aguardando o início da partida");

    entrada = interface.coletarEntrada();

    if (entrada == ENTRADA_SAIR) {
        interface.~Interface();
        exit(1);
    }

    while (!partida.getAcabou()) {
        clear();
        partida.proximaJogada();
        interface.imprimirTabuleiro(partida.getTabuleiro());
        interface.imprimirCapturados(partida.getCapturados());

        entrada = interface.coletarEntrada();

        if (entrada == ENTRADA_SAIR) {
            interface.~Interface();
            exit(1);
        }
    }

    interface.imprimirResultado(partida.getJogo().getResultado(), partida.getJogo().getJogadas().size(), partida.getCapturados()[0].size(), partida.getCapturados()[1].size());

    return 0;
}
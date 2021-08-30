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

    //Inicializa a partida com o nome do arquivo a ser lido
    Partida partida(nomeArquivo);

    //Inicializa a interface, imprime os dados do jogo e o tabuleiro inicial
    Interface interface;
    interface.imprimirJogo(partida.getJogo());
    interface.imprimirTabuleiro(partida.getTabuleiro());

    std::cout << "\nENTER: começar" << std::endl;
    std::cin.ignore();

    while (!partida.getAcabou()) {
        partida.proximaJogada();

        interface.imprimirTabuleiro(partida.getTabuleiro());

        std::cout << "\nENTER: próxima jogada" << std::endl;
        std::cin.ignore();
    }

    return 0;
}
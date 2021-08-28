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
    if (argc <= 1) {
        std::cout << "Informe o nome de um arquivo PGN como argumento" << std::endl
                  << "Ex: " << argv[0] << " jogo01.pgn" << std::endl;

        return -1;
    }

    //Inicializa a partida com o nome do arquivo a ser lido
    Partida partida(argv[1]);

    //Obtém o jogo e o tabuleiro do objeto Partida
    Jogo jogo = partida.getJogo();
    std::vector<std::vector<std::string>> tabuleiro = partida.getTabuleiro();

    //Inicializa a interface, imprime os dados do jogo e o tabuleiro inicial
    Interface interface;
    interface.imprimirJogo(jogo);
    interface.imprimirTabuleiro(tabuleiro);

    partida.proximaJogada();
    partida.proximaJogada();

    //tabuleiro = partida.getTabuleiro();
    //interface.imprimirTabuleiro(tabuleiro);

    return 0;
}
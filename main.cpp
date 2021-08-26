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

#include "interface.h"
#include "jogo.h"
#include "partida.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "Informe o nome de um arquivo PGN como argumento" << std::endl
                  << "Ex: " << argv[0] << " jogo01.pgn" << std::endl;

        return 1;
    }

    Partida partida(argv[1]);

    Jogo jogo = partida.getJogo();
    Interface interface;

    interface.imprimirJogo(jogo);

    return 0;
}
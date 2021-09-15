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

    //Inicializa a interface
    Interface interface;

    if (argc > 1) {
        nomeArquivo = argv[1];
    } else {
        nomeArquivo = interface.selecionarArquivo();
    }

    //Inicializa a partida com o nome do arquivo a ser lido
    Partida partida(nomeArquivo, &interface);

    partida.preparar();

    partida.comecar();

    interface.imprimirResultado(partida.getJogo().getResultado(), partida.getJogo().getJogadas().size(), partida.getCapturados()[0].size(), partida.getCapturados()[1].size());

    interface.encerrarPrograma("Fim do jogo");

    return 0;
}
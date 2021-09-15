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

    //Pega o nome do arquivo pelo terminal, se informado, ou do menu de opções
    if (argc > 1) {
        nomeArquivo = argv[1];
    } else {
        nomeArquivo = interface.selecionarArquivo();
    }

    //Inicializa a partida com o nome do arquivo a ser lido
    Partida partida(nomeArquivo, &interface);

    //Prepara e começa o jogo
    partida.preparar();
    partida.comecar();

    return 0;
}
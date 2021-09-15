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

    //Imprime os dados do jogo
    interface.imprimirJogo(partida.getJogo());

    int acao = interface.aguardarAcao(true, false, true);

    //Imprime o tabuleiro inicial com legenda
    interface.imprimirTabuleiro(partida.getTabuleiro(), true);
    interface.imprimirInformacao("Aguardando o inicio da partida");

    while (!partida.getAcabou()) {
        acao = interface.aguardarAcao(true, true, true, true);

        if (acao == ENTRADA_VOLTAR) {
            partida.jogadaAnterior();
            interface.imprimirTabuleiro(partida.getTabuleiro());
            interface.imprimirCapturados(partida.getCapturados());
        }

        else if (acao == ENTRADA_CONTINUAR) {
            partida.proximaJogada();
            interface.imprimirTabuleiro(partida.getTabuleiro());
            interface.imprimirCapturados(partida.getCapturados());
        }
    }

    interface.imprimirResultado(partida.getJogo().getResultado(), partida.getJogo().getJogadas().size(), partida.getCapturados()[0].size(), partida.getCapturados()[1].size());

    interface.encerrarPrograma("Fim do jogo");

    return 0;
}
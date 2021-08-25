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

#include "jogo.h"

std::string extrairValor(std::string linha) {
    int posInicio, posFim;
    std::string valor;

    posInicio = linha.find("\"");
    posInicio++;
    posFim = linha.find("\"]");
    valor = linha.substr(posInicio, posFim - posInicio);
    return valor;
}

int main() {
    std::ifstream arquivo;
    std::string linha, evento, local, data, rodada, branco, preto, resultado;

    arquivo.open("jogo01.pgn");

    if (arquivo.is_open()) {
        getline(arquivo, linha);
        evento = extrairValor(linha);

        getline(arquivo, linha);
        local = extrairValor(linha);

        getline(arquivo, linha);
        data = extrairValor(linha);

        getline(arquivo, linha);
        rodada = extrairValor(linha);

        getline(arquivo, linha);
        branco = extrairValor(linha);

        getline(arquivo, linha);
        preto = extrairValor(linha);

        getline(arquivo, linha);
        resultado = extrairValor(linha);

        Jogo jogo(evento, local, data, rodada, branco, preto, resultado);
        jogo.imprimirDados();

    } else {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
    }

    return 0;
}
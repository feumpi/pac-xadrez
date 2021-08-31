#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <vector>

#define T_LEGENDA "R: torre, N: cavalo, B: bispo, Q: dama, K: rei, P: peão\nMaíscula: Branco, Minúscula: Preto\n\n"
#define T_LINHA_LETRAS "      A       B       C       D       E       F       G       H    \n"
#define T_BORDA_HORIZONTAL "  -----------------------------------------------------------------\n"
#define T_LINHA_VAZIA "  |       |       |       |       |       |       |       |       |\n"

#include "jogo.h"

class Interface {
   public:
    //Exibe uma mensagem de boas-vindas ao inicializar
    Interface();

    //Exibe uma mensagem de encerramento ao fim do programa
    ~Interface();

    //Recebe uma matriz de string representando o tabuleiro e a imprime usando caracteres ASCII
    void imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro, bool legenda = false);

    //Imprime as informações sobre um jogo
    void imprimirJogo(Jogo jogo);
};

#endif
#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <vector>

#include "jogo.h"

class Interface {
   public:
    Interface();

    ~Interface();

    //Imprime uma representação visual do tabuleiro usando caracteres ASCII
    void imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro);

    //Imprime as informações sobre um jogo
    void imprimirJogo(Jogo jogo);

    //Imprime o que acontece numa jogada
    void imprimirJogada(std::string);
};

#endif
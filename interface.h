#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <vector>

#include "jogo.h"

class Interface {
   public:
    //Exibe uma mensagem de boas-vindas ao inicializar
    Interface();

    //Exibe uma mensagem de encerramento ao fim do programa
    ~Interface();

    //Recebe uma matriz de string representando o tabuleiro e a imprime usando caracteres ASCII
    void imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro);

    //Imprime as informações sobre um jogo
    void imprimirJogo(Jogo jogo);
};

#endif
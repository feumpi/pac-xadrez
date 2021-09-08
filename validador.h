#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <cstdlib>
#include <iostream>
#include <vector>

#define BRANCO 0
#define PRETO 1

class Validador {
   public:
    static bool torre(std::vector<int> posInicial, std::vector<int> posFinal);
    static bool cavalo(std::vector<int> posInicial, std::vector<int> posFinal);
    static bool bispo(std::vector<int> posInicial, std::vector<int> posFinal);
    static bool dama(std::vector<int> posInicial, std::vector<int> posFinal);
    static bool rei(std::vector<int> posInicial, std::vector<int> posFinal);
    static bool peao(std::vector<int> posInicial, std::vector<int> posFinal, int jogador, bool primeiraJogada, bool captura = false);
};

#endif
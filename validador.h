#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <cstdlib>
#include <iostream>
#include <vector>

class Validador {
   public:
    static bool torre(std::vector<int> posInicial, std::vector<int> posFinal);
    static bool cavalo(std::vector<int> posInicial, std::vector<int> posFinal);
    static bool bispo(std::vector<int> posInicial, std::vector<int> posFinal);
    static bool dama(std::vector<int> posInicial, std::vector<int> posFinal);
    static bool rei(std::vector<int> posInicial, std::vector<int> posFinal);
    static bool peao(std::vector<int> posInicial, std::vector<int> posFinal, bool primeiraJogada, bool captura = false);
};

#endif
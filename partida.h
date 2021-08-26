#ifndef PARTIDA_H
#define PARTIDA_H

#include <fstream>
#include <string>
#include <vector>

#include "jogo.h"

//Guarda as informações de uma partida, incluindo o objeto Jogo, mas também a jogada atual e o tabuleiro
class Partida {
   public:
    Partida(std::string nomeArquivo);
    Jogo getJogo();

   private:
    Jogo _jogo{};

    std::string _extrairValor(std::string linha);
};

#endif
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
    std::vector<std::vector<std::string>> getTabuleiro();

   private:
    Jogo _jogo{};

    std::string _extrairValor(std::string linha);
    std::string _extrairJogada(std::string* linha);
    std::vector<std::string> _lerJogadas(std::ifstream* arquivo);
    std::vector<std::vector<std::string>> _tabuleiro;
};

#endif
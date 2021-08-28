#ifndef PARTIDA_H
#define PARTIDA_H

#include <fstream>
#include <string>
#include <vector>

#include "jogo.h"

//Guarda as informações de uma partida, incluindo o objeto Jogo, mas também a jogada atual e o tabuleiro
class Partida {
   public:
    //Inicializa o objeto carregando o arquivo informado
    Partida(std::string nomeArquivo);

    //Getters
    Jogo getJogo();
    std::vector<std::vector<std::string>> getTabuleiro();

   private:
    Jogo _jogo{};
    std::vector<std::vector<std::string>> _tabuleiro;

    //Recebe uma string da linha de dados extras do PGN e retorna o apenas o valor que importa
    std::string _extrairValor(std::string linha);

    //Recebe o arquivo PGN aberto (com os dados extras já extraídos) e retorna um vetor de strings com as jogadas em sequência
    std::vector<std::string> _lerJogadas(std::ifstream* arquivo);
};

#endif
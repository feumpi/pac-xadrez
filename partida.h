#ifndef PARTIDA_H
#define PARTIDA_H

#include <cctype>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "jogo.h"
#include "validador.h"

#define BRANCO 0
#define PRETO 1

//Guarda as informações de uma partida, incluindo o objeto Jogo, mas também a jogada atual e o tabuleiro
class Partida {
   public:
    //Inicializa o objeto carregando o arquivo informado
    Partida(std::string nomeArquivo);

    //Getters
    Jogo getJogo();
    std::vector<std::vector<std::string>> getTabuleiro();
    bool getAcabou();

    //Executa a próxima jogada sequencial dos dois jogadores ao tabuleiro
    void proximaJogada();

   private:
    Jogo _jogo{};
    std::vector<std::vector<std::string>> _tabuleiro;

    int _jogadaAtual = -1;
    bool _acabou = false;
    std::map<std::string, std::string> _pecas;

    //Recebe uma string da linha de dados extras do PGN e retorna o apenas o valor que importa
    std::string _extrairValor(std::string linha);

    //Recebe o arquivo PGN aberto (com os dados extras já extraídos) e retorna um vetor de strings com as jogadas em sequência
    std::vector<std::string> _lerJogadas(std::ifstream& arquivo);

    //Aplica uma única jogada ao tabuleiro
    void _aplicarJogada(int jogador, std::string Jogada);

    //Encontra uma peça do tipo adequada e a move para o destino
    void _moverPeca(int jogador, std::string peca, std::string destino);

    //Recebe uma coordenada algébrica e retorna um vetor dos índices correspondentes no tabuleiro
    std::vector<int> _encontrarIndices(std::string coordenada);
};

#endif
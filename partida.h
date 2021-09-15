#ifndef PARTIDA_H
#define PARTIDA_H

#include <cctype>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "interface.h"
#include "jogo.h"
#include "validador.h"

#define BRANCO 0
#define PRETO 1

//Guarda as informações de uma partida, incluindo o objeto Jogo, mas também a jogada atual e o tabuleiro
class Partida {
    typedef std::vector<std::vector<std::string>> Tabuleiro;

    typedef struct {
        Tabuleiro tabuleiro;
        std::vector<std::string> capturadosBranco;
        std::vector<std::string> capturadosPreto;
    } EstadoJogo;

   public:
    //Inicializa o objeto carregando o arquivo informado
    Partida(std::string nomeArquivo, Interface* interface);

    //Getters
    Jogo getJogo();
    Tabuleiro getTabuleiro();
    Tabuleiro getCapturados();
    bool getComecou();
    bool getAcabou();

    //Exibe os dados do jogo e o tabuleiro inicial
    void preparar();

    //Executa a próxima jogada, a anterior, ou sai, de acordo com a entrada do usuário, repetidamente até o fim das jogadas
    void comecar();

    //Volta para o estado inicial e recomeça a partida
    void recomecar();

    //Executa a próxima jogada sequencial dos dois jogadores ao tabuleiro
    void proximaJogada();

    //Desfaz a última jogada, retornando para o estado anterior
    void jogadaAnterior();

   private:
    Jogo _jogo{};
    Interface* _interface;
    Tabuleiro _tabuleiro;
    std::vector<EstadoJogo> _estadosJogo;

    int _jogadaAtual = -1;
    bool _comecou = false;
    bool _acabou = false;
    std::map<std::string, std::string> _pecas;
    std::vector<std::string> _capturadosBranco;
    std::vector<std::string> _capturadosPreto;
    std::vector<std::vector<int>> _posDestaque;

    //Recebe uma string da linha de dados extras do PGN e retorna o apenas o valor que importa
    std::string _extrairValor(std::string linha);

    //Recebe o arquivo PGN aberto (com os dados extras já extraídos) e retorna um vetor de strings com as jogadas em sequência
    std::vector<std::string> _lerJogadas(std::ifstream& arquivo);

    //Aplica uma única jogada ao tabuleiro
    void _aplicarJogada(int jogador, std::string Jogada);

    //Encontra uma peça do tipo adequada e a move para o destino
    void _moverPeca(int jogador, std::string peca, std::string destino, std::string colunaOrigem, bool captura);

    //Executa a jogada especial roque (castling)
    void _moverRoque(int jogador, std::string jogada);

    //Recebe uma coordenada algébrica e retorna um vetor dos índices correspondentes no tabuleiro
    std::vector<int> _encontrarIndices(std::string coordenada);

    //Verifica se o caminho entre a posInicial e posFinal está livre de peças (horizontalmente, a princípio)
    bool _caminhoLivre(std::vector<int> posInicial, std::vector<int> posFinal);
};

#endif
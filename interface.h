#ifndef INTERFACE_H
#define INTERFACE_H

//Importa o curses adequado de acordo com o sistema operacional
#ifdef __linux__
#include <ncurses.h>
#elif _WIN32
#include "PDCurses\curses.h"
#endif

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

//Partes do tabuleiro
#define T_LEGENDA "R: torre, N: cavalo, B: bispo, Q: dama, K: rei, P: peão\nMAIUSCULAS: BRANCAS, minusculas: pretas\n\n"
#define T_LINHA_LETRAS "       [A]     [B]     [C]     [D]     [E]     [F]     [G]     [H]   \n"
#define T_BORDA_HORIZONTAL "    -----------------------------------------------------------------\n"
#define T_LINHA_VAZIA "    |       |       |       |       |       |       |       |       |\n"

//Opções de entrada no menu
#define ENTRADA_SAIR 0
#define ENTRADA_CONTINUAR 1
#define ENTRADA_VOLTAR 2
#define ENTRADA_RECOMECAR 3

//Cores
#define COR_SECUNDARIA 1
#define COR_MENU 2
#define COR_DESTAQUE 3
#define COR_LEGENDA 4
#define COR_TABULEIRO 5
#define COR_PECA_BRANCA 6
#define COR_PECA_BRANCA_DESTAQUE 7
#define COR_PECA_PRETA 8
#define COR_PECA_PRETA_DESTAQUE 9
#define COR_CAPTURA 10
#define COR_XEQUE 11

#include "jogo.h"
class Interface {
   public:
    //Exibe uma mensagem de boas-vindas e inicializa a interface curses
    Interface();

    //Encerra o modo curses e fecha o programa
    ~Interface();

    //Avisa que o programa vai encerrar por algum motivo e aguarda confirmação
    void encerrarPrograma(std::string motivo, bool ignorarConfirmacao = false);

    //Exibe os arquivos PGN disponíveis no diretório e retorna a opção selecionada
    std::string selecionarArquivo();

    //Imprime as informações sobre um jogo
    void imprimirJogo(Jogo jogo);

    //Recebe uma matriz de string representando o tabuleiro e a imprime usando caracteres ASCII
    void imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro, bool legenda = false, std::vector<std::vector<int>> posDestaque = {});

    //Imprime as peças capturadas dos dois jogadores
    void imprimirCapturados(std::vector<std::vector<std::string>> capturados);

    //Imprime na janela padrão
    void imprimir(std::string texto);

    //Imprime na janela de informações
    void imprimirInformacao(std::string texto, int cor = 0);

    //Imprime o resultado e estatísticas do jogo
    void imprimirResultado(std::string resultado, int jogadas, int capturadosBranco, int capturadosPreto);

    //Exibe o menu de opções e aguarda a ação do usuário, retornando a opção solicitada
    int aguardarAcao(bool continuar, bool voltar, bool recomecar, bool sair);

    //Limpa a janela de informações
    void limparInformacoes();

   private:
    WINDOW* _janelaPadrao;
    WINDOW* _janelaInformacoes;
    WINDOW* _janelaOpcoes;
};

#endif
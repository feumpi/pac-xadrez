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

#define T_LEGENDA "R: torre, N: cavalo, B: bispo, Q: dama, K: rei, P: peão\nMAIUSCULAS: BRANCAS, minusculas: pretas\n\n"
#define T_LINHA_LETRAS "       [A]     [B]     [C]     [D]     [E]     [F]     [G]     [H]   \n"
#define T_BORDA_HORIZONTAL "    -----------------------------------------------------------------\n"
#define T_LINHA_VAZIA "    |       |       |       |       |       |       |       |       |\n"

#define ENTRADA_SAIR 0
#define ENTRADA_CONTINUAR 1
#define ENTRADA_VOLTAR 2

#include "jogo.h"
class Interface {
   public:
    //Exibe uma mensagem de boas-vindas e inicializa a interface curses
    Interface();

    //Encerra o modo curses e fecha o programa
    ~Interface();

    //Avisa que o programa vai encerrar por algum motivo e aguarda confirmação
    void encerrarPrograma(std::string motivo);

    //Exibe os arquivos PGN disponíveis no diretório e retorna a opção selecionada
    std::string selecionarArquivo();

    //Imprime as informações sobre um jogo
    void imprimirJogo(Jogo jogo);

    //Recebe uma matriz de string representando o tabuleiro e a imprime usando caracteres ASCII
    void imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro, bool legenda = false);

    //Imprime as peças capturadas dos dois jogadores
    void imprimirCapturados(std::vector<std::vector<std::string>> capturados);

    //Imprime na janela padrão
    void imprimir(std::string texto);

    //Imprime na janela de informações
    void imprimirInformacao(std::string texto);

    //Imprime o resultado e estatísticas do jogo
    void imprimirResultado(std::string resultado, int jogadas, int capturadosBranco, int capturadosPreto);

    //Coleta e retorna uma opção válida da entrada do usuário
    int coletarEntrada();

    //Limpa a janela de informações
    void limparInformacoes();

   private:
    WINDOW* _janelaPadrao;
    WINDOW* _janelaInformacoes;
    WINDOW* _janelaOpcoes;
};

#endif
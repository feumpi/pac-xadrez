#include "interface.h"

Interface::Interface() {
    initscr();
    curs_set(0);
    noecho();

    printw("################################\n");
    printw("#                              #\n");
    printw("#          PAC XADREZ          #\n");
    printw("#                              #\n");
    printw("################################\n");
    printw("Bem-vindo!\n\n");
};

Interface::~Interface() {
    printw("Obrigado por usar o programa!\n");
    endwin();
}

void Interface::imprimirJogo(Jogo jogo) {
    //Obtém e imprime cada um dos dados extras
    printw("Evento: %s\n", jogo.getEvento().c_str());
    printw("Local: %s\n", jogo.getLocal().c_str());
    printw("Data: %s\n", jogo.getData().c_str());
    printw("Rodada: %s\n", jogo.getRodada().c_str());
    printw("Branco: %s\n", jogo.getBranco().c_str());
    printw("Preto: %s\n", jogo.getPreto().c_str());
    printw("Resultado: %s\n", jogo.getResultado().c_str());
}

void Interface::imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro, bool legenda) {
    int numLinha;

    if (legenda) printw(T_LEGENDA);

    printw(T_LINHA_LETRAS);
    printw(T_BORDA_HORIZONTAL);

    //Iteração das linhas
    for (int i = 0; i < tabuleiro.size(); i++) {
        printw(T_LINHA_VAZIA);
        //Imprime o número da linha, de 8 a 1, e a borda esquerda
        numLinha = 8 - i;
        printw("[%d] |", numLinha);

        //Iteração das colunas em cada linha
        for (auto coluna : tabuleiro[i]) {
            //Elemento do quadrado ou espaço vazio, espaçamento e borda direita
            printw("   %s   |", (coluna.length() > 0 ? coluna.c_str() : " "));
        }

        printw("[%d]\n", numLinha);
        printw(T_LINHA_VAZIA);
        printw(T_BORDA_HORIZONTAL);
    }

    printw(T_LINHA_LETRAS);
    printw("\n");
}

void Interface::imprimirCapturados(std::vector<std::vector<std::string>> capturados) {
    std::vector<std::string> branco = capturados[0], preto = capturados[1];

    printw("Capturados Branco: ");
    for (auto peca : branco) {
        printw("%s ", peca.c_str());
    }
    printw("\n");

    printw("Capturados Preto: ");
    for (auto peca : preto) {
        printw("%s ", peca.c_str());
    }
    printw("\n");
}

void Interface::imprimirResultado(std::string resultado, int jogadas, int capturadosBranco, int capturadosPreto) {
    printw("\n\n");
    printw("###############################\n");
    printw("#                             #\n");
    printw("#         FIM DO JOGO         #\n");
    printw("#                             #\n");
    printw("###############################\n\n");
    printw("Resultado: %s\n\n", resultado);
    printw("%d jogadas foram executadas\n", jogadas);
    printw("%d peças brancas foram capturadas\n", capturadosBranco);
    printw("%d peças pretas foram capturadas\n", capturadosPreto);
    printw("\n");
}
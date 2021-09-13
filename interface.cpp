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

    _janelaPadrao = newwin(200, 80, 0, 0);
    _janelaInformacoes = newwin(100, 50, 0, 85);

    overwrite(_janelaPadrao, stdscr);
    overwrite(_janelaInformacoes, stdscr);
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

    wclear(_janelaPadrao);

    if (legenda) wprintw(_janelaPadrao, T_LEGENDA);

    wprintw(_janelaPadrao, T_LINHA_LETRAS);
    wprintw(_janelaPadrao, T_BORDA_HORIZONTAL);

    //Iteração das linhas
    for (int i = 0; i < tabuleiro.size(); i++) {
        wprintw(_janelaPadrao, T_LINHA_VAZIA);
        //Imprime o número da linha, de 8 a 1, e a borda esquerda
        numLinha = 8 - i;
        wprintw(_janelaPadrao, "[%d] |", numLinha);

        //Iteração das colunas em cada linha
        for (auto coluna : tabuleiro[i]) {
            //Elemento do quadrado ou espaço vazio, espaçamento e borda direita
            wprintw(_janelaPadrao, "   %s   |", (coluna.length() > 0 ? coluna.c_str() : " "));
        }

        wprintw(_janelaPadrao, "[%d]\n", numLinha);
        wprintw(_janelaPadrao, T_LINHA_VAZIA);
        wprintw(_janelaPadrao, T_BORDA_HORIZONTAL);
    }

    wprintw(_janelaPadrao, T_LINHA_LETRAS);
    wprintw(_janelaPadrao, "\n");

    overwrite(_janelaPadrao, stdscr);
    refresh();
}

void Interface::imprimirCapturados(std::vector<std::vector<std::string>> capturados) {
    std::vector<std::string> branco = capturados[0], preto = capturados[1];

    wprintw(_janelaPadrao, "Capturados Branco: ");
    for (auto peca : branco) {
        wprintw(_janelaPadrao, "%s ", peca.c_str());
    }
    wprintw(_janelaPadrao, "\n");

    wprintw(_janelaPadrao, "Capturados Preto: ");
    for (auto peca : preto) {
        wprintw(_janelaPadrao, "%s ", peca.c_str());
    }
    wprintw(_janelaPadrao, "\n");
}

void Interface::imprimirInformacao(std::string texto) {
    wprintw(_janelaInformacoes, "%s\n\n", texto.c_str());
    overwrite(_janelaInformacoes, stdscr);
    refresh();
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

int Interface::coletarEntrada() {
    while (1) {
        int entrada = getch();
        if (entrada == '\n') return ENTRADA_CONTINUAR;
        if (entrada == 'q') return ENTRADA_SAIR;
    }
}
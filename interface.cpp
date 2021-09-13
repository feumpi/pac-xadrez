#include "interface.h"

Interface::Interface() {
    initscr();
    curs_set(0);
    noecho();

    _janelaPadrao = newwin(40, 80, 1, 0);
    _janelaInformacoes = newwin(40, 50, 1, 85);
    _janelaOpcoes = newwin(2, 80, 41, 0);

    wprintw(_janelaPadrao, "################################\n");
    wprintw(_janelaPadrao, "#                              #\n");
    wprintw(_janelaPadrao, "#          PAC XADREZ          #\n");
    wprintw(_janelaPadrao, "#                              #\n");
    wprintw(_janelaPadrao, "################################\n");
    wprintw(_janelaPadrao, "Bem-vindo!\n\n");

    overwrite(_janelaPadrao, stdscr);
    overwrite(_janelaInformacoes, stdscr);

    wprintw(_janelaOpcoes, "[ENTER] continuar | [q] sair\n");
    overwrite(_janelaOpcoes, stdscr);
};

Interface::~Interface() {
    printw("Obrigado por usar o programa!\n");
    endwin();
}

void Interface::imprimirJogo(Jogo jogo) {
    //Obtém e imprime cada um dos dados extras
    wprintw(_janelaPadrao, "Evento: %s\n", jogo.getEvento().c_str());
    wprintw(_janelaPadrao, "Local: %s\n", jogo.getLocal().c_str());
    wprintw(_janelaPadrao, "Data: %s\n", jogo.getData().c_str());
    wprintw(_janelaPadrao, "Rodada: %s\n", jogo.getRodada().c_str());
    wprintw(_janelaPadrao, "Branco: %s\n", jogo.getBranco().c_str());
    wprintw(_janelaPadrao, "Preto: %s\n", jogo.getPreto().c_str());
    wprintw(_janelaPadrao, "Resultado: %s\n", jogo.getResultado().c_str());

    overwrite(_janelaPadrao, stdscr);
}

void Interface::imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro, bool legenda) {
    int numLinha;

    wclear(_janelaPadrao);

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

    if (legenda) wprintw(_janelaPadrao, T_LEGENDA);

    overwrite(_janelaPadrao, stdscr);
    overwrite(_janelaOpcoes, stdscr);
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

    overwrite(_janelaPadrao, stdscr);
    refresh();
}

void Interface::imprimirInformacao(std::string texto) {
    wprintw(_janelaInformacoes, "%s\n\n", texto.c_str());
    overwrite(_janelaInformacoes, stdscr);
    refresh();
}

void Interface::imprimirResultado(std::string resultado, int jogadas, int capturadosBranco, int capturadosPreto) {
    wclear(_janelaPadrao);

    wprintw(_janelaPadrao, "\n\n");
    wprintw(_janelaPadrao, "###############################\n");
    wprintw(_janelaPadrao, "#                             #\n");
    wprintw(_janelaPadrao, "#         FIM DO JOGO         #\n");
    wprintw(_janelaPadrao, "#                             #\n");
    wprintw(_janelaPadrao, "###############################\n\n");
    wprintw(_janelaPadrao, "Resultado: %s\n\n", resultado.c_str());
    wprintw(_janelaPadrao, "%d jogadas foram executadas\n", jogadas);
    wprintw(_janelaPadrao, "%d peças brancas foram capturadas\n", capturadosBranco);
    wprintw(_janelaPadrao, "%d peças pretas foram capturadas\n", capturadosPreto);
    wprintw(_janelaPadrao, "\n");

    overwrite(_janelaPadrao, stdscr);

    this->limparInformacoes();
}

int Interface::coletarEntrada() {
    while (1) {
        int entrada = getch();
        if (entrada == '\n') return ENTRADA_CONTINUAR;
        if (entrada == 'q') return ENTRADA_SAIR;
    }
}

void Interface::limparInformacoes() {
    wclear(_janelaInformacoes);
    overwrite(_janelaInformacoes, stdscr);
}
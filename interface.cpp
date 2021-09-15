#include "interface.h"

Interface::Interface() {
    //Inicializa a tela em modo curses, esconde o cursor e a entrada do usuário
    initscr();
    curs_set(0);
    noecho();

    start_color();
    init_pair(COR_SECUNDARIA, COLOR_CYAN, COLOR_BLACK);
    init_pair(COR_MENU, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COR_DESTAQUE, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COR_LEGENDA, COLOR_BLUE, COLOR_BLACK);
    init_pair(COR_PECA_BRANCA, COLOR_GREEN, COLOR_BLACK);
    init_pair(COR_PECA_PRETA, COLOR_MAGENTA, COLOR_BLACK);

    //Inicializa as janelas que serão utilizadas
    _janelaPadrao = newwin(40, 80, 1, 0);
    _janelaInformacoes = newwin(40, 60, 1, 85);
    _janelaOpcoes = newwin(2, 80, 41, 0);

    //Imprime a mensagem de boas vindas na janela padrão e a exibe
    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "################################\n");
    wprintw(_janelaPadrao, "#                              #\n");
    wprintw(_janelaPadrao, "#          PAC XADREZ          #\n");
    wprintw(_janelaPadrao, "#                              #\n");
    wprintw(_janelaPadrao, "################################\n");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Bem-vindo!\n\n");
    overwrite(_janelaPadrao, stdscr);

    overwrite(_janelaInformacoes, stdscr);
};

Interface::~Interface() {
    //Encerra o modo curses para retornar ao terminal
    endwin();
    exit(1);
}

void Interface::encerrarPrograma(std::string motivo, bool limparJanelas, bool ignorarConfirmacao) {
    if (limparJanelas) {
        wclear(_janelaPadrao);
        wclear(_janelaInformacoes);
        overwrite(_janelaPadrao, stdscr);
        overwrite(_janelaInformacoes, stdscr);
    }

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "\n\nEncerrando o programa: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n\n", motivo.c_str());

    if (!ignorarConfirmacao)
        int entrada = this->aguardarAcao(false, false, true);

    this->~Interface();
}

std::string Interface::selecionarArquivo() {
    std::vector<std::string> arquivos;

    for (auto& arquivo : std::filesystem::directory_iterator(std::filesystem::current_path())) {
        std::string nome = arquivo.path().filename().string();
        std::string extensao = arquivo.path().extension().string();
        if (extensao == ".pgn") arquivos.push_back(nome);
    }

    //Encerra o programa se nenhum arquivo for encontrado
    if (!arquivos.size()) {
        this->encerrarPrograma("Nenhum arquivo PGN encontrado. Coloque algum na mesma pasta desde executavel e tente novamente.");
    }

    wprintw(_janelaPadrao, "Escolha um arquivo PGN para comecar:\n\n");
    for (int i = 0; i < arquivos.size(); i++) {
        wattron(_janelaPadrao, COLOR_PAIR(COR_MENU));
        wprintw(_janelaPadrao, "[%d] %s\n", i + 1, arquivos[i].c_str());
        wattroff(_janelaPadrao, COLOR_PAIR(COR_MENU));
    }
    wprintw(_janelaPadrao, "\n");
    overwrite(_janelaPadrao, stdscr);

    while (1) {
        int entrada = wgetch(stdscr);
        int numero = entrada - '0';

        if (numero > 0 && numero <= arquivos.size()) return arquivos[numero - 1];
    }
}

void Interface::imprimirJogo(Jogo jogo) {
    //Obtém e imprime cada um dos dados extras na janela padrão e a exibe

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Evento: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n", jogo.getEvento().c_str());

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Local: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n", jogo.getLocal().c_str());

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Data: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n", jogo.getData().c_str());

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Rodada: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n", jogo.getRodada().c_str());

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Branco: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n", jogo.getBranco().c_str());

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Preto: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n", jogo.getPreto().c_str());

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Resultado: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n", jogo.getResultado().c_str());

    overwrite(_janelaPadrao, stdscr);
}

void Interface::imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro, bool legenda) {
    int numLinha;

    //Limpa a janela padrão
    wclear(_janelaPadrao);

    wattron(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));
    wprintw(_janelaPadrao, T_LINHA_LETRAS);
    wattroff(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));

    wprintw(_janelaPadrao, T_BORDA_HORIZONTAL);

    //Iteração das linhas
    for (int i = 0; i < tabuleiro.size(); i++) {
        wprintw(_janelaPadrao, T_LINHA_VAZIA);
        //Imprime o número da linha, de 8 a 1, e a borda esquerda
        numLinha = 8 - i;

        wattron(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));
        wprintw(_janelaPadrao, "[%d]", numLinha);
        wattroff(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));
        wprintw(_janelaPadrao, " |", numLinha);

        //Iteração das colunas em cada linha
        for (auto coluna : tabuleiro[i]) {
            //Elemento do quadrado ou espaço vazio, espaçamento e borda direita
            std::string conteudo = coluna.length() > 0 ? coluna.c_str() : " ";
            bool branco = std::isupper(conteudo[0]);

            wattron(_janelaPadrao, COLOR_PAIR(branco ? COR_PECA_BRANCA : COR_PECA_PRETA));
            wprintw(_janelaPadrao, "   %s   ", (coluna.length() > 0 ? coluna.c_str() : " "));
            wattroff(_janelaPadrao, COLOR_PAIR(branco ? COR_PECA_BRANCA : COR_PECA_PRETA));
            wprintw(_janelaPadrao, "|");
        }

        wattron(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));
        wprintw(_janelaPadrao, " [%d]\n", numLinha);
        wattroff(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));

        wprintw(_janelaPadrao, T_LINHA_VAZIA);
        wprintw(_janelaPadrao, T_BORDA_HORIZONTAL);
    }

    wattron(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));
    wprintw(_janelaPadrao, T_LINHA_LETRAS);
    wattroff(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));

    wprintw(_janelaPadrao, "\n");

    //Imprime a legenda das peças, se solicitado
    if (legenda) wprintw(_janelaPadrao, T_LEGENDA);

    //Atualiza e reexibe a janela padrão e a janela opções
    overwrite(_janelaPadrao, stdscr);
}

void Interface::imprimirCapturados(std::vector<std::vector<std::string>> capturados) {
    std::vector<std::string> branco = capturados[0], preto = capturados[1];

    wprintw(_janelaPadrao, "Pecas brancas capturadas: ");
    for (auto peca : branco) {
        wprintw(_janelaPadrao, "%s ", peca.c_str());
    }
    wprintw(_janelaPadrao, "\n");

    wprintw(_janelaPadrao, "Pecas pretas capturadas: ");
    for (auto peca : preto) {
        wprintw(_janelaPadrao, "%s ", peca.c_str());
    }
    wprintw(_janelaPadrao, "\n");

    overwrite(_janelaPadrao, stdscr);
    refresh();
}

void Interface::imprimir(std::string texto) {
    wprintw(_janelaPadrao, "%s\n\n", texto.c_str());
    overwrite(_janelaPadrao, stdscr);
}

void Interface::imprimirInformacao(std::string texto) {
    wprintw(_janelaInformacoes, "%s\n\n", texto.c_str());
    overwrite(_janelaInformacoes, stdscr);
}

void Interface::imprimirResultado(std::string resultado, int jogadas, int capturadosBranco, int capturadosPreto) {
    wclear(_janelaPadrao);

    wprintw(_janelaPadrao, "\n\n");
    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "###############################\n");
    wprintw(_janelaPadrao, "#                             #\n");
    wprintw(_janelaPadrao, "#         FIM DO JOGO         #\n");
    wprintw(_janelaPadrao, "#                             #\n");
    wprintw(_janelaPadrao, "###############################\n\n");

    wprintw(_janelaPadrao, "Resultado: ", resultado.c_str());
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n\n", resultado.c_str());

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%d ", jogadas);
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "jogadas foram executadas\n");

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%d ", capturadosBranco);
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "peças brancas foram capturadas\n");

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%d ", capturadosPreto);
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "peças pretas foram capturadas\n");

    wprintw(_janelaPadrao, "\n");

    overwrite(_janelaPadrao, stdscr);

    this->limparInformacoes();
}

int Interface::aguardarAcao(bool continuar, bool voltar, bool sair, bool partidaIniciada) {
    //Limpa a janela de opções
    wclear(_janelaOpcoes);

    //Imprime e exibe as opções
    wattron(_janelaOpcoes, COLOR_PAIR(COR_MENU));

    if (continuar) wprintw(_janelaOpcoes, " [ENTER] continuar ");
    if (voltar) wprintw(_janelaOpcoes, " [v] voltar ");
    if (sair) wprintw(_janelaOpcoes, " [q] sair ");
    wprintw(_janelaOpcoes, "\n");

    wattroff(_janelaOpcoes, COLOR_PAIR(COR_MENU));
    overwrite(_janelaOpcoes, stdscr);

    //Coleta a entrada
    while (1) {
        int entrada = getch();

        if (entrada == '\n' && continuar) {
            wclear(_janelaOpcoes);
            overwrite(_janelaOpcoes, stdscr);
            return ENTRADA_CONTINUAR;
        } else if (entrada == 'v' && voltar) {
            wclear(_janelaOpcoes);
            overwrite(_janelaOpcoes, stdscr);
            return ENTRADA_VOLTAR;
        } else if (entrada == 'q' && sair) {
            wclear(_janelaOpcoes);
            overwrite(_janelaOpcoes, stdscr);
            //Encerra o programa, limpando as janelas se a partida tiver sido iniciada
            this->encerrarPrograma("Solicitado pelo usuário.", partidaIniciada, true);
        }
    }
}

void Interface::limparInformacoes() {
    wclear(_janelaInformacoes);
    overwrite(_janelaInformacoes, stdscr);
}
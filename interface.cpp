#include "interface.h"

Interface::Interface() {
    //Inicializa a tela em modo curses, esconde o cursor e a entrada do usuário
    initscr();
    curs_set(0);
    noecho();

    //Inicializa as janelas que serão utilizadas
    _janelaPadrao = newwin(40, 80, 1, 0);
    _janelaInformacoes = newwin(40, 60, 1, 85);
    _janelaOpcoes = newwin(2, 80, 41, 0);

    //Imprime a mensagem de boas vindas na janela padrão e a exibe
    wprintw(_janelaPadrao, "################################\n");
    wprintw(_janelaPadrao, "#                              #\n");
    wprintw(_janelaPadrao, "#          PAC XADREZ          #\n");
    wprintw(_janelaPadrao, "#                              #\n");
    wprintw(_janelaPadrao, "################################\n");
    wprintw(_janelaPadrao, "Bem-vindo!\n\n");
    overwrite(_janelaPadrao, stdscr);

    wprintw(_janelaOpcoes, "[ENTER] continuar | [v] voltar | [q] sair\n");

    overwrite(_janelaInformacoes, stdscr);
};

Interface::~Interface() {
    //Encerra o modo curses para retornar ao terminal
    endwin();
    exit(1);
}

void Interface::encerrarPrograma(std::string motivo) {
    wprintw(_janelaPadrao, "Encerrando o programa: %s\n\n", motivo.c_str());
    wprintw(_janelaPadrao, "Pressione [ENTER] ou [q] para sair e retornar ao terminal.\n");
    overwrite(_janelaPadrao, stdscr);

    //Aguarda a confirmação do usuário antes de encerrar
    while (1) {
        int entrada = getch();
        if (entrada == '\n' || entrada == 'q') break;
    }

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
        wprintw(_janelaPadrao, "%d) %s\n", i + 1, arquivos[i].c_str());
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

    //Limpa a janela padrão
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

        wprintw(_janelaPadrao, " [%d]\n", numLinha);
        wprintw(_janelaPadrao, T_LINHA_VAZIA);
        wprintw(_janelaPadrao, T_BORDA_HORIZONTAL);
    }

    wprintw(_janelaPadrao, T_LINHA_LETRAS);
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
    //Exibe a janela opções
    overwrite(_janelaOpcoes, stdscr);

    //Coleta a entrada
    while (1) {
        int entrada = getch();
        if (entrada == '\n') return ENTRADA_CONTINUAR;
        if (entrada == 'v') return ENTRADA_VOLTAR;
        if (entrada == 'q') return ENTRADA_SAIR;
    }
}

void Interface::limparInformacoes() {
    wclear(_janelaInformacoes);
    overwrite(_janelaInformacoes, stdscr);
}
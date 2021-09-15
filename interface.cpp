#include "interface.h"

Interface::Interface() {
    //Inicializa a tela em modo curses, esconde o cursor e a entrada do usuário
    initscr();
    curs_set(0);
    noecho();

    //Inicializa as cores
    start_color();
    init_pair(COR_SECUNDARIA, COLOR_CYAN, COLOR_BLACK);
    init_pair(COR_MENU, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COR_DESTAQUE, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COR_LEGENDA, COLOR_BLUE, COLOR_BLACK);
    init_pair(COR_PECA_BRANCA, COLOR_GREEN, COLOR_BLACK);
    init_pair(COR_PECA_BRANCA_DESTAQUE, COLOR_GREEN, COLOR_WHITE);
    init_pair(COR_PECA_PRETA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COR_PECA_PRETA_DESTAQUE, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(COR_CAPTURA, COLOR_RED, COLOR_BLACK);
    init_pair(COR_XEQUE, COLOR_CYAN, COLOR_BLACK);

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

void Interface::encerrarPrograma(std::string motivo, bool ignorarConfirmacao) {
    //Exibe o motivo do encerramento informado
    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "\n\nEncerrando o programa: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n\n", motivo.c_str());
    overwrite(_janelaPadrao, stdscr);

    //Exibe o menu somente com a opção sair e aguarda confirmação
    if (!ignorarConfirmacao)
        int entrada = this->aguardarAcao(false, false, false, true);

    this->~Interface();
}

std::string Interface::selecionarArquivo() {
    std::vector<std::string> arquivos;

    //Itera os arquivos do diretório atual e guarda no vetor os que tem a extensão ".pgn"
    for (auto& arquivo : std::filesystem::directory_iterator(std::filesystem::current_path())) {
        std::string nome = arquivo.path().filename().string();
        std::string extensao = arquivo.path().extension().string();
        if (extensao == ".pgn") arquivos.push_back(nome);
    }

    //Encerra o programa se nenhum arquivo for encontrado
    if (!arquivos.size()) {
        this->encerrarPrograma("Nenhum arquivo PGN encontrado. Coloque algum na mesma pasta deste executavel e tente novamente.");
    }

    //Exibe os arquivos encontrados e os números correspondentes
    wprintw(_janelaPadrao, "Escolha um arquivo PGN para comecar:\n\n");
    wattron(_janelaPadrao, COLOR_PAIR(COR_MENU));
    for (int i = 0; i < arquivos.size(); i++) {
        wprintw(_janelaPadrao, "[%d] %s\n", i + 1, arquivos[i].c_str());
    }
    wprintw(_janelaPadrao, "\n[q] sair\n\n");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_MENU));
    overwrite(_janelaPadrao, stdscr);

    //Coleta a entrada do número da opção, ou q para sair
    while (1) {
        int entrada = wgetch(stdscr);

        if (entrada == 'q' || entrada == 'Q') this->encerrarPrograma("", true);

        //Converte o número em char para um número inteiro
        int numero = entrada - '0';

        //Retorna o nome de arquivo no índice correspondente
        if (numero > 0 && numero <= arquivos.size()) return arquivos[numero - 1];
    }
}

void Interface::imprimirJogo(Jogo jogo) {
    //Exibe cada um dos itens usando cor para o nome do item e branco para o conteúdo
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

    //Nesse caso e no proximo, adiciona o elo ao lado do nome dos jogadores, se ele existir
    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Branco: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    std::string elo = jogo.getEloBranco();
    wprintw(_janelaPadrao, "%s %s\n", jogo.getBranco().c_str(), elo.length() > 0 ? std::string("(elo " + elo + ")").c_str() : "");

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Preto: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    elo = jogo.getEloPreto();
    wprintw(_janelaPadrao, "%s %s\n", jogo.getPreto().c_str(), elo.length() > 0 ? std::string("(elo " + elo + ")").c_str() : "");

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "Resultado: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n", jogo.getResultado().c_str());

    wattron(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "ECO: ");
    wattroff(_janelaPadrao, COLOR_PAIR(COR_SECUNDARIA));
    wprintw(_janelaPadrao, "%s\n", jogo.getEco().c_str());

    overwrite(_janelaPadrao, stdscr);
}

void Interface::imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro, bool legenda, std::vector<std::vector<int>> posDestaque) {
    int numLinha;

    //Limpa a janela padrão
    wclear(_janelaPadrao);

    //Coordenadas e borda superior
    wattron(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));
    wprintw(_janelaPadrao, T_LINHA_LETRAS);
    wattroff(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));
    wprintw(_janelaPadrao, T_BORDA_HORIZONTAL);

    //Iteração das linhas
    for (int i = 0; i < tabuleiro.size(); i++) {
        //Linha vazia com delimitadores verticais
        wprintw(_janelaPadrao, T_LINHA_VAZIA);

        //Número da linha, de 8 a 1, e a borda esquerda
        numLinha = 8 - i;
        wattron(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));
        wprintw(_janelaPadrao, "[%d]", numLinha);
        wattroff(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));
        wprintw(_janelaPadrao, " |", numLinha);

        //Iteração das colunas em cada linha
        for (int j = 0; j < tabuleiro[i].size(); j++) {
            //Elemento do quadrado ou espaço vazio
            std::string conteudo = tabuleiro[i][j].length() > 0 ? tabuleiro[i][j].c_str() : " ";

            //Determina se é o branco (letra maiúscula)
            bool branco = std::isupper(conteudo[0]);

            //Determina a cor (de impressão) da peça (branco/preto e se está na posição de destaque)
            int cor;
            if (branco) {
                if (posDestaque.size() >= 1 && posDestaque[0][0] == i && posDestaque[0][1] == j)
                    cor = COR_PECA_BRANCA_DESTAQUE;
                else
                    cor = COR_PECA_BRANCA;
            } else {
                if (posDestaque.size() >= 2 && posDestaque[1][0] == i && posDestaque[1][1] == j)
                    cor = COR_PECA_PRETA_DESTAQUE;
                else
                    cor = COR_PECA_PRETA;
            }

            //Espaçamento, conteúdo (peça ou vazio) e borda direita, nas cores apropriadas
            wprintw(_janelaPadrao, "  ");
            wattron(_janelaPadrao, COLOR_PAIR(cor));
            wprintw(_janelaPadrao, " %s ", conteudo.c_str());
            wattroff(_janelaPadrao, COLOR_PAIR(cor));
            wprintw(_janelaPadrao, "  ");
            wprintw(_janelaPadrao, "|");
        }

        //Número da linha à direita
        wattron(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));
        wprintw(_janelaPadrao, " [%d]\n", numLinha);
        wattroff(_janelaPadrao, COLOR_PAIR(COR_LEGENDA));

        //Linha vazia e borda horizontal
        wprintw(_janelaPadrao, T_LINHA_VAZIA);
        wprintw(_janelaPadrao, T_BORDA_HORIZONTAL);
    }

    //Coordenadas inferiores
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

    //Capturados do branco, com cores apropriadas
    wprintw(_janelaPadrao, "Pecas brancas capturadas: ");
    wattron(_janelaPadrao, COLOR_PAIR(COR_PECA_BRANCA));
    for (auto peca : branco) {
        wprintw(_janelaPadrao, "%s ", peca.c_str());
    }
    wattroff(_janelaPadrao, COLOR_PAIR(COR_PECA_BRANCA));
    wprintw(_janelaPadrao, "\n");

    //Capturados do preto, com cores apropriadas
    wprintw(_janelaPadrao, "Pecas pretas capturadas: ");
    wattron(_janelaPadrao, COLOR_PAIR(COR_PECA_PRETA));
    for (auto peca : preto) {
        wprintw(_janelaPadrao, "%s ", peca.c_str());
    }
    wattroff(_janelaPadrao, COLOR_PAIR(COR_PECA_PRETA));
    wprintw(_janelaPadrao, "\n");

    overwrite(_janelaPadrao, stdscr);
    refresh();
}

void Interface::imprimir(std::string texto) {
    wprintw(_janelaPadrao, "%s\n\n", texto.c_str());
    overwrite(_janelaPadrao, stdscr);
}

void Interface::imprimirInformacao(std::string texto, int cor) {
    //Ativa e desativa a cor para imprimir, se informada (> 0)
    if (cor > 0) wattron(_janelaInformacoes, COLOR_PAIR(cor));
    wprintw(_janelaInformacoes, "%s\n\n", texto.c_str());
    if (cor > 0) wattroff(_janelaInformacoes, COLOR_PAIR(cor));
    overwrite(_janelaInformacoes, stdscr);
}

void Interface::imprimirResultado(std::string resultado, int jogadas, int capturadosBranco, int capturadosPreto) {
    //Limpa a janela padrão e a de informações
    wclear(_janelaPadrao);
    this->limparInformacoes();

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
}

int Interface::aguardarAcao(bool continuar, bool voltar, bool recomecar, bool sair) {
    //Limpa a janela de opções
    wclear(_janelaOpcoes);

    //Imprime e exibe as novas opções
    wattron(_janelaOpcoes, COLOR_PAIR(COR_MENU));
    if (continuar) wprintw(_janelaOpcoes, " [ENTER] continuar ");
    if (voltar) wprintw(_janelaOpcoes, " [v] voltar ");
    if (recomecar) wprintw(_janelaOpcoes, " [r] recomecar ");
    if (sair) wprintw(_janelaOpcoes, " [q] sair ");
    wprintw(_janelaOpcoes, "\n");
    wattroff(_janelaOpcoes, COLOR_PAIR(COR_MENU));
    overwrite(_janelaOpcoes, stdscr);

    //Coleta a entrada e retorna o inteiro correspondente, se ela for válida
    //No caso sair, encerra o programa diretamente
    while (1) {
        int entrada = getch();

        //Se for uma letra maiúscula, converte para minúscula
        if (std::isupper(entrada)) entrada = std::tolower(entrada);

        //Continuar
        if (entrada == '\n' && continuar) {
            wclear(_janelaOpcoes);
            overwrite(_janelaOpcoes, stdscr);
            return ENTRADA_CONTINUAR;
        }

        //Voltar
        else if (entrada == 'v' && voltar) {
            wclear(_janelaOpcoes);
            overwrite(_janelaOpcoes, stdscr);
            return ENTRADA_VOLTAR;
        }

        //Recomeçar
        else if (entrada == 'r' && recomecar) {
            wclear(_janelaOpcoes);
            overwrite(_janelaOpcoes, stdscr);
            return ENTRADA_RECOMECAR;
        }

        //Sair
        else if (entrada == 'q' && sair) {
            wclear(_janelaOpcoes);
            overwrite(_janelaOpcoes, stdscr);
            //Encerra o programa, ignorando a confirmação
            this->encerrarPrograma("Solicitado pelo usuário.", true);
        }
    }
}

void Interface::limparInformacoes() {
    wclear(_janelaInformacoes);
    overwrite(_janelaInformacoes, stdscr);
}
#include "partida.h"

#include <iostream>

Partida::Partida(std::string nomeArquivo, Interface* interface) {
    std::ifstream arquivo;
    std::string linha, evento, local, data, rodada, branco, preto, resultado, eloBranco, eloPreto, eco;
    std::vector<std::string> jogadas;

    _interface = interface;

    _interface->imprimir("Lendo arquivo " + nomeArquivo);

    arquivo.open(nomeArquivo);

    //Se o arquivo foi aberto corretamente
    if (arquivo.is_open()) {
        //Extrai os dados extras do jogo, em sequência
        getline(arquivo, linha);
        evento = _extrairValor(linha);
        getline(arquivo, linha);
        local = _extrairValor(linha);
        getline(arquivo, linha);
        data = _extrairValor(linha);
        getline(arquivo, linha);
        rodada = _extrairValor(linha);
        getline(arquivo, linha);
        branco = _extrairValor(linha);
        getline(arquivo, linha);
        preto = _extrairValor(linha);
        getline(arquivo, linha);
        resultado = _extrairValor(linha);
        getline(arquivo, linha);
        eloBranco = _extrairValor(linha);
        getline(arquivo, linha);
        eloPreto = _extrairValor(linha);
        getline(arquivo, linha);
        eco = _extrairValor(linha);

        //Extrai as jogadas das linhas restantes do arquivo
        jogadas = _lerJogadas(arquivo);

        //Cria o objeto jogo com os dados que foram lidos
        _jogo = Jogo(evento, local, data, rodada, branco, preto, resultado, eloBranco, eloPreto, eco, jogadas);

        //Redimensiona o vetor para guardar um estado de jogo para cada jogada + 1, sendo o primeiro o inicial
        _estadosJogo.resize(_jogo.getJogadas().size() + 1);

        //Inicializa o tabuleiro com as posições iniciais das peças
        _tabuleiro = {
            //Linha 1
            {
                "r",  //torre preta (Rook)
                "n",  //cavalo preto (kNight)
                "b",  //bispo preto (Bishop)
                "q",  //dama preta (Queen)
                "k",  //rei preto (King)
                "b",  //bispo preto (Bishop)
                "n",  //cavalo preto (kNight)
                "r",  //torre preta (Rook)
            },
            //Linha 2
            {
                //peões pretos
                "p",
                "p",
                "p",
                "p",
                "p",
                "p",
                "p",
                "p",
            },
            {
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
            },
            {
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
            },
            {
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
            },
            {
                "",
                "",
                "",
                "",
                "",
                "",
                "",
                "",
            },
            //Linha 7
            {
                //peões brancos
                "P",
                "P",
                "P",
                "P",
                "P",
                "P",
                "P",
                "P",
            },
            //Linha 8
            {
                "R",  //torre branca (Rook)
                "N",  //cavalo branco (kNight)
                "B",  //bispo branco (Bishop)
                "Q",  //dama branca (Queen)
                "K",  //rei branco (King)
                "B",  //bispo branco (Bishop)
                "N",  //cavalo branco (kNight)
                "R",  //torre branca (Rook)
            }};

        //Inicializa o map com os nomes das peças
        _pecas = {{"R", "torre"}, {"N", "cavalo"}, {"B", "bispo"}, {"Q", "dama"}, {"K", "rei"}, {"P", "peao"}};

        //Sinaliza o sucesso ao ler o arquivo
        _interface->imprimir(nomeArquivo + " carregado com sucesso!");

    }
    //Encerra o programa se o arquivo não puder ser lido
    else {
        _interface->encerrarPrograma("Nao foi possivel abrir o arquivo " + nomeArquivo);
    }
}

Jogo Partida::getJogo() {
    return _jogo;
}
Partida::Tabuleiro Partida::getTabuleiro() {
    return _tabuleiro;
}
Partida::Tabuleiro Partida::getCapturados() {
    return {_capturadosBranco, _capturadosPreto};
}
bool Partida::getComecou() {
    return _comecou;
}
bool Partida::getAcabou() {
    return _acabou;
}

std::string Partida::_extrairValor(std::string linha) {
    int posInicio, posFim;
    std::string valor;

    //Encontra a posição logo após as primeiras aspas duplas (começo do valor)
    posInicio = linha.find("\"");
    posInicio++;

    //Encontra a posição das aspas duplas seguidas de colchete (fim do valor)
    posFim = linha.find("\"]");

    //Retorna a substring entre o começo e o fim (valor desejado)
    valor = linha.substr(posInicio, posFim - posInicio);
    return valor;
}

std::vector<std::string> Partida::_lerJogadas(std::ifstream& arquivo) {
    std::string linha, jogada;
    std::vector<std::string> jogadas;
    int posInicio, posMeio, posFim;

    //Itera as linhas restantes do arquivo
    while (getline(arquivo, linha)) {
        //Extrai a próxima jogada da linha atual, enquanto ela existir
        while (linha.length() > 0) {
            posInicio = linha.find(".");

            //Pula para a próxima linha se não for uma linha de jogadas (. não encontrado)
            if (posInicio < 0) break;

            //Torna posInicio a posição seguinte ao ponto
            ++posInicio;

            //Remove o começo da linha antes do . (antes da jogada)
            linha = linha.substr(posInicio);

            //Encontra a posição do primeiro espaço (no meio da jogada), interrompe se não encontrado
            posMeio = linha.find(" ");
            if (posMeio < 0) break;

            //Encontra a posição do segundo espaço (ao final da jogada)
            posFim = linha.find(" ", posMeio + 1);

            //Se o espaço não foi encontrado (posFim < 0), usa o último char a linha
            //Provavelmente por causa dos caracteres de quebra de linha direntes (CRLF/LF), o Windows e Linux se comportam diferente nesse caso
            //No windows, linha.length() - 1 deixa pra fora o último char da jogada. (\n = CRLF)
            //No linux, o anterior funciona perfeitamente enquanto apenas linha.length() resulta na leitura incorreta (\n = LF e CR como char extra)
            //Para resolver o problema nas duas plataformas, foi usada a verificação com macros de plataforma
#ifdef __linux__
            if (posFim < 0) posFim = linha.length() - 1;
#elif _WIN32
            if (posFim < 0) posFim = linha.length();
#endif

            //Extrai a jogada (entre o começo da linha e a posição final encontrada) e adiciona ela ao vetor
            jogada = linha.substr(0, posFim);
            jogadas.push_back(jogada);

            //Remove o pedaço da linha até a posição final anterior para continuar na próxima iteração
            linha = linha.substr(posFim);
        }
    }

    return jogadas;
}

void Partida::preparar() {
    //Imprime os dados do jogo
    _interface->imprimirJogo(_jogo);

    //Aguarda a confirmação para continuar, exibindo o menu com continuar e sair
    _interface->aguardarAcao(true, false, false, true);

    //Imprime o tabuleiro inicial com legenda e "aguardando início" na janela de informações
    _interface->imprimirTabuleiro(_tabuleiro, true);
    _interface->imprimirInformacao("Aguardando o inicio da partida");
}

void Partida::comecar() {
    _comecou = true;

    //Enquanto houverem jogadas restantes
    while (!_acabou) {
        //Exibe o menu de opções, mostrando continuar e sair; "voltar" somente se não for a primeira jogada
        int acao = _interface->aguardarAcao(true, _jogadaAtual > 0, false, true);

        //Volta uma jogada e reimprime o tabuleiro e as capturas
        if (acao == ENTRADA_VOLTAR) {
            this->jogadaAnterior();
            _interface->imprimirTabuleiro(_tabuleiro, false, _posDestaque);
            _interface->imprimirCapturados(this->getCapturados());
        }

        //Avança uma jogada e reimprime o tabuleiro e as capturas
        else if (acao == ENTRADA_CONTINUAR) {
            this->proximaJogada();
            _interface->imprimirTabuleiro(_tabuleiro, false, _posDestaque);
            _interface->imprimirCapturados(this->getCapturados());
        }
    }

    //Informa que as jogadas acabaram e aguarda confirmação (continuar ou sair)
    _interface->imprimirInformacao("Fim das jogadas! Avance para ver o resultado.");
    _interface->aguardarAcao(true, false, false, true);

    //Imprime o resultado do jogo
    _interface->imprimirResultado(_jogo.getResultado(), _jogo.getJogadas().size(), _capturadosBranco.size(), _capturadosPreto.size());

    //Aguarda a entrada para recomeçar a partida ou sair do programa
    int acao = _interface->aguardarAcao(false, false, true, true);
    if (acao == ENTRADA_RECOMECAR) this->recomecar();
}

void Partida::recomecar() {
    //Recupera o estado de jogo inicial (índice 0) e atualiza o tabuleiro
    EstadoJogo estadoInicial = _estadosJogo[0];
    _tabuleiro = estadoInicial.tabuleiro;

    _interface->imprimir("Recomeçando o jogo!");

    //Limpa os vetores de captura e estados de jogo, redimensionando novamente para o número de jogadas +1
    _capturadosBranco.clear();
    _capturadosPreto.clear();
    _estadosJogo.clear();
    _estadosJogo.resize(_jogo.getJogadas().size() + 1);

    //Reseta propriedades para valores iniciais
    _jogadaAtual = -1;
    _acabou = false;
    _comecou = false;

    //Prepara e começa o jogo novamente
    this->preparar();
    this->comecar();
}

void Partida::proximaJogada() {
    //Limpa as informações anteriores da janela
    _interface->limparInformacoes();

    //Salva o estado de jogo atual (tabuleiro e capturas)
    EstadoJogo estadoAtual;
    estadoAtual.tabuleiro = _tabuleiro;
    estadoAtual.capturadosBranco = _capturadosBranco;
    estadoAtual.capturadosPreto = _capturadosPreto;
    _estadosJogo[_jogadaAtual + 1] = estadoAtual;

    //Incrementa a jogada
    ++_jogadaAtual;

    //Se a jogada não existir, sinaliza que acabou e retorna
    if (_jogadaAtual >= _jogo.getJogadas().size()) {
        _acabou = true;
        return;
    }

    //Limpa as posições de destaque (peças movidas na jogada atual)
    _posDestaque.clear();

    //Obtém a string de NAP da próxima jogada
    std::string jogada = _jogo.getJogada(_jogadaAtual);
    _interface->imprimirInformacao("Jogada #" + std::to_string(_jogadaAtual + 1));

    //Separa as jogadas em branco e preto e aplica cada uma
    int posMeio = jogada.find(" ");
    std::string jogadaBranco = jogada.substr(0, posMeio);
    _aplicarJogada(BRANCO, jogadaBranco);
    try {
        std::string jogadaPreto = jogada.substr(posMeio + 1);
        _aplicarJogada(PRETO, jogadaPreto);
    } catch (std::out_of_range) {
        _interface->imprimirInformacao("Nao houve jogada do preto.");
    }
}

void Partida::jogadaAnterior() {
    //Se estiver primeira jogada ou antes, encerra
    if (_jogadaAtual <= 0) {
        _interface->imprimirInformacao("Nao e possivel voltar para antes da primeira jogada.");
        return;
    }

    //Decrementa a jogada em 2
    _jogadaAtual -= 2;

    //Restaura o estado de jogo de 2 jogadas atrás (_jogadaAtual + 1 pois o tabuleiro 0 é a jogada -1)
    EstadoJogo estadoRestaurado = _estadosJogo[_jogadaAtual + 1];
    _tabuleiro = estadoRestaurado.tabuleiro;
    _capturadosBranco = estadoRestaurado.capturadosBranco;
    _capturadosPreto = estadoRestaurado.capturadosPreto;

    //Reaplica a jogada anterior para imprimir as informações novamente
    this->proximaJogada();
}

void Partida::_aplicarJogada(int jogador, std::string jogada) {
    std::string peca, destino, colunaOrigem = "";
    int posInicio;

    //Exibe a jogada do jogador atual em NAP, na cor dele
    _interface->imprimirInformacao((jogador == BRANCO ? "BRANCO: " : "PRETO: ") + jogada, jogador == BRANCO ? COR_PECA_BRANCA : COR_PECA_PRETA);

    //Extrai a letra da peça da jogada no índice 0
    peca = jogada.substr(0, 1);

    //Caso especial roque
    if (peca == "O") {
        _moverRoque(jogador, jogada);
        return;
    }

    //Se for uma letra convencional, a coordenada começa no índice 1
    if (peca == "R" || peca == "N" || peca == "B" || peca == "Q" || peca == "K")
        posInicio = 1;

    //Se não, começa no índice 0 e a peça é um "P" (peão, omitido no PGN)
    //TODO: verificar o caso do roque (O-O ou O-O-O)
    else {
        peca = "P";
        posInicio = 0;
    }

    //Verifica se houve captura procurando por "x" na jogada
    bool captura = jogada.find("x") != -1;
    //Se houve, a posição da coordenada aumenta em 1
    if (captura) ++posInicio;

    //Caso de ambiguidade (coluna de origem informada na jogada)
    //Se o char na posição seguinte a de posInicio não for numérico, atribui a coluna de origem e incrementa posInicio
    //Se houver captura, a coluna origem está em posInicio - 1
    if (!std::isdigit(jogada[posInicio + 1])) {
        colunaOrigem = captura ? jogada[posInicio - 1] : jogada[posInicio];
        ++posInicio;
    }

    //Extrai a coordenada algébrica do destino da peça
    destino = jogada.substr(posInicio, 2);

    //Move um tipo de peça de um jogador específico para o destino encontrado
    _moverPeca(jogador, peca, destino, colunaOrigem, captura);

    //Verifica e imprime se houve xeque
    if (jogada.find("+") != -1) {
        _interface->imprimirInformacao("Rei " + std::string(jogador == BRANCO ? "preto" : "branco") + " esta em xeque!", COR_XEQUE);
    }
}

void Partida::_moverRoque(int jogador, std::string jogada) {
    std::vector<int> posRei, posTorre;

    //Posição inicial do rei
    jogador == BRANCO ? posRei = {7, 4} : posRei = {0, 4};

    //Para a esquerda (queenside)
    if (jogada.find("O-O-O") != -1) {
        //Posição inicial da torre
        jogador == BRANCO ? posTorre = {7, 0} : posTorre = {0, 0};

        //Move o rei 2 casas para a esquerda
        _tabuleiro[posRei[0]][posRei[1]] = "";
        _tabuleiro[posRei[0]][posRei[1] - 2] = jogador == BRANCO ? "K" : "k";

        //Adiciona a nova posição do rei à posDestaque
        _posDestaque.push_back({posRei[0], posRei[1] - 2});

        //Move a torre 3 casas para a direita
        _tabuleiro[posTorre[0]][posTorre[1]] = "";
        _tabuleiro[posTorre[0]][posTorre[1] + 3] = jogador == BRANCO ? "R" : "r";

        _interface->imprimirInformacao("Movimento roque do " + std::string(jogador == BRANCO ? "branco" : "preto") + " para a esquerda");

    }

    //Para a direita (kingside)
    else {
        //Posição inicial da torre
        jogador == BRANCO ? posTorre = {7, 7} : posTorre = {0, 7};

        //Move o rei 2 casas para a direita
        _tabuleiro[posRei[0]][posRei[1]] = "";
        _tabuleiro[posRei[0]][posRei[1] + 2] = jogador == BRANCO ? "K" : "k";

        //Adiciona a nova posição do rei à posDestaque
        _posDestaque.push_back({posRei[0], posRei[1] + 2});

        //Move a torre 2 casas para a esquerda
        _tabuleiro[posTorre[0]][posTorre[1]] = "";
        _tabuleiro[posTorre[0]][posTorre[1] - 2] = jogador == BRANCO ? "R" : "r";

        _interface->imprimirInformacao("Movimento roque do " + std::string(jogador == BRANCO ? "branco" : "preto") + " para a direita");
    }
}

void Partida::_moverPeca(int jogador, std::string peca, std::string destino, std::string colunaOrigem, bool captura) {
    std::string pecaAtual, pecaCapturada, colunas = "abcdefgh";
    std::vector<int> posInicial;
    int indiceOrigem;

    _interface->imprimirInformacao("Movendo " + _pecas[peca] + " " + std::string(((jogador == BRANCO) ? "branco" : "preto")) + " para " + destino);

    //Encontra os índices i,j do destino na matriz do tabuleiro a partir da coordenada algébrica (e1 -> linha 0, coluna 4)
    std::vector<int> posFinal = _encontrarIndices(destino);

    //Adiciona posFinal a posDestaque
    _posDestaque.push_back(posFinal);

    //TODO: iterar o tabuleiro e testar as peças do tipo certo até achar uma que atenda aos requisitos de movimento em x e y
    for (int i = 0; i < _tabuleiro.size(); i++) {
        for (int j = 0; j < _tabuleiro[i].size(); j++) {
            pecaAtual = _tabuleiro[i][j];
            posInicial = {i, j};

            //Avança para a próxima iteração se a coluna de origem for informada e a atual não for ela
            if (colunaOrigem.length() > 0) {
                indiceOrigem = colunas.find(colunaOrigem);
                if (indiceOrigem >= 0 && j != indiceOrigem) {
                    continue;
                }
            }

            //Avança para a próxima iteração se a peça for do outro jogador
            if ((jogador == BRANCO && std::islower(pecaAtual[0])) || (jogador == PRETO && std::isupper(pecaAtual[0]))) continue;

            //Avança para a próxima iteração se a peça não for do mesmo tipo
            if (std::toupper(pecaAtual[0]) != peca[0]) continue;

            //Avança para a próxima iteração se o movimento for inválido
            if (peca == "R" && (!Validador::torre(posInicial, posFinal) || !_caminhoLivre(posInicial, posFinal)))
                continue;
            if (peca == "N" && !Validador::cavalo(posInicial, posFinal))
                continue;
            if (peca == "B" && !Validador::bispo(posInicial, posFinal))
                continue;
            if (peca == "Q" && !Validador::dama(posInicial, posFinal))
                continue;
            if (peca == "K" && !Validador::rei(posInicial, posFinal))
                continue;
            if (peca == "P") {
                //Verifica se a linha do peão é a inicial (primeira jogada da peça)
                bool primeiraJogada = (posInicial[0] == 1 && jogador == PRETO) || (posInicial[0] == 6 && jogador == BRANCO);

                if (!Validador::peao(posInicial, posFinal, jogador, primeiraJogada, captura))
                    continue;
            }

            //Com a peça certa encontrada na posição (i, j)
            //Remove a peça do quadrado atual
            _tabuleiro[posInicial[0]][posInicial[1]] = "";

            //Muda a peça para uma letra minúscula se for do preto
            if (jogador == PRETO) peca[0] = std::tolower(peca[0]);

            //Registra a captura da peça na posição final (para o jogador contrário), se houver
            if (captura) {
                pecaCapturada = _tabuleiro[posFinal[0]][posFinal[1]];
                jogador == BRANCO ? _capturadosPreto.push_back(pecaCapturada) : _capturadosBranco.push_back(pecaCapturada);

                //Imprime a captura
                pecaCapturada = std::toupper(pecaCapturada[0]);
                _interface->imprimirInformacao(_pecas[pecaCapturada] + " " + std::string((jogador == BRANCO ? "preto" : "branco")) + " capturado", COR_CAPTURA);
            }

            //Adiciona a peça na nova posição e encerra a iteração
            _tabuleiro[posFinal[0]][posFinal[1]] = peca;
            return;
        }
    }
}

std::vector<int> Partida::_encontrarIndices(std::string coordenada) {
    std::string colunas = "abcdefgh", linhas = "87654321";
    std::string colunaStr = coordenada.substr(0, 1), linhaStr = coordenada.substr(1, 1);

    int coluna = colunas.find(colunaStr), linha = linhas.find(linhaStr);

    return {linha, coluna};
}

bool Partida::_caminhoLivre(std::vector<int> posInicial, std::vector<int> posFinal) {
    //Movimento não horizontal não implementado
    if (posInicial[0] != posFinal[0]) return true;

    //Linha a ser avaliada no tabuleiro
    std::vector<std::string> linha = _tabuleiro[posInicial[0]];

    //Movimento horizontal para direita
    if (posFinal[1] > posInicial[1]) {
        //Itera a linha do tabuleiro entre o y inicial e final (intervalo aberto)
        for (int i = posInicial[1] + 1; i < posFinal[1]; i++) {
            //Se a posição não estiver vazia, o caminho não está livre
            if (linha[i].length() > 0) return false;
        }
    }
    //Movimento horizontal para esquerda
    else {
        //Itera a linha do tabuleiro entre o y inicial e final (intervalo aberto)
        for (int i = posFinal[1] - 1; i > posInicial[1]; i--) {
            //Se a posição não estiver vazia, o caminho não está livre
            if (linha[i].length() > 0) return false;
        }
    }

    //Se nenhuma peça foi encontrada, o caminho está livre
    return true;
}
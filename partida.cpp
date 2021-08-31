#include "partida.h"

#include <iostream>

Partida::Partida(std::string nomeArquivo) {
    std::ifstream arquivo;
    std::string linha, evento, local, data, rodada, branco, preto, resultado;
    std::vector<std::string> jogadas;

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

        //Extrai as jogadas das linhas restantes do arquivo
        jogadas = _lerJogadas(arquivo);

        //Cria o objeto jogo com os dados que foram lidos
        _jogo = Jogo(evento, local, data, rodada, branco, preto, resultado, jogadas);

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

        _pecas = {{"R", "torre"}, {"N", "cavalo"}, {"B", "bispo"}, {"Q", "dama"}, {"K", "rei"}, {"P", "peão"}};

    } else {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
        exit(-1);
    }
}

Jogo Partida::getJogo() {
    return _jogo;
}
std::vector<std::vector<std::string>> Partida::getTabuleiro() {
    return _tabuleiro;
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

            ++posInicio;

            //Remove o começo da linha até o . (antes da jogada), interrompe se não encontrado
            linha = linha.substr(posInicio);

            //Encontra a posição do primeiro espaço no meio da jogada, interrompe se não encontrado
            posMeio = linha.find(" ");
            if (posMeio < 0) break;

            //Encontra a posição do segundo espaço ao final da jogada, usa o último char da linha se não encontrado
            posFim = linha.find(" ", posMeio + 1);
            if (posFim < 0) posFim = linha.length() - 1;

            //Extrai a jogada (entre o começo da linha e a posição final encontrada) e adiciona ela ao vetor
            jogada = linha.substr(0, posFim);
            jogadas.push_back(jogada);

            //Remove o pedaço da linha até a posição final anterior para continuar na próxima iteração
            linha = linha.substr(posFim);
        }
    }

    return jogadas;
}

void Partida::proximaJogada() {
    //Obtém a string de NAP da próxima jogada
    ++_jogadaAtual;

    if (_jogadaAtual >= _jogo.getJogadas().size()) {
        _acabou = true;
        std::cout << "fim das jogadas" << std::endl;
        return;
    }

    std::string jogada = _jogo.getJogada(_jogadaAtual);
    std::cout << "Próxima jogada: " << jogada << std::endl;

    //Separa as jogadas em branco e preto
    int posMeio = jogada.find(" ");
    std::string jogadaBranco = jogada.substr(0, posMeio);
    std::string jogadaPreto = jogada.substr(posMeio + 1);

    //Aplica as jogadas no tabuleiro
    _aplicarJogada(BRANCO, jogadaBranco);
    _aplicarJogada(PRETO, jogadaPreto);
}

void Partida::_aplicarJogada(int jogador, std::string jogada) {
    std::string peca, destino;
    int posInicio;

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

    //Extrai a coordenada algébrica do destino da peça
    destino = jogada.substr(posInicio, 2);

    //Move um tipo de peça de um jogador específico para o destino encontrado
    _moverPeca(jogador, peca, destino);
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

        //Move a torre 3 casas para a direita
        _tabuleiro[posTorre[0]][posTorre[1]] = "";
        _tabuleiro[posTorre[0]][posTorre[1] + 3] = jogador == BRANCO ? "R" : "r";

        std::cout << "Movimento roque do "
                  << ((jogador == BRANCO) ? "branco" : "preto")
                  << " para a esquerda" << std::endl;

    }

    //Para a direita (kingside)
    else {
        //Posição inicial da torre
        jogador == BRANCO ? posTorre = {7, 7} : posTorre = {0, 7};

        //Move o rei 2 casas para a direita
        _tabuleiro[posRei[0]][posRei[1]] = "";
        _tabuleiro[posRei[0]][posRei[1] + 2] = jogador == BRANCO ? "K" : "k";

        //Move a torre 2 casas para a esquerda
        _tabuleiro[posTorre[0]][posTorre[1]] = "";
        _tabuleiro[posTorre[0]][posTorre[1] - 2] = jogador == BRANCO ? "R" : "r";

        std::cout << "Movimento roque do "
                  << ((jogador == BRANCO) ? "branco" : "preto")
                  << " para a direita" << std::endl;
    }
}

void Partida::_moverPeca(int jogador, std::string peca, std::string destino) {
    std::string pecaAtual;
    std::vector<int> posInicial;

    std::cout << "Movendo " << _pecas[peca] << " "
              << ((jogador == BRANCO) ? "branco" : "preto")
              << " para " << destino << std::endl;

    //Encontra os índices i,j do destino na matriz do tabuleiro a partir da coordenada algébrica (e1 -> linha 0, coluna 4)
    std::vector<int> posFinal = _encontrarIndices(destino);

    //TODO: iterar o tabuleiro e testar as peças do tipo certo até achar uma que atenda aos requisitos de movimento em x e y
    for (int i = 0; i < _tabuleiro.size(); i++) {
        for (int j = 0; j < _tabuleiro[i].size(); j++) {
            pecaAtual = _tabuleiro[i][j];
            posInicial = {i, j};

            //Avança para a próxima iteração se a peça for do outro jogador
            if ((jogador == BRANCO && std::islower(pecaAtual[0])) || (jogador == PRETO && std::isupper(pecaAtual[0]))) continue;

            //Avança para a próxima iteração se a peça não for do mesmo tipo
            if (std::toupper(pecaAtual[0]) != peca[0]) continue;

            //Avança para a próxima iteração se o movimento for inválido
            if (peca == "R" && !Validador::torre(posInicial, posFinal))
                continue;
            if (peca == "N" && !Validador::cavalo(posInicial, posFinal))
                continue;
            if (peca == "B" && !Validador::bispo(posInicial, posFinal))
                continue;
            if (peca == "Q" && !Validador::dama(posInicial, posFinal))
                continue;
            if (peca == "K" && !Validador::rei(posInicial, posFinal))
                continue;
            if (peca == "P" && !Validador::peao(posInicial, posFinal, _jogadaAtual))
                continue;

            //Com a peça certa encontrada na posição (i, j)
            //Remove a peça do quadrado atual
            _tabuleiro[posInicial[0]][posInicial[1]] = "";

            //Muda a peça para uma letra minúscula se for do preto
            if (jogador == PRETO) peca[0] = std::tolower(peca[0]);

            //Adiciona a peça na nova posição
            _tabuleiro[posFinal[0]][posFinal[1]] = peca;
        }
    }
}

std::vector<int> Partida::_encontrarIndices(std::string coordenada) {
    std::string colunas = "abcdefgh", linhas = "87654321";
    std::string colunaStr = coordenada.substr(0, 1), linhaStr = coordenada.substr(1, 1);

    int coluna = colunas.find(colunaStr), linha = linhas.find(linhaStr);

    return {linha, coluna};
}
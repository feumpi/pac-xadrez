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
        jogadas = _lerJogadas(&arquivo);

        //Cria o objeto jogo com os dados que foram lidos
        _jogo = Jogo(evento, local, data, rodada, branco, preto, resultado, jogadas);

        //Inicializa o tabuleiro com as posições iniciais das peças
        _tabuleiro = {
            //Linha 1
            {
                "r",  //torre preta (Rook)
                "n",  //cavaleiro preto (kNight)
                "b",  //bispo preto (Bishop)
                "q",  //rainha preta (Queen)
                "k",  //rei preto (King)
                "b",  //bispo preto (Bishop)
                "n",  //cavaleiro preto (kNight)
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
                "N",  //cavaleiro branco (kNight)
                "B",  //bispo branco (Bishop)
                "Q",  //rainha branca (Queen)
                "K",  //rei branco (King)
                "B",  //bispo branco (Bishop)
                "N",  //cavaleiro branco (kNight)
                "R",  //torre branca (Rook)
            }};

        _pecas = {{"R", "torre"}, {"N", "cavaleiro"}, {"B", "bispo"}, {"Q", "rainha"}, {"K", "rei"}, {"P", "peão"}};

    } else {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
    }
}

Jogo Partida::getJogo() {
    return _jogo;
}
std::vector<std::vector<std::string>> Partida::getTabuleiro() {
    return _tabuleiro;
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

std::vector<std::string> Partida::_lerJogadas(std::ifstream* arquivo) {
    std::string linha, jogada;
    std::vector<std::string> jogadas;
    int posInicio, posMeio, posFim;

    //Itera as linhas restantes do arquivo
    while (getline(*arquivo, linha)) {
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

void Partida::_moverPeca(int jogador, std::string peca, std::string destino) {
    std::cout << "Movendo " << _pecas[peca] << " "
              << ((jogador == BRANCO) ? "branco" : "preto")
              << " para " << destino << std::endl;

    //TODO: iterar o tabuleiro e testar as peças do tipo certo até achar uma que atenda aos requisitos de movimento em x e y

    //Encontra os índices i,j do destino na matriz do tabuleiro a partir da coordenada algébrica (e1 -> linha 0, coluna 4)
    std::vector<int> indices = _encontrarIndices(destino);

    //_tabuleiro[indices[0]][indices[1]] = jogador == BRANCO ? "P" : "p";
}

std::vector<int> Partida::_encontrarIndices(std::string coordenada) {
    std::string colunas = "abcdefgh", linhas = "12345678";
    std::string colunaStr = coordenada.substr(0, 1), linhaStr = coordenada.substr(1, 1);

    int coluna = colunas.find(colunaStr), linha = linhas.find(linhaStr);

    return {linha, coluna};
}
#include "partida.h"

#include <iostream>

Partida::Partida(std::string nomeArquivo) {
    std::ifstream arquivo;
    std::string linha, evento, local, data, rodada, branco, preto, resultado;
    std::vector<std::string> jogadas;

    arquivo.open(nomeArquivo);

    if (arquivo.is_open()) {
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

        jogadas = _lerJogadas(&arquivo);

        _jogo = Jogo(evento, local, data, rodada, branco, preto, resultado, jogadas);

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

    posInicio = linha.find("\"");
    posInicio++;
    posFim = linha.find("\"]");
    valor = linha.substr(posInicio, posFim - posInicio);
    return valor;
}

std::string Partida::_extrairJogada(std::string* linha) {
    std::string jogada;
}

std::vector<std::string> Partida::_lerJogadas(std::ifstream* arquivo) {
    std::string linha, jogada;
    std::vector<std::string> jogadas;
    int posInicio, posMeio, posFim;

    while (getline(*arquivo, linha)) {
        while (linha.length() > 0) {
            posInicio = linha.find(".");

            //Pula para a próxima linha se não for uma linha de jogadas
            if (posInicio < 0) break;

            posInicio++;

            linha = linha.substr(posInicio);

            if (posInicio < 0) break;

            posMeio = linha.find(" ");

            if (posMeio < 0) break;

            posFim = linha.find(" ", posMeio + 1);

            if (posFim < 0) posFim = linha.length() - 1;

            jogada = linha.substr(0, posFim);

            jogadas.push_back(jogada);

            linha = linha.substr(posFim);
        }
    }

    return jogadas;
}
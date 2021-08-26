#include "partida.h"

#include <iostream>

Partida::Partida(std::string nomeArquivo) {
    std::ifstream arquivo;
    std::string linha, evento, local, data, rodada, branco, preto, resultado;

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

        _jogo = Jogo(evento, local, data, rodada, branco, preto, resultado);

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
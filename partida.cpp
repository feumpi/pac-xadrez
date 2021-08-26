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

    } else {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
    }
}

Jogo Partida::getJogo() {
    return _jogo;
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
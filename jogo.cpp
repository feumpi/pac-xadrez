#include "jogo.h"

#include <iostream>

Jogo::Jogo(std::string evento, std::string local, std::string data, std::string rodada, std::string branco, std::string preto, std::string resultado, std::vector<std::string> jogadas) {
    //Inicializa as propriedades privadas se os valores forem recebidos
    _evento = evento;
    _local = local;
    _data = data;
    _rodada = rodada;
    _branco = branco;
    _preto = preto;
    _resultado = resultado;
    _jogadas = jogadas;
}

std::string Jogo::getEvento() {
    return _evento;
}
std::string Jogo::getLocal() {
    return _local;
}
std::string Jogo::getData() {
    return _data;
}
std::string Jogo::getRodada() {
    return _rodada;
}
std::string Jogo::getBranco() {
    return _branco;
}
std::string Jogo::getPreto() {
    return _preto;
}
std::string Jogo::getResultado() {
    return _resultado;
}
std::vector<std::string> Jogo::getJogadas() {
    return _jogadas;
}
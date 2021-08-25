#include "jogo.h"

#include <iostream>

Jogo::Jogo(std::string evento, std::string local, std::string data, int rodada, std::string branco, std::string preto, std::string resultado) {
    _evento = evento;
    _local = local;
    _data = data;
    _rodada = rodada;
    _branco = branco;
    _preto = preto;
    _resultado = resultado;
}

void Jogo::imprimirDados() {
    std::cout << "Evento: " << _evento << std::endl;
    std::cout << "Local: " << _local << std::endl;
    std::cout << "Data: " << _data << std::endl;
    std::cout << "Rodada: " << _rodada << std::endl;
    std::cout << "Branco: " << _branco << std::endl;
    std::cout << "Preto: " << _preto << std::endl;
    std::cout << "Resultado: " << _resultado << std::endl;
}
#include "jogo.h"

#include <iostream>

Jogo::Jogo(std::string evento, std::string local, std::string data, std::string rodada, std::string branco, std::string preto, std::string resultado, std::string eloBranco, std::string eloPreto, std::string eco, std::vector<std::string> jogadas) {
    //Inicializa as propriedades privadas se os valores forem recebidos
    _evento = evento;
    _local = local;
    _data = data;
    _rodada = rodada;
    _branco = branco;
    _preto = preto;
    _resultado = resultado;
    _eloBranco = eloBranco;
    _eloPreto = eloPreto;
    _eco = eco;
    _jogadas = jogadas;
}

std::string Jogo::getEvento() {
    return _evento;
}
std::string Jogo::getLocal() {
    return _local;
}
std::string Jogo::getData() {
    std::string dia, mes, ano, data;
    int pos;

    data = _data;

    //Extrai o ano e corta a string data
    pos = data.find(".");
    ano = data.substr(0, pos);
    data = data.substr(pos + 1);

    //Extrai o mes, corta a string e usa o restante como dia
    pos = data.find(".");
    mes = data.substr(0, pos);
    dia = data.substr(pos + 1);

    //Retorna a data no formato adequado, ignorando dia e mês caso não existam
    return (dia != "??" ? dia + " de " : "") + (mes != "??" ? _meses[mes] + " de " : "") + ano;
}
std::string Jogo::getRodada() {
    return _rodada;
}
std::string Jogo::getBranco() {
    return _formatarNome(_branco);
}
std::string Jogo::getPreto() {
    return _formatarNome(_preto);
}
std::string Jogo::getResultado() {
    if (_resultado == "1-0") return _formatarNome(_branco) + " (branco) venceu";
    if (_resultado == "0-1") return _formatarNome(_preto) + " (preto) venceu";
    return "Houve empate";
}

std::string Jogo::getEloBranco() {
    return _eloBranco;
}

std::string Jogo::getEloPreto() {
    return _eloPreto;
}

std::string Jogo::getEco() {
    return _eco;
}

std::vector<std::string> Jogo::getJogadas() {
    return _jogadas;
}

std::string Jogo::getJogada(int indice) {
    if (indice < 0 || indice > _jogadas.size() - 1) {
        std::cout << "Jogada invalida" << std::endl;
        return "";
    }

    return _jogadas[indice];
}

std::string Jogo::_formatarNome(std::string nome) {
    std::string primeiroNome, sobrenome;
    int pos;

    //Encontra a posição do separador entre nome e sobrenome e extrai os dois
    pos = nome.find(",");
    primeiroNome = nome.substr(0, pos);
    sobrenome = nome.substr(pos + 1);

    //Retorna o nome no formato adequado concatenando as strings
    return primeiroNome + " " + sobrenome;
}
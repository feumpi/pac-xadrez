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

            posInicio++;

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
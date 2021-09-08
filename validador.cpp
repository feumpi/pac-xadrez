#include "validador.h"

bool Validador::torre(std::vector<int> posInicial, std::vector<int> posFinal) {
    int difY = std::abs(posFinal[0] - posInicial[0]);
    int difX = std::abs(posFinal[1] - posInicial[1]);

    //Qualquer número de casas, mas apenas em X OU Y
    return (difX > 0 && difY == 0) || (difY > 0 && difX == 0);
}

bool Validador::cavalo(std::vector<int> posInicial, std::vector<int> posFinal) {
    int difY = std::abs(posFinal[0] - posInicial[0]);
    int difX = std::abs(posFinal[1] - posInicial[1]);

    //Movimento de L vertical ou horizontal
    return (difX == 1 && difY == 2) || (difX == 2 && difY == 1);
}

bool Validador::bispo(std::vector<int> posInicial, std::vector<int> posFinal) {
    int difY = std::abs(posFinal[0] - posInicial[0]);
    int difX = std::abs(posFinal[1] - posInicial[1]);

    //Qualquer número de casas diagonalmente
    return difX > 0 && difY > 0 && difX == difY;
}

bool Validador::dama(std::vector<int> posInicial, std::vector<int> posFinal) {
    int difY = std::abs(posFinal[0] - posInicial[0]);
    int difX = std::abs(posFinal[1] - posInicial[1]);

    //Qualquer número de casas em linha reta OU diagonalmente
    return ((difX > 0 && difY == 0) || (difY > 0 && difX == 0)) || (difX > 0 && difY > 0 && difX == difY);
}

bool Validador::rei(std::vector<int> posInicial, std::vector<int> posFinal) {
    int difY = std::abs(posFinal[0] - posInicial[0]);
    int difX = std::abs(posFinal[1] - posInicial[1]);

    //Uma casa em qualquer direção
    return (difX == 1 && difY == 0) || (difX == 0 && difY == 1) || (difX == 1 && difY == 1);
}

bool Validador::peao(std::vector<int> posInicial, std::vector<int> posFinal, bool primeiraJogada, bool captura) {
    //Nesse caso, importa se é positivo ou negativo, e os índices do tabuleiro começam ao contrário (de cima pra baixo)
    int difY = std::abs(posFinal[0] - posInicial[0]);
    int difX = std::abs(posFinal[1] - posInicial[1]);

    //Primeira jogada
    if (primeiraJogada) {
        //Uma ou duas casas para frente
        return difX == 0 && (difY == 1 || difY == 2);
    }

    //Uma casa diagonal em captura
    if (captura) {
        return difX == 1 && difY == 1;
    }

    //Uma casa para frente nos outros casos
    return difY == 1 && difX == 0;
}
#include "interface.h"

Interface::Interface() {
    std::cout << "Bem-vindo!" << std::endl;
};

Interface::~Interface() {
    std::cout << "Obrigado por usar o programa!" << std::endl;
}

void Interface::imprimirJogo(Jogo jogo) {
    //Obtém e imprime cada um dos dados extras
    std::cout << "Evento: " << jogo.getEvento() << std::endl;
    std::cout << "Local: " << jogo.getLocal() << std::endl;
    std::cout << "Data: " << jogo.getData() << std::endl;
    std::cout << "Rodada: " << jogo.getRodada() << std::endl;
    std::cout << "Branco: " << jogo.getBranco() << std::endl;
    std::cout << "Preto: " << jogo.getPreto() << std::endl;
    std::cout << "Resultado: " << jogo.getResultado() << std::endl;
}

void Interface::imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro, bool legenda) {
    std::cout << std::endl;
    int numLinha;

    if (legenda) std::cout << T_LEGENDA;

    std::cout << T_LINHA_LETRAS;
    std::cout << T_BORDA_HORIZONTAL;

    //Iteração das linhas
    for (int i = 0; i < tabuleiro.size(); i++) {
        std::cout << T_LINHA_VAZIA;
        //Imprime o número da linha, de 8 a 1, e a borda esquerda
        numLinha = 8 - i;
        std::cout << "[" << numLinha << "] |";

        //Iteração das colunas em cada linha
        for (auto coluna : tabuleiro[i]) {
            //Elemento do quadrado ou espaço vazio, espaçamento e borda direita
            std::cout << "   " << (coluna.length() > 0 ? coluna : " ") << "   |";
        }

        std::cout << " [" << numLinha << "]\n";
        std::cout << T_LINHA_VAZIA;
        std::cout << T_BORDA_HORIZONTAL;
    }

    std::cout << T_LINHA_LETRAS;
    std::cout << std::endl;
}

void Interface::imprimirCapturados(std::vector<std::vector<std::string>> capturados) {
    std::vector<std::string> branco = capturados[0], preto = capturados[1];

    std::cout << "Capturados Branco: ";
    for (auto peca : branco) {
        std::cout << peca << " ";
    }
    std::cout << std::endl;

    std::cout << "Capturados Preto: ";
    for (auto peca : preto) {
        std::cout << peca << " ";
    }
    std::cout << std::endl;
}

void Interface::imprimirResultado(std::string resultado, int jogadas, int capturadosBranco, int capturadosPreto) {
    std::cout << "\n\n"
              << "###############################\n"
              << "#                             #\n"
              << "#         FIM DO JOGO         #\n"
              << "#                             #\n"
              << "###############################\n\n"
              << "Resultado: " << resultado << "\n\n"
              << jogadas << " jogadas foram executadas\n"
              << capturadosBranco << " peças brancas foram capturadas\n"
              << capturadosBranco << " peças pretas foram capturadas\n"
              << std::endl;
}
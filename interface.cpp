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

    //Obtém o vetor de jogadas em NAP e imprime cada uma
    std::vector<std::string> jogadas = jogo.getJogadas();
    std::cout << "\n\nJogadas:\n\n";
    for (int i = 0; i < jogadas.size(); i++) {
        std::cout << jogadas[i] << std::endl;
    }
    std::cout << std::endl;
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
        for (int j = 0; j < tabuleiro[i].size(); j++) {
            //Elemento do quadrado ou espaço vazio, espaçamento e borda direita
            std::cout << "   " << (tabuleiro[i][j].length() > 0 ? tabuleiro[i][j] : " ") << "   |";
        }

        std::cout << " [" << numLinha << "]\n";
        std::cout << T_LINHA_VAZIA;
        std::cout << T_BORDA_HORIZONTAL;
    }

    std::cout << T_LINHA_LETRAS;
    std::cout << std::endl;
}
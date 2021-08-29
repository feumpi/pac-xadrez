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

void Interface::imprimirTabuleiro(std::vector<std::vector<std::string>> tabuleiro) {
    //Iteração das linhas
    for (int i = 0; i < tabuleiro.size(); i++) {
        //Imprime o número da linha, de 8 a 1
        std::cout << "[" << 8 - i << "]"
                  << "\t";

        //Iteração das colunas em cada linha
        for (int j = 0; j < tabuleiro[i].size(); j++) {
            //Elemento do quadrado e espaçmento à direita
            std::cout << tabuleiro[i][j] << "\t";
        }

        std::cout << std::endl
                  << std::endl;
    }
    //Imprime as letras das colunas correspondentes, com o mesmo espaçamento
    std::cout << "\t[A]\t[B]\t[C]\t[D]\t[E]\t[F]\t[G]]\t[H]" << std::endl;
}
#include "interface.h"

Interface::Interface() {
    std::cout << "Bem-vindo!" << std::endl;
};

Interface::~Interface() {
    std::cout << "Obrigado por usar o programa!" << std::endl;
}

void Interface::imprimirJogo(Jogo jogo) {
    std::cout << "Evento: " << jogo.getEvento() << std::endl;
    std::cout << "Local: " << jogo.getLocal() << std::endl;
    std::cout << "Data: " << jogo.getData() << std::endl;
    std::cout << "Rodada: " << jogo.getRodada() << std::endl;
    std::cout << "Branco: " << jogo.getBranco() << std::endl;
    std::cout << "Preto: " << jogo.getPreto() << std::endl;
    std::cout << "Resultado: " << jogo.getResultado() << std::endl;
}
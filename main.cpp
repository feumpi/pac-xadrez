/*#######################################################################
#                                                                       #
#   Universidade Federal do Espírito Santo                              #
#   INF09324 Programação Aplicada de Computadores 2021/1                #
#   Primeiro trabalho                                                   #
#                                                                       #
#   Aluno: 2020205193 Felipe Pereira Umpierre                           #
#   Professor: Rodrigo Martins de Siqueira Barbosa                      #
#   Entrega: 01/09/2021                                                 #
#                                                                       #
#   Como utilizar: USO.pdf ou USO.md                                    #
#   Sobre o desenvolvimento: DESENVOLVIMENTO.pdf ou DESENVOLVIMENTO.md  #
#                                                                       #
#######################################################################*/

#include <iostream>

#include "jogo.h"

int main() {
    Jogo jogo("Super torneio", "Minha casa", "2021-08-25", 3, "Felipe", "Batata", "2-2");

    std::cout << std::endl
              << std::endl;

    Jogo jogo2("Outro torneio", "Na rua", "2020-03-02", 1, "Maria", "Lucy", "4-2");

    jogo.imprimirDados();
    jogo2.imprimirDados();

    return 0;
}
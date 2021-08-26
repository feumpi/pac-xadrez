#ifndef JOGO_H
#define JOGO_H

#include <string>

class Jogo {
   public:
    Jogo(std::string evento = "", std::string local = "", std::string data = "", std::string rodada = "", std::string branco = "", std::string preto = "", std::string resultado = "");

    std::string getEvento();
    std::string getLocal();
    std::string getData();
    std::string getRodada();
    std::string getBranco();
    std::string getPreto();
    std::string getResultado();

   private:
    std::string _evento;
    std::string _local;
    std::string _data;
    std::string _rodada;
    std::string _branco;
    std::string _preto;
    std::string _resultado;
};

#endif
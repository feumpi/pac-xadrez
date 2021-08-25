#include <string>

class Jogo {
   public:
    Jogo(std::string evento, std::string local, std::string data, int rodada, std::string branco, std::string preto, std::string resultado);

    void imprimirDados();

   private:
    std::string _evento;
    std::string _local;
    std::string _data;
    int _rodada;
    std::string _branco;
    std::string _preto;
    std::string _resultado;
};
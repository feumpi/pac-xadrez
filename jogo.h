#ifndef JOGO_H
#define JOGO_H

#include <map>
#include <string>
#include <vector>

class Jogo {
   public:
    //Inicializa recebendo os dados do jogo ou em branco, com strings vazias
    Jogo(std::string evento = "", std::string local = "", std::string data = "", std::string rodada = "", std::string branco = "", std::string preto = "", std::string resultado = "", std::vector<std::string> jogadas = {});

    //Getters
    std::string getEvento();
    std::string getLocal();
    std::string getData();
    std::string getRodada();
    std::string getBranco();
    std::string getPreto();
    std::string getResultado();
    std::vector<std::string> getJogadas();
    std::string getJogada(int indice);

   private:
    std::string _evento;
    std::string _local;
    std::string _data;
    std::string _rodada;
    std::string _branco;
    std::string _preto;
    std::string _resultado;
    std::vector<std::string> _jogadas;
    std::map<std::string, std::string> _meses = {{"01", "janeiro"},
                                                 {"02", "fevereiro"},
                                                 {"03", "março"},
                                                 {"04", "abril"},
                                                 {"05", "maio"},
                                                 {"06", "junho"},
                                                 {"07", "julho"},
                                                 {"08", "agosto"},
                                                 {"09", "setembro"},
                                                 {"10", "outubro"},
                                                 {"11", "novembro"},
                                                 {"12", "dezembro"}};

    std::string
    _formatarNome(std::string nome);
};

#endif
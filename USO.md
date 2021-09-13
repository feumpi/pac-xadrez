### Universidade Federal do Espírito Santo

### INF09324 Programação Aplicada de Computadores 2021/1

### Primeiro trabalho

### Aluno: 2020205193 Felipe Pereira Umpierre

### Professor: Rodrigo Martins de Siqueira Barbosa

---

# Sobre o programa

Este programa é um visualizador de partida de xadrez. Ao iniciar, deve ser informado um arquivo válido em formato PGN contendo os dados de uma partida. É possível ver as informações sobre o jogo e acompanhar a partida jogada a jogada numa representação visual de tabuleiro, junto com informações sobre o que está acontecendo. A qualquer momento, o usuário pode pressionar [ENTER] para continuar (começar o jogo ou avançar para a próxima jogada) ou [q] para sair do programa.

# Compatibilidade

O programa foi testado e funcionou como esperado primariamente em ambiente Linux com `Ubuntu 20.04 LTS` e compilado com `gcc 9.3.0`. Adicionalmente, em `Windows 10 build 22454` compilado com `gcc 10.2.0`. Apesar dos esforços para manter o programa multiplataforma e oferecer bibliotecas e instruções de compilação equivalentes, a execução em Linux é recomendada, se possível.

# Como utilizar este programa

## Preparar bibliotecas

**Linux:** Installe o pacote `libncurses-dev`, necessário para compilar a biblioteca `ncurses.h`:

```bash
sudo apt install libncurses-dev
```

_no caso do Ubuntu, ou pacote e sintaxe equivalente para a distribuição utilizada._

**Windows:** baixe e compile o código-fonte da biblioteca _PDCurses_:

```bash
git clone https://github.com/wmcbrine/PDCurses
cd PDCurses\wincon
make
```

_ou `mingw32-make`, de acordo com a disponibilidade._

Observe que os arquivos `PDCurses\wincon\curses.h` e `PDCurses\wincon\pdcurses.a` são esperados nesses exatos caminhos, a partir da raiz do programa, para o correto funcionamento.

## Compilar

**Linux:** Compile o código-fonte incluindo os arquivos **main.cpp**, **jogo.cpp**, **partida.cpp**, **interface.cpp** e **validador.cpp** e a biblioteca **ncurses**, criando um executável **main.sh**:

```bash
> g++ main.cpp jogo.cpp partida.cpp interface.cpp validador.cpp -lncurses -o main.sh
```

Ou usando um atalho para incluir todos os arquivos **.cpp** do diretório:

```bash
> g++ *.cpp -lncurses -o main.sh
```

**Windows:** Compile o código-fonte incluindo os arquivos **main.cpp**, **jogo.cpp**, **partida.cpp**, **interface.cpp** e **validador.cpp** e a biblioteca **pdcurses**, criando um executável **main.exe**:

```bash
> g++ main.cpp jogo.cpp partida.cpp interface.cpp validador.cpp pdcurses.a -o main.exe
```

## Executar

Execute o arquivo criado no passo anterior

**Linux:**

```bash
./main.sh
```

**Windows:**

```bash
main.exe
```

O programa solicitará o nome de um arquivo PGN a ser lido:

```bash
Informe o nome de um arquivo PGN a ser lido. Ex: jogo01.pgn
> Nome: _
```

Esse passo pode ser evitado informando o nome como argumento na linha de comando:

```bash
> ./main.sh jogo01.pgn
```

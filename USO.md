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

```console
sudo apt install libncurses-dev
```

_no caso do Ubuntu, ou pacote e sintaxe equivalente para a distribuição utilizada._

**Windows:** baixe e compile o código-fonte da biblioteca _PDCurses_:

```console
git clone https://github.com/wmcbrine/PDCurses
cd PDCurses\wincon
make
```

_ou `mingw32-make`, de acordo com a disponibilidade._

Observe que os arquivos `PDCurses\curses.h` e `PDCurses\wincon\pdcurses.a` são esperados nesses exatos caminhos, a partir da raiz do programa, para o correto funcionamento.

## Compilar

O código-fonte precisa da especificação **C++17** para funcionar. Ela é suportada pelo _GCC_ desde a versão 5, mas só é usada por padrão a partir da versão 11. Por isso, é necessário especificar `-std=c++17` no comando de compilação.

**Linux:** Compile o código-fonte incluindo os arquivos **main.cpp**, **jogo.cpp**, **partida.cpp**, **interface.cpp** e **validador.cpp** e a biblioteca **ncurses**, criando um executável **main.sh**:

```console
> g++ -std=c++17 main.cpp jogo.cpp partida.cpp interface.cpp validador.cpp -lncurses -o main.sh
```

Ou usando um atalho para incluir todos os arquivos **.cpp** do diretório:

```console
> g++ -std=c++17 *.cpp -lncurses -o main.sh
```

**Windows:** Compile o código-fonte incluindo os arquivos **main.cpp**, **jogo.cpp**, **partida.cpp**, **interface.cpp** e **validador.cpp** e a biblioteca **pdcurses.a**, criando um executável **main.exe**:

```console
g++ -std=c++17 main.cpp jogo.cpp partida.cpp interface.cpp validador.cpp PDCurses\wincon\pdcurses.a -o main.exe
```

## Executar

Execute o arquivo criado no passo anterior

**Linux:**

```console
./main.sh
```

**Windows:**

```console
main.exe
```

O programa irá buscar arquivos PGN na mesma pasta do executável e oferecer como opções, bastando pressionar o número correspondente:

```
################################
#                              #
#          PAC XADREZ          #
#                              #
################################
Bem-vindo!

Escolha um arquivo PGN para comecar:

1) jogo03.pgn
2) jogo02.pgn
3) jogo01.pgn
```

Esse passo pode ser evitado informando o nome como argumento na executação:

```bash
./main.sh jogo01.pgn
```

Caso o arquivo não possa ser lido, o programa será encerrado:

```
Lendo arquivo jogo04.pgn

Encerrando o programa: Nao foi possivel abrir o arquivo jogo04.pgn

Pressione [ENTER] ou [q] para sair e retornar ao terminal.
```

O arquivo será carregado e as informações do jogo exibidas:

```
Lendo arquivo jogo01.pgn

jogo01.pgn carregado com sucesso!

Evento: URS-ch36
Local: URS
Data: 1968
Rodada: 2
Branco: Zaitsev  Igor A
Preto: Kholmov  Ratmir D
Resultado: Houve empate
```

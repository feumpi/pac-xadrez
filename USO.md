### Universidade Federal do Espírito Santo

### INF09324 Programação Aplicada de Computadores 2021/1

### Primeiro trabalho

### Aluno: 2020205193 Felipe Pereira Umpierre

### Professor: Rodrigo Martins de Siqueira Barbosa

---

# Sobre o programa

Este programa é um visualizador de partida de xadrez. Ao iniciar, deve ser informado um arquivo válido em formato PGN contendo os dados de uma partida. É possível ver as informações sobre o jogo e acompanhar a partida jogada a jogada numa representação visual de tabuleiro, junto com informações sobre o que está acontecendo. A qualquer momento, terá opções de ação como [ENTER] para continuar (começar o jogo ou avançar para a próxima jogada) ou [q] para sair do programa, sendo que algumas podem estar indisponíveis de acordo com o momento.

# Compatibilidade

O programa foi testado e funcionou como esperado primariamente em ambiente Linux com `Ubuntu 20.04 LTS` e compilado com `gcc 9.3.0`. Adicionalmente, em `Windows 10 build 22454` compilado com `gcc 10.2.0`. Apesar dos esforços para manter o programa multiplataforma e oferecer bibliotecas e instruções de compilação equivalentes, a execução em Linux é recomendada caso algum problema seja encontrado.

# Como utilizar este programa

## Preparar bibliotecas

**Linux:** Installe o pacote `libncurses-dev`, necessário para compilar a biblioteca `ncurses.h`:

```console
sudo apt install libncurses-dev
```

_no caso do Ubuntu, ou pacote e sintaxe equivalente para a distribuição utilizada._

**Windows:** baixe o código-fonte da biblioteca _PDCurses_ para a pasta do projeto:

```console
git clone https://github.com/wmcbrine/PDCurses
```
Ou baixe e extraia o .zip

Compile:
```
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

O programa irá buscar arquivos PGN na mesma pasta do executável e oferecer como opções, bastando pressionar o número correspondente, ou **q** para sair:

```
################################
#                              #
#          PAC XADREZ          #
#                              #
################################
Bem-vindo!

Escolha um arquivo PGN para comecar:

[1] 01.pgn
[2] 02.pgn
[3] 03.pgn

[q] sair
```

Esse passo pode ser evitado informando o nome como argumento na executação:

```bash
./main.sh jogo01.pgn
```

Caso o arquivo não possa ser lido, o programa será encerrado:

```
################################
#                              #
#          PAC XADREZ          #
#                              #
################################
Bem-vindo!

Lendo arquivo jogo04.pgn



Encerrando o programa: Nao foi possivel abrir o arquivo jogo04.pgn
```

O arquivo será carregado e as informações do jogo exibidas:

```
Lendo arquivo 01.pgn

01.pgn carregado com sucesso!

Evento: URS-ch36
Local: URS
Data: 1968
Rodada: 2
Branco: Zaitsev  Igor A
Preto: Kholmov  Ratmir D
Resultado: Houve empate
ECO: C42
```

A partir deste momento, um menu de opções sempre estará disponível, contendo opções diferentes de acordo com o momento:

```
 [ENTER] continuar  [q] sair
```

Pressionando **ENTER** para continuar, um tabuleiro inicial será exibido, junto com a legenda do que cada letra representa:

```

       [A]     [B]     [C]     [D]     [E]     [F]     [G]     [H]
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[8] |   r   |   n   |   b   |   q   |   k   |   b   |   n   |   r   | [8]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[7] |   p   |   p   |   p   |   p   |   p   |   p   |   p   |   p   | [7]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[6] |       |       |       |       |       |       |       |       | [6]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[5] |       |       |       |       |       |       |       |       | [5]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[4] |       |       |       |       |       |       |       |       | [4]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[3] |       |       |       |       |       |       |       |       | [3]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[2] |   P   |   P   |   P   |   P   |   P   |   P   |   P   |   P   | [2]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[1] |   R   |   N   |   B   |   Q   |   K   |   B   |   N   |   R   | [1]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
       [A]     [B]     [C]     [D]     [E]     [F]     [G]     [H]

R: torre, N: cavalo, B: bispo, Q: dama, K: rei, P: peão
MAIUSCULAS: BRANCAS, minusculas: pretas
```

À direita dele, fica a região onde será exibida informação adicional:

```
Aguardando o inicio da partida
```

Ao continuar mais uma vez, será aplicada a primeira jogada da partida carregada, atualizando as posições das peças no tabuleiro:

```

       [A]     [B]     [C]     [D]     [E]     [F]     [G]     [H]
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[8] |   r   |   n   |   b   |   q   |   k   |   b   |   n   |   r   | [8]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[7] |   p   |   p   |   p   |   p   |       |   p   |   p   |   p   | [7]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[6] |       |       |       |       |       |       |       |       | [6]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[5] |       |       |       |       |   p   |       |       |       | [5]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[4] |       |       |       |       |   P   |       |       |       | [4]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[3] |       |       |       |       |       |       |       |       | [3]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[2] |   P   |   P   |   P   |   P   |       |   P   |   P   |   P   | [2]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
    |       |       |       |       |       |       |       |       |
[1] |   R   |   N   |   B   |   Q   |   K   |   B   |   N   |   R   | [1]
    |       |       |       |       |       |       |       |       |
    -----------------------------------------------------------------
       [A]     [B]     [C]     [D]     [E]     [F]     [G]     [H]
```

Na janela à direita, são exibidas as informações sobre a jogada atual:

```
Jogada #1

Movendo peao branco para e4

PRETO: e5

Movendo peao preto para e5
```

Agora, abaixo do tabuleiro, ficam visíveis as peças já capturadas de cada jogador:

```
Pecas brancas capturadas: P Q B
Pecas pretas capturadas: p q n
```

E assim sucessivamente para cada jogada.

A partir da segunda jogada, o menu mostra também a opção voltar, que desfaz a última jogada e volta para a anterior:

```
[ENTER] continuar  [v] voltar  [q] sair
```

A janela à direita avisará quando acabarem as jogadas:

```
Fim das jogadas! Avance para ver o resultado.
```

Avançando nesse momento, será exibida a tela de fim de jogo com o resultado e algumas estatísticas:

```
###############################
#                             #
#         FIM DO JOGO         #
#                             #
###############################

Resultado: Houve empate

15 jogadas foram executadas
4 peças brancas foram capturadas
4 peças pretas foram capturadas
```

Agora, é possível recomeçar o jogo ou sair do programa:

```
 [r] recomecar  [q] sair
```

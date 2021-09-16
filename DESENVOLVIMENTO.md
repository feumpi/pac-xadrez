### Universidade Federal do Espírito Santo

### INF09324 Programação Aplicada de Computadores 2021/1

### Primeiro trabalho

### Aluno: 2020205193 Felipe Pereira Umpierre

### Professor: Rodrigo Martins de Siqueira Barbosa

---

# Sobre o desenvolvimento deste programa

## Convenções

### Nomes de classes

Para todos os nomes de classes, foi adotada a convenção _PascalCase_, com todas as iniciais de palavras em letra maiúscula.

```cpp
class NomeDaClasse {
    (...)
};
```

### Nomes de variáveis, propriedades e métodos

Para todos os nomes de variáveis, propriedades e métodos, foi adotada a convenção _camelCase_, com a primeira inicial minúscula e todas as iniciais seguintes em letra maiúscula.

No caso de propriedades e métodos privados, também foi utilizada a convenção de começar o nome com um _underscore_.

```cpp
(...)
public:
    int getPropriedadeUm();
    int getPropriedadeDois();
private:
    int _propriedadeUm;
    int _propriedadeDois;
(...)
```

## Sobre as classes

### Classe Jogo

Tem como propriedades os dados de um jogo, como o local e nomes dos jogadores, e também a sequência de jogadas em _NAP_.

### Classe Partida

Inicializa lendo os dados de um arquivo PGN e então instancia um objeto `Jogo` com eles. Contém também uma matriz que representa o tabuleiro com as posições das peças, os vetores de peças capturadas para cada jogador e os estados anteriores dessas variáveis no jogo. É responsável por interpretar e executar corretamente uma jogada, e também desfazê-lá.

### Classe Interface

Responsável pela entrada do usuário e pelas impressões na tela, como a formatação dos dados extras sobre um jogo e o desenho do tabuleiro com as peças nas posições certas. Abstrai para as outras classes a biblioteca `curses` que coleta entrada, gerencia a tela, janela e cores. Todas as impressões e coletas de entrada devem ser feitas por métodos dessa classe, nunca diretamente.

### Classe Validador

Uma classe de métodos estáticos (ou seja, que não precisa ser instanciada) para validar o movimento de uma peça de acordo com as regras do xadrez, recebendo as posições final e inicial no tabuleiro e retornado `true`, para um movimento válido, ou `false`, para um movimento proibido.

---

## Fluxo do programa

### O início de tudo

Para começar, o programa inicializa a `Interface`, que em seu construtor inicializa a tela em modo _curses_, cria as janelas necessárias e faz uma impressão de boas-vindas.

Em seguida, o programa verifica se um nome de arquivo PGN foi passado como argumento pela linha de comando. Se não for, usa `Interface::selecionarArquivo` para encontrar e listar os arquivos PGN no mesmo diretório do usuário, solicitando que o usuário digite um número correspondente a um dos arquivos.

Nos dois casos, se o nome informado na execução não existir ou nenhum PGN for encontrado no diretório, o programa usa `Interface::encerrarPrograma` para informar um erro e finalizar com a confirmação do usuário.

Do contrário, instancia um objeto `Partida` informando o nome desse arquivo a ser lido.

### Lendo o arquivo

O construtor da classe `Partida`, tenta ler um arquivo com o nome informado. Se ele não for encontrado ou não puder ser aberto, o programa também usa `Interface::encerrarPrograma` informando o erro.

Se o arquivo existir, ele é aberto e interpretado linha a linha. Primeiro são extraídos os dados extras do jogo, como o nome do evento e os nomes dos participantes, cada um para sua própria variável. Depois, o ponteiro do arquivo é passado para `Partida::_lerJogadas`, método responsável por extrair as jogadas e guardá-las em sequência num vetor.

Com os dados extras e o vetor de jogadas em mãos, é instanciado um objeto `Jogo`, dentro do objeto `Partida`, para guardar essas informações.

### Tabuleiro e vetores de captura

Ainda no objeto Partida, o tabuleiro, representado por uma matriz (ou vetor de vetores de strings, definido como `tabuleiro` usando um typedef para melhorar a legibilidade), é inicializado com as posições iniciais das peças dos dois jogadores.

Uma propriedade interna `_jogadaAtual` registra qual é o índice da jogada atual, começando em -1 (nenhuma jogada aplicada).

Os vetores de string `_capturadosBranco` e `_capturadosPreto`, inicialmente vazios, guardam as peças que já foram capturadas dos respectivos jogadores.

### Dados do jogo e tabuleiro e menu

De volta ao fluxo principal do programa, `Partida::preparar` é chamado. Nele,`Interface::imprimirJogo` é usado para imprimir os dados do jogo usando getters de `Partida` e `Jogo`. Com a confirmação do usuário para continuar pelo método `Interface::aguardarAcao`, o programa depois chama `Interface::comecar` para iniciar o jogo. A tela é apagada e o tabuleiro inicial é exibido usando `Interface::imprimirTabuleiro`. A partir daqui, a coleta de entrada será feita após cada ação, podendo o usuário optar por continuar, voltar, recomeçar ou sair, dependendo do momento do jogo.

### Executando a próxima jogada

Optando o usuário por continuar, o programa solicita que a próxima jogada sequencial seja aplicada usando o método `Partida::proximaJogada`.

Primeiro, a janela de informações é limpa usando `Interface::limparInformacoes`.

Antes de qualquer modificação, o tabuleiro e os vetores de peças capturadas atualmente são salvas em uma variável do struct `EstadoJogo`, que é salva no vetor `_estadosJogo` no índice correspondente a `_jogadaAtual + 1`, pois o estado de jogo 0 equivale à jogada -1 (nenhuma jogada)

Depois, o objeto `Partida` incrementa o índice `jogadaAtual` em 1, obtém a string da jogada correspondente em notação algébrica usando `Jogo::getJogada` e a separa em jogada do branco e jogada do preto.

Para cada jogada individual em NAP, ocorre a interpretação da string em `Partida::_aplicarJogada` para verificar qual peça foi movida e se houve captura ou cheque. O movimento da peça, de fato, ocorre em `Partida::_moverPeca`, para peças comuns, ou `Partida::_moverRoque`, para o caso de jogo especial roque. Em um dos dois últimos métodos citados também ocorre o preenchimento do vetor `_posDestaque`, que guarda as coordenadas de duas peças movidas na jogada atual, posteriormente passado para a impressão do tabuleiro.

A partir da coordenada algébrica do destino (ex. `e4`), são determinados os índices i,j do quadrado no tabuleiro usando `Partida::_encontrarIndices` e encontrada uma peça do tipo adequado que tenha movimento válido para esse destino, usando os métodos da classe Validador (ex. `Validador::peao_ `). Se houve captura, a peça atual da posição final é adicionada ao vetor de capturados correspondente. A peça adequada é então removida da posição anterior e colocada na posição final. No caso da torre, uma validação adicional com `Partida::_caminhoLivre` é necessária para encontrar a peça certa, sem bloqueios no caminho.

Nesse momento o programa pode solicitar a impressão do novo tabuleiro usando `Interface::imprimirTabuleiro`.

### Voltando jogadas

Quando o usuário opta por voltar, é usado o método `Partida::jogadaAnterior`.

Nele, é restaurado o estado de jogo de 2 jogadas atrás, decrementando `_jogadaAtual` em 2 e restaurando `_tabuleiro`, `_capturadosBranco` e `_capturadosPreto` de `_estadosJogo[_jogadaAtual + 1]`.

Por fim, é usado `Partida::proximaJogada` reaplicar a jogada imediatamente anterior à do início, reimprimindo as informações necessárias e registrando as capturas novamente, se houver.

Por causa da necessidade de voltar 2 jogadas, não é possível voltar para antes da jogada 1 (tabuleiro inicial). De qualquer forma, essa possibilidade foi considerada irrelevante pois o estado anterior (tabuleiro inicial) é conhecido e não é difícil identificar o que aconteceu com as informações da primeira jogada impressas.

### Fim das jogadas e resultado

Quando o usuário tenta avançar para uma jogada que não existe, dado por `Partida::_jogadaAtual >= Jogo::getJogadas::size`, é sinalizado o fim do jogo com `Partida::_acabou = true` para interromper o loop que repetia a sequência.

O resultado (quem venceu, ou empate) e as estatísticas do jogo (quantidade de jogadas e de capturas) são exibidas com `Interface::imprimirResultado`.

A entrada do usuário é coletada mais uma vez, recomeçando o jogo com `Partida::recomecar` ou encerrando o programa.

---

## Outras observações

### Impressão do tabuleiro

O tabuleiro é impresso usando somente caracteres ASCII comuns como `-` e `|` pois caracteres do ASCII extendido como `█` _(ALT + 219)_ não foram impressos corretamente
fora do Windows.

### Compatibilidade Linux-Windows

O programa foi desenvolvimento primariamente com a biblioteca `ncurses.h`, disponível no Linux. Para Windows, a biblioteca `PDCurses`, que disponibiliza um cabeçalho `curses.h` é em grande parte equivalente (totalmente, no caso deste programa). A biblioteca correta será incluida de acordo com o sistema onde acontece a compilação pelo uso de macros de plataforma `__linux__` e `_WIN32`. No Windows, o cabeçalho precisa estar em `PDCurses\curses.h`. Os macros também são utilizados para resolver uma diferença entre o uso de `CRLF` e `LF` entre os sistemas em `Partida::_lerJogadas`.

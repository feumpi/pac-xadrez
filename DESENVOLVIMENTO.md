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

## Fluxo do programa

### O início de tudo

Pra começar, o programa verifica se um nome de arquivo PGN foi passado como argumento pela linha de comando. Se não for, imprime a sintaxe esperada e encerra.

Se for, instancia um objeto `Partida` que recebe o nome desse arquivo.

### Lendo o arquivo

No construtor da classe `Partida`, é lido um arquivo com o nome informado. Se ele não for encontrado ou não puder ser aberto, o programa imprime um erro e cancela.

Se for, o arquivo é aberto e interpretado linha a linha. Primeiro são extraídos os dados extras do jogo, como o nome do evento e os nomes dos participantes. Depois, o ponteiro do arquivo é passado para outro método interno responsável por extrair as jogadas e guardá-las em sequência num vetor.

Com os dados extras e o vetor de jogadas em mãos, é instanciado um objeto `Jogo`, dentro do objeto `Partida`, para guardar essas informações.

### O tabuleiro

Ainda no objeto Partida, o tabuleiro, representado por uma matriz (ou vetor de vetores de strings), é inicializado com as posições iniciais das peças dos dois jogadores.

Uma propriedade interna `_jogadaAtual` registra qual é o índice da jogada atual, começando em -1 (nenhuma jogada aplicada).

### Interface

De volta ao fluxo principal do programa, um objeto `Interface` é criado para cuidar das impressões na tela, exibindo uma mensagem de boas-vindas.

O objeto `Jogo`, contendo os dados extras, e o tabuleiro, são obtidos usando getters de `Partida` e passados para a `Interface` cuidar das impressões iniciais.

### Executando a próxima jogada

Usando o método público `Partida::proximaJogada`, o programa solicita que a próxima jogada sequencial seja aplicada.

Quando isso acontece, o objeto Partida incrementa o índice `jogadaAtual` em 1, obtém a string da jogada correspondente em notação algébrica do vetor `Jogo::jogadas` e a separa em jogada do branco e jogada do preto.

Para cada jogada em NAP, ocorre a interpretação da string para verificar qual peça foi movida e se houve captura ou cheque.

A partir da coordenada algébrica do destino (ex. e4), são determinados os índices i,j do quadrado no tabuleiro e encontrada uma peça do tipo adequado que tenha movimento válido para esse destino, usando os métodos da classe Validador (ex. `Validador::peao_ `). A peça adequada é então removida da posição anterior e colocada na posição final.

Nesse momento o programa pode solicitar a impressão do novo tabuleiro usando `Interface::imprimirTabuleiro`.

---

## Sobre as classes

### Classe Jogo

Tem como propriedades os dados de um jogo, como o local e nomes dos jogadores, e também a sequência de jogadas em _NAP_.

### Classe Partida

Inicializa lendo os dados de um arquivo PGN e então instancia um objeto `Jogo` com eles. Contém também uma matriz que representa o tabuleiro com as posições das peças e é responsável por aplicar a próxima jogada e atualizá-lo.

### Classe Interface

Responsável pelas impressões na tela, como a formatação dos dados extras sobre um jogo e o desenho do tabuleiro. Também exibe uma mensagem de boas-vindas ao ser construída e uma mensagem final no encerramento.

### Classe Validador

Uma classe de métodos estáticos (ou seja, que não precisa ser instanciada) para validar o movimento de uma peça de acordo com as regras do xadrez, recebendo as posições final e inicial no tabuleiro e retornado `true`, para um movimento válido, ou `false`, para um movimento proibido.

---

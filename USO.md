### Universidade Federal do Espírito Santo

### INF09324 Programação Aplicada de Computadores 2021/1

### Primeiro trabalho

### Aluno: 2020205193 Felipe Pereira Umpierre

### Professor: Rodrigo Martins de Siqueira Barbosa

---

# Como utilizar este programa

Compile o código-fonte incluindo os arquivos **main.cpp**, **jogo.cpp**, **partida.cpp**, **interface.cpp** e **validador.cpp**, criando um executável **main.sh**:

```bash
> g++ main.cpp jogo.cpp partida.cpp interface.cpp validador.cpp -o main.sh
```

Execute o arquivo **main.sh** criado no passo anterior

```bash
> ./main.sh
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

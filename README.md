# Matchmaking System

## Descrição do Projeto

Este projeto implementa um sistema simples de **matchmaking** para jogos online competitivos.

O sistema é responsável por armazenar jogadores em uma fila de espera e formar grupos de jogadores com níveis de habilidade semelhantes, utilizando algoritmos de ordenação para facilitar a busca por partidas válidas.

Cada jogador possui:

- ID único
- Nome
- Score de habilidade
- Timestamp de entrada na fila

O sistema permite:

- Inserção de jogadores
- Remoção de jogadores
- Ordenação dos jogadores por score
- Formação de grupos válidos
- Recuperação da fila atual
- Exibição do estado da fila

---

## Estrutura do Projeto

O projeto foi organizado utilizando programação orientada a objetos e modularização em arquivos `.hpp` e `.cpp`.

A estrutura principal é:

```text
main.cpp
Matchmaking.hpp
Matchmaking.cpp
Player.hpp
Player.cpp
```

### Descrição dos Arquivos

- **Player.hpp / Player.cpp**
  
  Implementam a classe `Player`, responsável por representar um jogador da fila.

- **Matchmaking.hpp / Matchmaking.cpp**
  
  Implementam a classe `Matchmaking`, responsável pelo gerenciamento da fila de espera, ordenação e formação de grupos.

- **main.cpp**
  
  Contém todos os testes exigidos pelo trabalho.

---

## Organização Interna do Sistema

Os jogadores são armazenados em um array de tamanho fixo:

```cpp
Player players[MAX_PLAYERS];
```

A fila é gerenciada utilizando um tamanho lógico (`size`) que representa quantos jogadores estão atualmente armazenados.

Os algoritmos de ordenação implementados manualmente foram:

- Insertion Sort
- Merge Sort

A ordenação utiliza os seguintes critérios:

1. menor score
2. em caso de empate, menor timestamp

---

## Formação de Grupos

Antes da busca por grupos, os jogadores são ordenados por score.

Após a ordenação, o sistema percorre apenas grupos consecutivos do array, verificando se:

```text
maior_score - menor_score <= delta
```

Isso reduz significativamente a complexidade da busca por grupos válidos.

---

## Fluxo de Execução

O programa executa diversos casos de teste no `main.cpp`, incluindo:

1. Inserção de jogadores
2. Remoção de jogadores
3. Ordenação utilizando Insertion Sort
4. Ordenação utilizando Merge Sort
5. Ordenação com empate de score
6. Formação bem-sucedida de grupo
7. Tentativa de formação de grupo sem sucesso
8. Recuperação da fila usando `getWaitingPlayers`
9. Exibição do estado atual do sistema

---

## Instruções de Compilação

Para compilar o projeto, utilize:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```
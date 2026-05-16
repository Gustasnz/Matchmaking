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
compare.cpp
```

---
## Instruções de Compilação

Para compilar o projeto, utilize:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking && g++ compare.cpp Matchmaking.cpp Player.cpp -o compare
```

### Testes de Funcionamento e Desempenho

Após a compilação, para a execução dos testes de funcionamento do sistema (inserção e remoção de jogadores, ordenação das filas, etc.) basta efetuar:

```bash
./matchmaking
```
E para execução dos testes de desempenho entre o Insertion Sort e Merge Sort (testes de velocidade com base na quantidade de jogadores a serem ordenados), basta efetuar:
```bash
./compare
```

#include <iostream>
#include "Matchmaking.hpp"

using namespace std;

void printGroup(Player* group, int n) {
    cout << "Grupo:" << endl;
    if (group == nullptr) {
        cout << "Sem grupos...\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << "["
             << group[i].getId() << " | "
             << group[i].getName() << " | "
             << group[i].getScore() << " | "
             << group[i].getTimestamp() << "]\n";
    }
}

int main(){
    
    Matchmaking mm;

    // inserção dos jogadores
    mm.insert(Player(101, "MrK1ller", 1030, 1));
    mm.insert(Player(26, "DocHudson", 1100, 2));
    mm.insert(Player(842, "TheSBR", 1010, 3));
    mm.insert(Player(137, "FilipGamer", 1025, 4));
    cout << "\nAntes de ordenar (Insertion):\n";
    mm.printWaitingPlayers();

    // ordenação com insertion
    mm.sortByScoreInsertion();
    cout << "\nDepois de ordenar (Insertion):\n";
    mm.printWaitingPlayers();

    // formação de grupo
    int n;
    Player* group1 = mm.formGroup(3, 30, &n);
    cout << "\nGrupos formados:\n";
    printGroup(group1, n);
    delete[] group1;
    
    // remoção de jogadores
    cout << "\nJogadores esperando:\n";
    mm.printWaitingPlayers();
    mm.removePlayer(26);
    cout << "\nDepois de remover jogador da fila:\n";
    mm.printWaitingPlayers();

    // ordenação com merge (com empate)
    mm.insert(Player(51, "FredPvP", 1165, 5));
    mm.insert(Player(996, "Gersinho1997", 1090, 6));
    mm.insert(Player(171, "###--skull--###", 1240, 7));
    mm.insert(Player(462, "SkylineGTR", 1090, 8));
    cout << "\nNova fila antes de ordenar (Merge):\n";
    mm.printWaitingPlayers();
    mm.sortByScoreMerge();
    cout << "\nDepois de ordenar (Merge):\n";
    mm.printWaitingPlayers();

    // erro na formação de grupo
    Player* failed = mm.formGroup(3, 50, &n);
    cout << "\nGrupos formados:\n";
    printGroup(failed, n);
    delete[] failed;

    // uso do getWaitingPlayers
    Player* waiting = mm.getWaitingPlayers(&n);
    cout << "\nDescrição dos jogadores esperando:\n";
    for(int i = 0; i < n; i++){
        cout<< ">>> O player: "
            << waiting[i].getName() << " (com ID: "
            << waiting[i].getId() << " e TimeStamp: "
            << waiting[i].getTimestamp() << ") possui "
            << waiting[i].getScore() << " pontos\n";
    } delete[] waiting;

    return 0;
}
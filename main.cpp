#include <iostream>
#include "Matchmaking.hpp"

using namespace std;

void printGroup(Player* group, int n) {
    cout << "Grupo:" << endl;
    if (group == nullptr) {
        cout << "Sem grupos.\n";
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

int main() {
    Matchmaking matchmaking;
    matchmaking.insert(Player(1, "Alice", 1030, 1));
    matchmaking.insert(Player(2, "Bruno", 1100, 2));
    matchmaking.insert(Player(3, "Carla", 1010, 3));
    matchmaking.insert(Player(4, "Diego", 1025, 4));
    matchmaking.insert(Player(5, "Erdos", 1075, 5));
    matchmaking.insert(Player(6, "Fabio", 1053, 6));
    matchmaking.insert(Player(7, "Galio", 1055, 7));

    cout << "\nAntes do sort:\n";
    matchmaking.printWaitingPlayers();

    matchmaking.sortByScoreMerge();

    cout << "\nDepois do sort:\n";
    matchmaking.printWaitingPlayers();

    int n;
    Player* group1 = matchmaking.formGroup(3, 30, &n);
    Player* group2 = matchmaking.formGroup(3, 30, &n);
    cout << "\nGrupos formados:\n";
    printGroup(group1, n);
    printGroup(group2, n);

    delete[] group1;
    delete[] group2;

    cout << "\nJogadores esperando:\n";
    matchmaking.printWaitingPlayers();

    matchmaking.removePlayer(2);

    cout << "\nDepois de remover Bruno:\n";
    matchmaking.printWaitingPlayers();

    return 0;
}
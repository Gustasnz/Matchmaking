#include "Player.hpp"
const int MAX_PLAYERS = 100000;

class Matchmaking {

private:
    Player* players;
    int size;

public:
    Matchmaking();
    ~Matchmaking();

    bool insert(Player player);
    bool removePlayer(int id);
    void sortByScoreInsertion();
    void sortByScoreMerge();
    Player* formGroup(int groupSize, int delta, int* n);
    Player* getWaitingPlayers(int* n);
    void printWaitingPlayers();
};
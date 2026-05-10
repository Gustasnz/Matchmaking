#include <iostream>
#include "Matchmaking.hpp"
using namespace std;

Matchmaking::Matchmaking(){
    players = new Player[MAX_PLAYERS];
    size = 0;
}
Matchmaking::~Matchmaking(){
    delete[] players;
};

bool Matchmaking::insert(Player player){
    if (this->size < MAX_PLAYERS){
        this->players[size] = player;
        size++;
        return true;
    } return false;
}

bool Matchmaking::removePlayer(int id){
    for(int i=0; i<size; i++){
        Player curr = this->players[i];
        if (curr.getId()==id){
            for(int j=i; j<size-1; j++){
                this->players[j] = this->players[j+1];
            }
            size--;
            return true;
        }
    } return false;
}

void Matchmaking::sortByScoreInsertion(){
    if(this->size <= 1){return;}
    for (int i=1;i<size;i++){
        Player curr = this->players[i];
        int j = i-1;
        while(j >= 0 && (this->players[j].getScore() > curr.getScore() || (this->players[j].getScore() == curr.getScore() && this->players[j].getTimestamp() > curr.getTimestamp()))){
            this->players[j+1] = this->players[j];
            j--;
        } this->players[j+1] = curr;
    }
}

Player* MergeSort(Player arr[],int n){
    if(n <= 1){
        Player* base = new Player[1];
        if (n == 1) base[0] = arr[0];
        return base;
    }
    int mid = n/2;
    Player* left = MergeSort(arr, mid);
    Player* right = MergeSort(arr + mid, n - mid);
    int i = 0, j = 0, k = 0;
    Player* merged = new Player[n];
    while(i < mid && j < n-mid){
        if (left[i].getScore() < right[j].getScore() || (left[i].getScore() == right[j].getScore() && left[i].getTimestamp() < right[j].getTimestamp())){
            merged[k] = left[i];
            i++;
        }
        else {
            merged[k] = right[j];
            j++;
        } k++;
    }
    while(i < mid){
        merged[k++] = left[i++];
    }
    while(j < n - mid){
        merged[k++] = right[j++];
    }
    delete[] left;
    delete[] right;
    return merged;
}

void Matchmaking::sortByScoreMerge(){
    if(this->size<=1){return;}
    Player* sorted = MergeSort(this->players,size);
    for(int i=0; i < size; i++){
        this->players[i] = sorted[i];
    } delete[] sorted;
}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n) {
    *n = 0;

    if (size < groupSize) return nullptr;

    sortByScoreMerge(); // IMPORTANT: ensure sorted state

    for (int i = 0; i <= size - groupSize; i++) {

        int minScore = players[i].getScore();
        int maxScore = players[i + groupSize - 1].getScore();

        if (maxScore - minScore <= delta) {

            Player* group = new Player[groupSize];

            for (int j = 0; j < groupSize; j++) {
                group[j] = players[i + j];
            }

            // SHIFT LEFT SAFELY
            for (int j = i; j < size - groupSize; j++) {
                players[j] = players[j + groupSize];
            }

            size -= groupSize;
            *n = groupSize;

            return group;
        }
    }

    return nullptr;
}

Player* Matchmaking::getWaitingPlayers(int* n){
    if(this->size == 0){
        *n = 0;
        return nullptr;
    }
    *n = this->size;
    Player* copy = new Player[size];
    for (int i = 0; i < size; i++) {
        copy[i] = this->players[i];
    } return copy;
};

void Matchmaking::printWaitingPlayers(){
    cout << "Waiting Players:\n";
    if (size == 0) {
        cout << "No players...\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        cout
            << "["
            << players[i].getId() << " | "
            << players[i].getName() << " | "
            << players[i].getScore() << " | "
            << players[i].getTimestamp()
            << "]\n";
    }
};
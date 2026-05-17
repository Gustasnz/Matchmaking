#include <iostream>
#include "Matchmaking.hpp"
using namespace std;

Matchmaking::Matchmaking(){
    players = new Player[MAX_PLAYERS];
    size = 0; // inicializa o tamanho da fila com 0 players
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
            for(int j=i; j<size-1; j++){ // desloca os players à frente do que foi removido para a esquerda, preenchendo o espaço vazio
                this->players[j] = this->players[j+1];
            }
            size--;
            return true;
        }
    } return false;
}

void Matchmaking::sortByScoreInsertion(){
    if(this->size <= 1){return;} // arrays de tamanho 0 ou 1 já estão ordenados
    for (int i=1;i<size;i++){
        Player curr = this->players[i];
        int j = i-1;
        // aqui deslocamos o player atual para a direita até o caso de parada (verificando todos os casos em que o player atual deve vir antes do player na posição players[j])
        while(j >= 0 && (this->players[j].getScore() > curr.getScore() || (this->players[j].getScore() == curr.getScore() && this->players[j].getTimestamp() > curr.getTimestamp()))){
            this->players[j+1] = this->players[j];
            j--;
        } this->players[j+1] = curr;
    }
}

Player* MergeSort(Player arr[],int n){ // função auxiliar para fazer o merge sort
    if(n <= 1){ // caso base da recursão
        Player* base = new Player[1];
        if (n == 1) base[0] = arr[0];
        return base;
    }
    int mid = n/2;
    Player* left = MergeSort(arr, mid); // ordena recursivamente à esquerda
    Player* right = MergeSort(arr + mid, n - mid); // ordena recursivamente à direita
    int i = 0; // indice que percorre à esquerda
    int j = 0; // indice que percorre à direita
    int k = 0; // indice que percorre o array final
    Player* merged = new Player[n];
    // enquanto existirem players nas duas metades, escolhemos o player (da esquerda ou da direita) que deve entrar primeiro no array final ordenado
    while(i < mid && j < n-mid){
        if (left[i].getScore() < right[j].getScore() || (left[i].getScore() == right[j].getScore() && left[i].getTimestamp() < right[j].getTimestamp())){
            merged[k] = left[i];
            i++; // player à esquerda entra primeiro
        }
        else {
            merged[k] = right[j];
            j++; // player à direita entra primeiro
        } k++; // próxima posição do array final
    }
    // copiamos elementos que possivelmente tenham sobrado à esquerda e/ou à direita
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
    if(this->size<=1){return;} // arrays de tamanho 0 ou 1 já estão ordenados
    Player* sorted = MergeSort(this->players,size);
    for(int i=0; i < size; i++){ // copia o resultado ordenado para o array principal
        this->players[i] = sorted[i];
    } delete[] sorted;
}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n) {
    *n = 0; // número de players no grupo a ser criado
    if (size < groupSize) return nullptr; // não foi possivel gerar grupo
    sortByScoreMerge(); // deixa o array ordenado para formação dos grupos
    for (int i = 0; i <= size - groupSize; i++) { // percorre todas as janelas consecutivas possíveis de tamanho groupSize
        int minScore = players[i].getScore(); // primeiro player do grupo
        int maxScore = players[i + groupSize - 1].getScore(); // último player do grupo
        if (maxScore - minScore <= delta) { // se houver uma sequência de players que satisfaz o delta, cria o grupo
            Player* group = new Player[groupSize];
            for (int j = 0; j < groupSize; j++) {
                group[j] = players[i + j];
            }
            for (int j = i; j < size - groupSize; j++) { // preenche o espaço vazio deixado pelo grupo que se formou
                players[j] = players[j + groupSize];
            }
            size -= groupSize;
            *n = groupSize;
            return group;
        }
    } return nullptr;
}

Player* Matchmaking::getWaitingPlayers(int* n){
    if(this->size == 0){
        *n = 0;
        return nullptr;
    }
    *n = this->size;
    Player* copy = new Player[size];
    for (int i = 0; i < size; i++) { // cria uma cópia com os players que estão na fila
        copy[i] = this->players[i];
    } return copy;
};

void Matchmaking::printWaitingPlayers(){
    if (size == 0) {
        cout << "Sem jogadores...\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        cout
            << "["
            << players[i].getId() << " | "
            << players[i].getName() << " | "
            << players[i].getScore() << " | "
            << players[i].getTimestamp() << "]\n";
    }
};
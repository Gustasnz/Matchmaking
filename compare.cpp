#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Matchmaking.hpp"

#include <chrono>
int main() {

    std::cout << "START\n";

    srand(time(NULL)); 

    Matchmaking mmMerge;
    Matchmaking mmInsert;
    int sizes[] = {100, 500, 1000, 5000, 10000};
    for (int j=0;j<5;j++){
    for(int i = 0; i < sizes[j]; i++) {
        int id = i + 1;
        std::string name = "Player" + std::to_string(id);
        int score = rand() % 2000 + 1000; 
        int timestamp = rand() % 1000; 
        mmMerge.insert(Player(id, name, score, timestamp));
        mmInsert.insert(Player(id, name, score, timestamp));
    }

    auto start = std::chrono::high_resolution_clock::now();
    mmMerge.sortByScoreMerge();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\nTIME OF MERGE_SORT for "<<sizes[j]<<" players:\n";
    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << ms.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    mmInsert.sortByScoreInsertion();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "\nTIME OF INSERTION_SORT for " <<sizes[j]<<" players:\n";
    std::chrono::duration<double, std::milli> msg = end - start;
    std::cout << msg.count() << " ms\n";
}

   

    return 0;
}
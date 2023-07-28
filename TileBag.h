#ifndef TILEBAG_H
#define TILEBAG_H 

#include "Tile.h"
#include "LinkedList.h"
#include <iostream>
#include <random>


class TileBag {
public:
    TileBag();
    // Pass any boolean to construct an empty tileBag
    TileBag(bool empty);
    ~TileBag();

    Tile* getFront();
    void deleteFront();
    void addToBack(Tile* tile);
    std::string getTileBagAsString();
    bool isEmpty();

private:
    std::random_device engine;
    // Seeded random engine
    //std::defaul_random_engine engine(10);
    
    LinkedList* tileBag;
};

#endif // TILEBAG_H

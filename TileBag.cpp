#include "TileBag.h"
#include "TileCodes.h"


// Constructor for a full tile bag
TileBag::TileBag() {
    tileBag = new LinkedList();
    LinkedList* temp = new LinkedList();
    // Add two of each tile to a temporary linked list
    for (int i = 0; i < NUM_OF_COLOURS; i++) {
        for (int j = 0; j < NUM_OF_SHAPES; j++) {
            temp->addBack(new Tile(colours[i], shapes[j]));
            temp->addBack(new Tile(colours[i], shapes[j])); //2 of each tile
        }
    }
    int min = 0;
    int max = 2*NUM_OF_COLOURS*NUM_OF_SHAPES-1;
    
    // Randomly add the tiles to the tilebag
    for (int i = 0; i < max; max--) {
        std::uniform_int_distribution<int> uniformDist(min, max);
        int value = uniformDist(engine);
        tileBag->addBack(new Tile(*temp->get(value)));
        temp->deleteAt(value);
    }
    delete temp;
}

// Constructor for an empty tile bag
TileBag::TileBag(bool empty) {
    tileBag = new LinkedList();
}

// Destructor
TileBag::~TileBag() {
    delete tileBag;
}

// Get the front at the front of the tile bag 
Tile* TileBag::getFront() {
    return tileBag->get(0);
}

// Delete the tile at the front of the tile bag
void TileBag::deleteFront() {
    tileBag->deleteAt(0);
}

// Add tile to the back of the tile bag
void TileBag::addToBack(Tile* tile) {
    tileBag->addBack(tile);
}

// Get the tile bag as string representation
std::string TileBag::getTileBagAsString() {
    std::string tileBagString;
    for (int i = 0; i < tileBag->size(); i++) {
        tileBagString += tileBag->get(i)->getColour() + std::to_string(tileBag->get(i)->getShape()) + ",";
    }
    return tileBagString.substr(0,tileBagString.size()-1);
}

bool TileBag::isEmpty() {
    return tileBag->size() == 0;
}
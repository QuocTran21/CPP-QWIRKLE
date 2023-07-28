#ifndef PLAYER_H
#define PLAYER_H

#include "LinkedList.h"
#include <iostream>

class Player {
public:
    Player(std::string name);
    ~Player();

    std::string getName();
    void addToBackOfHand(Tile* tile);
    void addScore(int points);
    int getScore();
    Tile* getTile(std::string tileCode);
    Tile* getTile(int index);
    std::string getHandAsString();

    bool tileInHand(std::string tileCode);
    void deleteTile(std::string tileCode);
    int handSize();
    bool handIsEmpty();
    void printHand();

private:
    std::string name;
    LinkedList* hand;
    int score;
    
    void drawUnicode(char tileColour, std::string tileShape);
};
#endif // PLAYER_H

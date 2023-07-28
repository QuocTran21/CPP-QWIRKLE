#include "Player.h"

#define RESET               "\033[0m"
#define RED                 "\033[31m"
#define ORANGE              "\033[38;5;203m"
#define YELLOW              "\033[33m"
#define GREEN               "\033[32m"
#define BLUE                "\033[34m"
#define PURPLE              "\033[38;5;93m"

#define CIRCLE_UNICODE      "\u25CF"
#define STAR_4_UNICODE      "\u2726"
#define DIAMOND_UNICODE     "\u2666"
#define SQUARE_UNICODE      "\u25A0"
#define STAR_6_UNICODE      "\u2736"
#define CLOVER_UNICODE      "\u2663"



// Constructor
Player::Player(std::string name) {
    this->name = name;
    score = 0;
    hand = new LinkedList();
}

// Destructor
Player::~Player() {
    delete hand;
}

// Get the name of the player
std::string Player::getName() {
    return name;
}

// Add the tile to the back of hand
void Player::addToBackOfHand(Tile* tile) {
    hand->addBack(tile);
}

// Add point to score
void Player::addScore(int points) {
    score += points;
}

// Get the score
int Player::getScore() {
    return score;
}

// Get the tile by tile code
Tile* Player::getTile(std::string tileCode) {
    int index = 0;
    for (int i = 0; i < hand->size(); i++) {
        if (tileCode == hand->get(i)->getColour() + std::to_string(hand->get(i)->getShape())) {
            index = i;
        }
    }
    return hand->get(index);
}

// Get the tile by index
Tile* Player::getTile(int index) {
    return hand->get(index);
}

// Get all tile in the hand as string representation
std::string Player::getHandAsString() {
    std::string handString;
    for (int i = 0; i < hand->size(); i++) {
        handString += hand->get(i)->getColour() + std::to_string(hand->get(i)->getShape()) + ",";
    }
    return handString.substr(0,handString.size()-1);
}

void Player::printHand() {
    for (int i = 0; i < hand->size(); i++) {
        drawUnicode(hand->get(i)->getColour(), std::to_string(hand->get(i)->getShape()));
        if (i < hand->size()-1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl << std::endl;
}

// Check if the tile is in hand
bool Player::tileInHand(std::string tileCode) {
    bool inHand = false;
    for (int i = 0; i < hand->size(); i++) {
        if (tileCode == hand->get(i)->getColour() + std::to_string(hand->get(i)->getShape())) {
            inHand = true;
        }
    }
    return inHand;
}

// Delete the tile
void Player::deleteTile(std::string tileCode) {
    bool deleted = false;
    for (int i = 0; i < hand->size(); i++) {
        if (tileCode == hand->get(i)->getColour() + std::to_string(hand->get(i)->getShape()) && !deleted) {
            hand->deleteAt(i);
            deleted = true; //to prevent a double getting deleted
        }
    }
}

int Player::handSize() {
    return hand->size();
}

bool Player::handIsEmpty() {
    return hand->size() == 0;
}

void Player::drawUnicode(char tileColour, std::string tileShape) {
    std::string colour;
    std::string shape;
    if (tileColour == 'R') {
        colour = RED;
    } else if (tileColour == 'O') {
        colour = ORANGE;
    } else if (tileColour == 'Y') {
        colour = YELLOW;
    } else if (tileColour == 'G') {
        colour = GREEN;
    } else if (tileColour == 'B') {
        colour = BLUE;
    } else if (tileColour == 'P') {
        colour = PURPLE;
    }
    if (tileShape == "1") {
        shape = CIRCLE_UNICODE;
    } else if (tileShape == "2") {
        shape = STAR_4_UNICODE;
    } else if (tileShape == "3") {
        shape = DIAMOND_UNICODE;
    } else if (tileShape == "4") {
        shape = SQUARE_UNICODE;
    } else if (tileShape == "5") {
        shape = STAR_6_UNICODE;
    } else if (tileShape == "6") {
        shape = CLOVER_UNICODE;
    }

    std::cout << colour << shape << RESET << "[" << tileColour << tileShape << "]";
}
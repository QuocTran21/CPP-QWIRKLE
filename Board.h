#ifndef BOARD_H
#define BOARD_H 

#include <vector>
#include <string> 
#include <iostream>

#define BOARD_DIMENSION     26
#define BOARD_EDGE          "Q2C"

#define RESET               "\033[0m"
#define RED                 "\033[31m"
#define ORANGE              "\033[38;5;202m"
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

class Board {
public:
    Board(int boardDimension);
    ~Board();
    // Check tile is placed at a valid location
    bool isValidMove(std::string tile, std::string position);
    void placeTileOnSquare(std::string tile, std::string position);
    // Return board state as a string for save file
    std::string getBoardStateAsString();
    int getBoardDimension();
    void printBoard();
    // Check if there are same coloured tiles to left and right
    bool checkRows(std::string tile, std::string position);
    // Check if there are same shaped tiles above and below
    bool checkColumns(std::string tile, std::string position);
    // Check if there are both vertical and horizontal neighbours
    bool hasVerticalAndHorizontalNeighbours(std::string position);
    // Scane entire board for possible moves
    bool checkAllValidMoves(std::string tile);
    int getPoints();
    void resetPoints();
    bool isQuirkle();
    void resetQuirkle();
    std::string getHint();
    void resetHintPoints();
    int getHintPoints();
    bool getIsEmpty();

private:
    int boardDimension;
    int getRowIndex(char rowLabel);
    bool isEmpty;
    void drawUnicode(std::string tileColour, std::string tileShape);
    
    int points = 0;
    int hintPoints = 0;
    std::string hint;
    bool quirkle = false;
    
    std::vector<std::vector<std::string>> board;
};

#endif // BOARD_H

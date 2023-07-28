#include "Board.h"


// Constructor
// Creates an empty board with a board edge all around it which is used to check edge cases
Board::Board(int boardDimension) {
    this->boardDimension = boardDimension;
    std::vector<std::string> firstRow;
    for (int i = 0; i < boardDimension+2; i++) {
        firstRow.push_back(BOARD_EDGE);
    }
    board.push_back(firstRow);

    for (int i = 0; i < boardDimension; i++) {
        std::vector<std::string> row;
        row.push_back(BOARD_EDGE);
        for (int j = 0; j < boardDimension; j++) {
            row.push_back("  ");
        }
        row.push_back(BOARD_EDGE);
        board.push_back(row);
    }
    std::vector<std::string> finalRow;
    for (int i = 0; i < boardDimension+2; i++) {
        finalRow.push_back(BOARD_EDGE);
    }
    board.push_back(finalRow);
    isEmpty = true;
}

// Destructor
Board::~Board() {
    for (int i = 0; i < boardDimension+2; i++) {
        board[i].clear();
    }
    board.clear();
}

// Check if the move is valid
bool Board::isValidMove(std::string tile, std::string position) {
    int rowIndex = getRowIndex(position[0])+1;
    int colIndex = std::stoi(position.substr(1))+1;

    bool isValid = false;
    if (rowIndex >= 1 && rowIndex <= boardDimension+1 && colIndex >= 1 && 
        colIndex <= boardDimension+1 && board[rowIndex][colIndex] == "  ") {
        if (!isEmpty) { // Check surrounding tiles
            if (hasVerticalAndHorizontalNeighbours(position)){
                if (checkRows(tile, position) && checkColumns(tile, position)) {
                    isValid = true;
                }
            } else if (checkRows(tile, position)) {
                isValid = true;
            } else if (checkColumns(tile, position)) {
                isValid = true;
            }

        } else { // First tile placement of game
            isValid = true;
            points++;
        }
    }

    return isValid;
}

// Place the tile on the square
void Board::placeTileOnSquare(std::string tile, std::string position) {
    int rowIndex = getRowIndex(position[0])+1;
    int colIndex = std::stoi(position.substr(1))+1;

    board[rowIndex][colIndex] = tile;
    isEmpty = false;
}

// Get the board state as string representation
std::string Board::getBoardStateAsString()
{
    std::string boardState = "";
    char letter = 'A';
    for (int i = 1; i <= boardDimension; i++) {
        for (int j = 1; j <= boardDimension; j++) {
            if (board[i][j] != "  ") {
                boardState += board[i][j] + "@" + letter + std::to_string(j-1) + ",";
            }
        }
        letter++;
    }
    return boardState.substr(0, boardState.size() - 1);
}

// Get the dimension of the board
int Board::getBoardDimension() {
    return boardDimension;
}

// Display the board
void Board::printBoard() {
    std::string topLabel = "   ";
    std::string topLine = "  _";
    for (int i = 0; i < boardDimension; i++) {
        topLabel += (std::to_string(i) + "  ").substr(0, 3);
        topLine += "___";
    }

    std::cout << topLabel << std::endl;
    std::cout << topLine << std::endl;

    char letter = 'A';
    for (int i = 1; i <= boardDimension; i++) {
        std::cout << letter << " |";
        for (int j = 1; j <= boardDimension; j++) {
    
            if (board[i][j] != "  ") {
                drawUnicode(board[i][j].substr(0,1),board[i][j].substr(1));
            } else {
                std::cout << board[i][j] << "|";
            }
        }
        std::cout << std::endl;
        letter++;
    }
    std::cout << std::endl;
}

// Get the row index of the row label
int Board::getRowIndex(char rowLabel) {
    char letter = 'A';

    int rowIndex = -1;
    for (int i = 0; i < boardDimension; i++) {
        if (rowLabel == letter) {
            rowIndex = i;
        }
        letter++;
    }
    return rowIndex;
}

// Check rows
bool Board::checkRows(std::string tile, std::string position) {
    int rowIndex = getRowIndex(position[0]) + 1;
    int colIndex = std::stoi(position.substr(1)) + 1;

    std::vector<std::string> rowOfNeighbours; // Vector to store same colour tiles

    if (board[rowIndex][colIndex-1] != BOARD_EDGE && board[rowIndex][colIndex-1] != "  " && 
        board[rowIndex][colIndex+1] != BOARD_EDGE && board[rowIndex][colIndex+1] != "  ") // Tiles on left and right
    {
        while (board[rowIndex][colIndex-1] != BOARD_EDGE && board[rowIndex][colIndex-1] != "  ") { // Add tiles to left with same colour in vector
            rowOfNeighbours.push_back(board[rowIndex][colIndex-1]);
            colIndex--; 
        }

        int colIndex = std::stoi(position.substr(1)) + 1; // Reset col index to move right

        while (board[rowIndex][colIndex+1] != BOARD_EDGE && board[rowIndex][colIndex+1] != "  ") { // Add tiles to right in vector
            rowOfNeighbours.push_back(board[rowIndex][colIndex+1]);
            colIndex++; 
        }
    }
    else if (board[rowIndex][colIndex+1] != BOARD_EDGE && board[rowIndex][colIndex+1] != "  ")// Only tiles on right
    {
        while (board[rowIndex][colIndex+1] != BOARD_EDGE && board[rowIndex][colIndex+1] != "  ") { 
            rowOfNeighbours.push_back(board[rowIndex][colIndex+1]);
            colIndex++; 
        }
    }
    else if (board[rowIndex][colIndex-1] != BOARD_EDGE && board[rowIndex][colIndex-1] != "  ") // Only tiles on left
    {
        while (board[rowIndex][colIndex-1] != BOARD_EDGE && board[rowIndex][colIndex-1] != "  ") { 
            rowOfNeighbours.push_back(board[rowIndex][colIndex-1]);
            colIndex--; 
        }
    }

    bool validMove = false; 
    if (rowOfNeighbours.size() > 0 && rowOfNeighbours.size() < 6) { // Check there are not more than 6 in a row
        validMove = true;
        for (int i = 0; i < rowOfNeighbours.size(); i++) {
            if (rowOfNeighbours[i][0] != tile[0]) { // Check they are all same colours
                validMove = false;
            }
            if (rowOfNeighbours[i][1] == tile[1]) { // Check they are all different shapes
                validMove = false;
            }
        }
        if (validMove) {
            if (rowOfNeighbours.size() == 5) { // Five tiles in a row plus placed tile is quirkle
                quirkle = true;
                points += 6;
            } else {
                points += rowOfNeighbours.size() + 1; // Number of tiles next to placed tile plus itself
            }
        }
    }
    return validMove;
}

// Check columns
bool Board::checkColumns(std::string tile, std::string position) {
    int rowIndex = getRowIndex(position[0]) + 1;
    int colIndex = std::stoi(position.substr(1)) + 1;

    std::vector<std::string> colsOfNeighbours; // Vector to store same shaped tiles

    if (board[rowIndex+1][colIndex] != BOARD_EDGE && board[rowIndex+1][colIndex] != "  " && 
        board[rowIndex-1][colIndex] != BOARD_EDGE && board[rowIndex-1][colIndex] != "  ") // Tiles above and below
    {
        while (board[rowIndex+1][colIndex] != BOARD_EDGE && board[rowIndex+1][colIndex] != "  ") { // Add tiles below in vector
            colsOfNeighbours.push_back(board[rowIndex+1][colIndex]);
            rowIndex++; 
        }

        int rowIndex = getRowIndex(position[0]) + 1; // Reset row index to move up

        while (board[rowIndex-1][colIndex] != BOARD_EDGE && board[rowIndex-1][colIndex] != "  ") { // Add tiles above in vector
            colsOfNeighbours.push_back(board[rowIndex-1][colIndex]);
            rowIndex--; 
        }
    }
    else if (board[rowIndex+1][colIndex] != BOARD_EDGE && board[rowIndex+1][colIndex] != "  ")// Only tiles below
    {
        while (board[rowIndex+1][colIndex] != BOARD_EDGE && board[rowIndex+1][colIndex] != "  ") {
            colsOfNeighbours.push_back(board[rowIndex+1][colIndex]);
            rowIndex++; 
        }
    }
    else if (board[rowIndex-1][colIndex] != BOARD_EDGE && board[rowIndex-1][colIndex] != "  ") // Only tiles above
    {
        while (board[rowIndex-1][colIndex] != BOARD_EDGE && board[rowIndex-1][colIndex] != "  ") {
            colsOfNeighbours.push_back(board[rowIndex-1][colIndex]);
            rowIndex--; 
        }
    }

    bool validMove = false;
    if (colsOfNeighbours.size() > 0 && colsOfNeighbours.size() < 6) {
        validMove = true;
        for (int i = 0; i < colsOfNeighbours.size(); i++) {
            if (colsOfNeighbours[i][1] != tile[1]) { // Check they are all the same shape
                validMove = false;
            }
        }
        for (int i = 0; i < colsOfNeighbours.size(); i++) {
            if (colsOfNeighbours[i][0] == tile[0]) { // Check they all different colour
                validMove = false;
            }
        }
        if (validMove) {
            if (colsOfNeighbours.size() == 5) {
                quirkle = true;
                points += 6;
            } else {
                points += colsOfNeighbours.size() + 1;
            }
        }
    }
    return validMove;
}

// Check if the position has vertical and horizontal neighbours
bool Board::hasVerticalAndHorizontalNeighbours(std::string position) {
    int rowIndex = getRowIndex(position[0]) + 1;
    int colIndex = std::stoi(position.substr(1)) + 1;

    bool hasVertAndHoriNeighbour = false;
    // Check left and down
    if (board[rowIndex][colIndex-1] != BOARD_EDGE && board[rowIndex][colIndex-1] != "  " && 
        board[rowIndex+1][colIndex] != BOARD_EDGE && board[rowIndex+1][colIndex] != "  ") {
        hasVertAndHoriNeighbour = true;
    }
    // Check left and up
    if (board[rowIndex][colIndex-1] != BOARD_EDGE && board[rowIndex][colIndex-1] != "  " && 
        board[rowIndex-1][colIndex] != BOARD_EDGE && board[rowIndex-1][colIndex] != "  ") {
        hasVertAndHoriNeighbour = true;
    }
    // Check right and down
    if (board[rowIndex][colIndex+1] != BOARD_EDGE && board[rowIndex][colIndex+1] != "  " && 
        board[rowIndex+1][colIndex] != BOARD_EDGE && board[rowIndex+1][colIndex] != "  ") {
        hasVertAndHoriNeighbour = true;
    }
    // Check right and up
    if (board[rowIndex][colIndex+1] != BOARD_EDGE && board[rowIndex][colIndex+1] != "  " && 
        board[rowIndex-1][colIndex] != BOARD_EDGE && board[rowIndex-1][colIndex] != "  ") {
        hasVertAndHoriNeighbour = true;
    }

    return hasVertAndHoriNeighbour;
}

// Scan entire board for possible moves
// Also used to detect highest score possible for hints and AI move
bool Board::checkAllValidMoves(std::string tile) {
    std::string maxTile;
    std::string maxPosition;
    bool isValid = false;
    char letter = 'A';
    for (int i = 0; i < boardDimension; i++) {
        for (int j = 0; j < boardDimension; j++) {
            std::string position = std::string(1,letter) + std::to_string(j);
            if (isValidMove(tile,position)) {
                isValid = true;
                if (points > hintPoints) {
                    hintPoints = points;
                    maxTile = tile;
                    maxPosition = position;
                    hint = "place " + maxTile + " at " + maxPosition + " for " + std::to_string(hintPoints) + " points";
                }
            } 
            points = 0;
        }
        letter++;
    }

    if (isEmpty) {
        hint = "It is a fresh start. Go wherever your heart desires";
    }
    else if (hintPoints == 0) {
        hint = "There are no possible moves with your hand. Replace a tile from your hand";
    }
    return isValid;
}

int Board::getPoints() {
    return points;
}

void Board::resetPoints() {
    points = 0;
}

bool Board::isQuirkle() {
    return quirkle;
}

void Board::resetQuirkle() {
    quirkle = false;
}

void Board::drawUnicode(std::string tileColour, std::string tileShape) {
    std::string colour;
    std::string shape;
    if (tileColour == "R") {
        colour = RED;
    } else if (tileColour == "O") {
        colour = ORANGE;
    } else if (tileColour == "Y") {
        colour = YELLOW;
    } else if (tileColour == "G") {
        colour = GREEN;
    } else if (tileColour == "B") {
        colour = BLUE;
    } else if (tileColour == "P") {
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

    std::cout << colour << shape << RESET << " |";
}

std::string Board::getHint() {
    return hint;
}

void Board::resetHintPoints() {
    hintPoints = 0;
}

int Board::getHintPoints() {
    return hintPoints;
}

bool Board::getIsEmpty() {
   return isEmpty;
}
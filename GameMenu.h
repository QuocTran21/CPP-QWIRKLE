#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "LinkedList.h"
#include "Player.h"
#include "TileBag.h"
#include "Board.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <map>

#define NUM_OF_TILES_IN_HAND     6
#define TILEBAG_SIZE             72
#define EXIT_SUCCESS             0

class GameMenu{

public:
    GameMenu();
    ~GameMenu();
    // Display menu options
    void menu(bool &exit);

private:
    std::string numberOfPlayers;
    // Perform specific feature for each option chose in the menu
    void newGame(bool &exit);
    void loadGame(bool &exit);
    // As game is created, keep it running until a specific condition is met
    void playGame(std::vector<Player*> players, TileBag* tileBag, Board* board, int playersTurnIndex);
    // Perform specific action when coming to a player turn
    void playersTurn(Player* player, Board* board, TileBag* tileBag, bool &playing, std::vector<Player*> players);
    void completeTurn(Player* player, Board* board, TileBag* tileBag, bool &playersTurn, bool &playing, std::vector<Player*> players, std::string tile, std::string location);
    void replaceTile(Player* player, TileBag* tileBag, std::string tile, bool &playersTurn);
    // Display game over message and winner
    void gameOver(std::vector<Player*> players);
    // Check integer
    bool isInt(std::string string);
    // Check character
    bool isAlphabetic(std::string string);
    // Check uppercase
    bool isUpper(std::string string);
    // Tokenizing a string
    std::vector<std::string> splitToTokens(std::string string, char delimiter);
    // Check file to load is correct format
    bool isCorrectFormat(std::string fileName);
    bool checkTileFormat(std::string tile);
    bool checkGridFormat(std::string grid);
    bool checkEOF(bool &exit);
    void checkEmptyInput(std::string &input);
    void checkInputIsHelp(std::string input, std::string check);
    void credits();
    void highScores();
    void writeToHighScore(std::vector<Player*> players);
    static bool sortByVal(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b);
};

#endif // GAMEMENU_H

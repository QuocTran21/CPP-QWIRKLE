#include "GameMenu.h"


GameMenu::GameMenu(){
}
GameMenu::~GameMenu(){
}
void GameMenu::menu(bool &exit) {
   std::cout << "Menu" << std::endl;
   std::cout << "----" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Credits" << std::endl;
   std::cout << "4. Quit" << std::endl;
   std::cout << "5. High Scores" << std::endl << std::endl << "> ";
   
   std::string menuInput;
   std::getline(std::cin, menuInput);
   checkEmptyInput(menuInput);
   checkInputIsHelp(menuInput, "menu");
   if (checkEOF(exit)) {} //Exit
   else {
      while ((!(isInt(menuInput)) || std::stoi(menuInput) < 1 || std::stoi(menuInput) > 5) && !exit) { //Reprompt if not valid input
         if (menuInput != "help") {
            std::cout << "Not a valid menu option" << std::endl << "> ";
         }
         std::getline(std::cin, menuInput);
         checkEmptyInput(menuInput);
         checkInputIsHelp(menuInput, "menu");
         if (checkEOF(exit)) {} //Exit
      }

      if (!exit) {
         if (std::stoi(menuInput) == 1) {
            newGame(exit);
         } else if (std::stoi(menuInput) == 2) {
            loadGame(exit);
         } else if (std::stoi(menuInput) == 3) {
            credits();
         } else if (std::stoi(menuInput) == 4) {
            exit = true;
         } else if (std::stoi(menuInput) == 5) {
            highScores();
         }
      }
   }
}

void GameMenu::newGame(bool &exit) {
   bool newGame = true;
   // Keep displaying new game message until players, board are properly created or user quit the game
   while (newGame)
   {
      std::cout << std::endl << "How many players?" << std::endl << "> ";
      std::getline(std::cin, numberOfPlayers);
      checkEmptyInput(numberOfPlayers);
      checkInputIsHelp(numberOfPlayers, "playerNumberSelection");
      if (checkEOF(exit)) {
         newGame = false; // Exit
      }
      else {
         while (!(isInt(numberOfPlayers) && !(std::stoi(numberOfPlayers) < 1 || std::stoi(numberOfPlayers) > 4)) && !exit) {
            if (numberOfPlayers != "help") {
               std::cout << "Please select 1, 2, 3 or 4 players" << std::endl << "> ";
            }
            std::getline(std::cin, numberOfPlayers);
            checkEmptyInput(numberOfPlayers);
            checkInputIsHelp(numberOfPlayers, "playerNumberSelection");
            if (checkEOF(exit)) {
               newGame = false; 
            }
         }
      }
      if (newGame) {
         std::cout << std::endl << "Starting a New Game" << std::endl;
         std::string playerNames[std::stoi(numberOfPlayers)];
         // Only allow uppercase
         std::regex regexPattern("[A-Z]+");
         
         int playerIndex = 1;
         bool isDuplicate = false;
         while (playerIndex <= std::stoi(numberOfPlayers) && newGame) {
            if (!isDuplicate) {
               std::cout << std::endl << "Enter a name for player " << playerIndex << std::endl << "> ";
            }
            isDuplicate = false;
            std::string playerName;
            std::getline(std::cin, playerName);
            checkInputIsHelp(playerName, "playerCreation");
            if (checkEOF(exit)) { 
               newGame = false; // Exit
            } 
            else {
               while ((!regex_match(playerName, regexPattern) && newGame) || playerName == "AI") { //Reprompt if not valid input
                  if (playerName == "AI") {
                     std::cout << "No you are not" << std::endl << "> ";
                  }
                  else if (playerName != "help") {
                     std::cout << "Invalid name format" << std::endl << "> ";
                  }
                  std::getline(std::cin, playerName);
                  checkInputIsHelp(playerName, "playerCreation");
                  if (checkEOF(exit)) { 
                     newGame = false; // Exit
                  } 
               }
               if (newGame) { //Valid input and no escape character
                  for (int i = 0; i < std::stoi(numberOfPlayers); i++) {
                     if (playerNames[i] == playerName) {
                        isDuplicate = true;
                     }
                  }
                  if (isDuplicate) {
                     std::cout << "Player name already exists" << std::endl << "> ";
                  } else {
                     // Add player name to the array
                     playerNames[playerIndex-1] = playerName;
                     playerIndex++;
                  }
               }
            }
         }
         //All player names have been created
         if (newGame) { 
            std::vector<Player*> players; 
            // Add every players to vector
            for (int i = 0; i < std::stoi(numberOfPlayers); i++) { 
               players.push_back(new Player(playerNames[i]));
            }
            if (std::stoi(numberOfPlayers) == 1) {
               numberOfPlayers = "2";
               players.push_back(new Player("AI"));
            }
            TileBag* tileBag = new TileBag(); 
            for (int i = 0; i < std::stoi(numberOfPlayers); i++) { 
               // distribute a number of tiles to a player
               for (int j = 0; j < NUM_OF_TILES_IN_HAND; j++) {
                  // Add tiles to a player hand
                  players[i]->addToBackOfHand(new Tile(*(tileBag->getFront())));
                  // remove the tiles added from the bag
                  tileBag->deleteFront();
               }
            }
            // Create a board of size 26x26
            Board* board = new Board(BOARD_DIMENSION);
            // Start the game
            std::cout << std::endl << "Let's Play!" << std::endl << std::endl;
            playGame(players, tileBag, board, 0);
            // Terminate the loop
            newGame = false;
            exit = true;
         }
      }
   }
}

void GameMenu::loadGame(bool &exit) {
   bool loadGame = true;
   std::ifstream loadFile;

   std::cout << std::endl << "Enter the filename from which to load a game" << std::endl << "> ";
   std::string fileName;
   // Input file name without .save
   std::getline(std::cin, fileName);
   checkInputIsHelp(fileName, "loadGame");
   loadFile.open(fileName + ".save");

   if (checkEOF(exit)) { 
      loadGame = false; // Exit
   } 
   else {
      while (!loadFile && loadGame) { // asking for reprompt until a valid filename is inputed
         if (fileName != "help") {
            std::cout << "File doesn't exist" << std::endl << "> ";
         }
         std::getline(std::cin, fileName);
         checkInputIsHelp(fileName, "loadGame");
         loadFile.open(fileName + ".save");

         if (checkEOF(exit)) {
            loadGame = false; // Exit
         } 
      }
      if (loadGame) {
         if (!isCorrectFormat(fileName)) {
            loadFile.close();
         } else { // load the game as a valid file is found
            std::cout << std::endl;
            std::vector<Player*> players;
            int numberOfLoadedPlayers = 0;
            bool isPlayer = true;

            std::string nextLine;
            getline(loadFile, nextLine);
            
            // Load every player info
            while (isPlayer) {
               players.push_back(new Player(nextLine)); //Player name

               getline(loadFile, nextLine); //Player score
               players[numberOfLoadedPlayers]->addScore(std::stoi(nextLine));

               getline(loadFile, nextLine); //Player hand
               std::vector<std::string> tiles = splitToTokens(nextLine, ',');
               for (int i = 0; i < tiles.size(); i++) {
                  //Add the tiles to a player hand
                  players[numberOfLoadedPlayers]->addToBackOfHand(new Tile(tiles[i].at(0), std::stoi(tiles[i].substr(1))));
               }

               numberOfLoadedPlayers++;
               getline(loadFile, nextLine);
               if (!isAlphabetic(nextLine) && !isUpper(nextLine)) { //Every third line in the save file is a new player
                  isPlayer = false;
               } 
            }

            std::vector<std::string> boardSize = splitToTokens(nextLine, ',');
            Board* board = new Board(std::stoi(boardSize[0])); //Board dimension

            getline(loadFile, nextLine); //Board states
            std::vector<std::string> states = splitToTokens(nextLine, ',');
            // Place all the tiles on the board as in the loaded game
            for (int i = 0; i < states.size(); i ++) {
               board->placeTileOnSquare(states[i].substr(0,2), states[i].substr(3));
            }

            getline(loadFile, nextLine); //Tile bag
            std::vector<std::string> tiles = splitToTokens(nextLine, ',');
            TileBag* tileBag = new TileBag(true);
            // Add all the available tiles to the tilebag as in the loaded game
            for (int i = 0; i < tiles.size(); i++) {
               tileBag->addToBack(new Tile(tiles[i].at(0), std::stoi(tiles[i].substr(1))));
            }

            getline(loadFile, nextLine); //Current player
            int currentPlayerIndex;
            // Jump to a player turn as in the loaded game
            for (int i = 0; i < numberOfLoadedPlayers; i++) {
               if (nextLine == players[i]->getName()) {
                  currentPlayerIndex = i;
               }
            }

            loadFile.close();
            numberOfPlayers = std::to_string(players.size());
            std::cout << "Quirkle game successfully loaded" << std::endl << std::endl;
            // Start the game
            playGame(players, tileBag, board, currentPlayerIndex);
            exit = true;
         }
      }
   } 
}

void GameMenu::playGame(std::vector<Player*> players, TileBag* tileBag, Board* board, int playersTurnIndex) {
   bool playing = true;
   int playerIndex = playersTurnIndex;
   // Keep the game running until the tilebag is empty or a player quit the game
   while (playing) {
      writeToHighScore(players);
      std::cout << players[playerIndex]->getName() << ", it's your turn" << std::endl;
      // Display score for each player
      for (int i = 0; i < players.size(); i++) {
         std::cout << "Score for " << players[i]->getName() << ": " << players[i]->getScore() << std::endl;
      }
      // Output the board
      board->printBoard();
      // Display current player's tiles in the hand
      std::cout << "Your hand is" << std::endl;
      players[playerIndex]->printHand();
        // Ask current player to play their turn
      playersTurn(players[playerIndex], board, tileBag, playing, players);
   
      playerIndex++;
      // reset the playerindex if it reach 2 
      if (playerIndex == players.size()) {
         playerIndex = 0; 
      }
   }
   //memory management here
   for (int i = 0; i < players.size(); i++) {
      delete players[i];
   }
   delete tileBag;
   delete board;
}

void GameMenu::playersTurn(Player* player, Board* board, TileBag* tileBag, bool &playing, std::vector<Player*> players) {
   bool playersTurn = true;
   board->resetHintPoints();
   
   // Scan board for highest scoring move for hint
   // Also see if there are any valid moves remaining in game
   
   bool validMove = false;
   for (int i = 0; i < player->handSize(); i++) {
      if (board->checkAllValidMoves(player->getTile(i)->getColour()+std::to_string(player->getTile(i)->getShape())) || !tileBag->isEmpty()) {
         validMove = true;
      }
   }
   if (!validMove) { // End the game
      std::cout << "No valid moves left" << std::endl;
      gameOver(players);
      playing = false;
      playersTurn = false;
      std::cout << std::endl;
   }
   

   std::vector<std::string> tokens;
   std::string input;
   // Keep asking for a player to input their turn command until it is valid
   while (playersTurn) {
      if (player->getName() != "AI") {
         std::cout << "> ";
         std::getline(std::cin, input);
         tokens = splitToTokens(input, ' ');
      }

      // AI's turn
      // AI places at highest score possible
      if (player->getName() == "AI") {
         // AI uses the hint to get the highest scoring move
         tokens = splitToTokens(board->getHint(), ' ');
         // If the score is 0 then there are no possible moves
         if (board->getHintPoints() == 0) {
            // Replace first tile in hand
            std::cout << "AI replaces " << player->getTile(0)->getColour() + std::to_string(player->getTile(0)->getShape()) << std::endl;
            replaceTile(player, tileBag, player->getTile(0)->getColour() + std::to_string(player->getTile(0)->getShape()), playersTurn);
         } else if (board->isValidMove(tokens[1], tokens[3])) {
            std::cout << "AI places " << tokens[1] << " at " << tokens[3] << std::endl;
            completeTurn(player, board, tileBag, playersTurn, playing, players, tokens[1], tokens[3]);
         }
      }
      // Place a tile on a board's coordinate if the input is valid (command length =4,first word is place, third word is at,
      // a tile is inputed in right format and is exist in the player's hand, a board coordinate is also in right format)
      else if (tokens.size() == 4 && tokens[0] == "place" && tokens[2] == "at") {
         if (!checkTileFormat(tokens[1])) {
            std::cout << "Invalid tile format" << std::endl;
         } else if (!player->tileInHand(tokens[1])) {
            std::cout << "Tile not in hand" << std::endl;
         } else {
            if (!checkGridFormat(tokens[3])) {
               std::cout << "Invalid grid format" << std::endl;
            } else if (!board->isValidMove(tokens[1], tokens[3])) {
               std::cout << "Invalid move" << std::endl;
               board->resetPoints();
            } else {
               completeTurn(player, board, tileBag, playersTurn, playing, players, tokens[1], tokens[3]);
            }
         }
      }
      // change a tile in a player hand with another tile in the bag if the input is valid
      // (command length = 2, first word is replace, second word is a valid tile that exist in the player's hand )
      else if (tokens.size() == 2 && tokens[0] == "replace") {
         if (!checkTileFormat(tokens[1])) {
            std::cout << "Invalid tile format" << std::endl;
         } else {
            if (!player->tileInHand(tokens[1])) {
               std::cout << "Tile not in hand" << std::endl;
            }
            else {
               if (tileBag->isEmpty()) {
                  std::cout << "Tile bag is empty" << std::endl;
               } else {
                  replaceTile(player, tileBag, tokens[1], playersTurn);
               }
            }
         }
      }
      // save the game if the input is valid (first word is save, second word is a file that player want to save to)
      else if (tokens.size() == 2 && tokens[0] == "save") {
         // add file extension
         std::ofstream saveFile(tokens[1] + ".save", std::ios::trunc);
         // add every player's name, score, tile in their hand to the file
         for (int i = 0; i < std::stoi(numberOfPlayers); i++) {
            saveFile << players[i]->getName() << std::endl;
            saveFile << players[i]->getScore() << std::endl;
            saveFile << players[i]->getHandAsString() << std::endl;
         } 
         // add board dimension to the file
         saveFile << std::to_string(board->getBoardDimension()) + "," + std::to_string(board->getBoardDimension()) << std::endl;
         // add location of tiles and the tiles themselves that are placed on the board to the file
         saveFile << board->getBoardStateAsString() << std::endl;
         // add the remaining tile from the bag to the file
         saveFile << tileBag->getTileBagAsString() << std::endl;
         saveFile << player->getName() << std::endl;
         saveFile.close();
         std::cout << "Game successfully saved" << std::endl << std::endl;
      }
      // Quit the game if player choose input quit or escape character
      else if ((tokens.size() == 1 && tokens[0] == "quit") || std::cin.eof()) {
         if (std::cin.eof()) {
            std::cout << std::endl;
         }
         playersTurn = false;
         playing = false;
      } 
      else if (tokens.size() == 1 && tokens[0] == "help") {
         checkInputIsHelp(input, "playersTurn");
      }
      else if (tokens.size() == 1 && tokens[0] == "hint") {
         std::cout << board->getHint() << std::endl;
      }
      else 
         std::cout << "Invalid command" << std::endl;
   }
}

void GameMenu::completeTurn(Player* player, Board* board, TileBag* tileBag, bool &playersTurn, bool &playing, std::vector<Player*> players,
                                 std::string tile, std::string location) {
   //remove the called tile from the player hand
   player->deleteTile(tile);
   // place it on the board
   board->placeTileOnSquare(tile, location);
   // update score
   player->addScore(board->getPoints());
   board->resetPoints();
   // run quirkle special op
   if (board->isQuirkle()) {
      std::cout << std::endl << "QWIRKLE!!!" << std::endl;
      board->resetQuirkle();
   }
   // Game is over
   if (tileBag->isEmpty() && player->handIsEmpty()) {
      // Print final board
      std::cout << std::endl;
      board->printBoard();
      gameOver(players);
      // end the game
      playing = false;
      playersTurn = false;
   } else if (!tileBag->isEmpty()) {
      // add new tile to the player hand if there are still tiles
      player->addToBackOfHand(new Tile(*(tileBag->getFront())));
      // remove the tile that has been added to the player from the bag
      tileBag->deleteFront();
   }
   playersTurn = false;
   std::cout << std::endl;
}

void GameMenu::replaceTile(Player* player, TileBag* tileBag, std::string tile, bool &playersTurn) {
   player->addToBackOfHand(new Tile(*(tileBag->getFront())));
   tileBag->deleteFront();
   tileBag->addToBack(new Tile(*(player->getTile(tile))));
   player->deleteTile(tile);
   playersTurn = false;
   std::cout << std::endl;
}

void GameMenu::gameOver(std::vector<Player*> players) {
   std::cout << std::endl << "Game over" << std::endl;
   int highestScore = 0;
   std::string highestPlayer;
   for (int i = 0; i < players.size(); i++) {
      if (players[i]->getScore() > highestScore) {
         highestScore = players[i]->getScore();
         highestPlayer = players[i]->getName();
      } else if (players[i]->getScore() == highestScore) {
         highestPlayer = "DRAW!";
      }
      std::cout << "Score for " << players[i]->getName() <<": " << players[i]->getScore() << std::endl;
   }
   if (highestPlayer == "DRAW!") {
      std::cout << highestPlayer;
   } else {
      std::cout << "Player " << highestPlayer <<" won!";
   }
}

bool GameMenu::isInt(std::string string) {
   bool isInt = true;

   for (long unsigned int i = 0; i < string.length(); i++) {
      if (isdigit(string[i]) == false)
         isInt = false;
   }
   return isInt;
}

bool GameMenu::isAlphabetic(std::string string) {
   bool isAlphabetic = true;
   for (int i = 0; i < string.size(); i++){
      if (!isalpha(string[i])) {
         isAlphabetic = false;
      }
   }
   return isAlphabetic;
}

bool GameMenu::isUpper(std::string string) {
   bool isUpper = true;
   for (int i = 0; i < string.size(); i++){
      if (!isupper(string[i])) {
         isUpper = false;
      }
   }
   return isUpper;
}

std::vector<std::string> GameMenu::splitToTokens(std::string string, char delimiter) {
   //Reference: https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
   std::vector <std::string> tokens;
   std::stringstream ss(string);
   std::string intermediate;
    
   while(getline(ss, intermediate, delimiter))
      tokens.push_back(intermediate);
      
   return tokens;
}

bool GameMenu::isCorrectFormat(std::string fileName) {
   std::ifstream loadFile;
   loadFile.open(fileName + ".save");
   std::string nextLine;
   getline(loadFile, nextLine); // This line should be a player name
   int line = 1;

   bool isCorrectFormat = true;
   bool isPlayer = true;

   if (loadFile.eof()) { // If the file is empty,
      std::cout << "File is empty" << std::endl << std::endl;
      isCorrectFormat = false;
   } else {
      std::vector<std::string> playerNames;
      while (isPlayer) {
         if (!isAlphabetic(nextLine) || !isUpper(nextLine) || nextLine.empty()) { // Check player name format
            std::cout << "Error at line " << line << ": not a valid name for player " << playerNames.size()+1 << std::endl << std::endl;
            isCorrectFormat = false;
            isPlayer = false;
         // Only get next line while format is correct. This also stops null error if the file doesn't have enough lines
         } else { 
            playerNames.push_back(nextLine); // Store player name to check current player exists later on
            getline(loadFile, nextLine); // Player score
            line++;
         }
         if (!isInt(nextLine) && isCorrectFormat) { // Check score format
            std::cout << "Error at line " << line << ": not a valid player score" << std::endl << std::endl;
            isCorrectFormat = false;
            isPlayer = false;
         // Only get next line while format is correct. This also stops null error if the file doesn't have enough lines
         } else {
            getline(loadFile, nextLine); // Player hand
            line++;
         }
         std::vector<std::string> tiles = splitToTokens(nextLine, ',');
         if ((tiles.size() == 0 || tiles.size() > NUM_OF_TILES_IN_HAND) && isCorrectFormat) { // Too many tiles
            std::cout << "Error at line " << line << ": too many tiles in player " << playerNames.size() << " hand" << std::endl << std::endl;
            isCorrectFormat = false;
            isPlayer = false;
         }
         for (int i = 0; i < tiles.size(); i++) { // Check hand format
            if (!checkTileFormat(tiles[i]) && isCorrectFormat) {
               std::cout << "Error at line " << line << ": invalid tile format in player " << playerNames.size() << " hand" << std::endl << std::endl;
               isCorrectFormat = false;
               isPlayer = false;
            }
         }
         // Only get next line while format is correct. This also stops null error if the file doesn't have enough lines
         if (isCorrectFormat) {
            getline(loadFile, nextLine); // This line is either another player or the board size
            line++;
         }
         if ((!isAlphabetic(nextLine) || !isUpper(nextLine)) && isCorrectFormat) { // Check if there are more players
            isPlayer = false;
            std::vector<std::string> boardSize = splitToTokens(nextLine, ',');
            if (!isInt(boardSize[0]) && boardSize[0] != boardSize[1]) {
               std::cout << "Error at line " << line << ": not a valid name for player " << playerNames.size()+1 << std::endl << std::endl;
               isCorrectFormat = false;
            }
         }
      }
      std::vector<std::string> boardSize = splitToTokens(nextLine, ',');
      if (!isInt(boardSize[0]) && boardSize[0] != boardSize[1] && isCorrectFormat) { // Check board size format
         std::cout << "Error at line " << line << ": invalid board size" << std::endl << std::endl;
         isCorrectFormat = false;
      // Only get next line while format is correct. This also stops null error if the file doesn't have enough lines
      } else {
         getline(loadFile, nextLine); // Board state
         line++;
      }
      std::vector<std::string> states = splitToTokens(nextLine, ',');
      for (int i = 0; i < states.size(); i ++) {                     
         if ((!checkTileFormat(states[i].substr(0,2)) || !checkGridFormat(states[i].substr(3))) && isCorrectFormat){ 
            std::cout << "Error at line " << line << ": invalid board states" << std::endl << std::endl;
            isCorrectFormat = false;
         }
      }
      // Only get next line while format is correct. This also stops null error if the file doesn't have enough lines
      if (isCorrectFormat) {
         getline(loadFile, nextLine); // Tiles in tile bag
         line++;
      }
      std::vector<std::string> tiles = splitToTokens(nextLine, ',');
      if (tiles.size() > (TILEBAG_SIZE)-(2*NUM_OF_TILES_IN_HAND)) {
         std::cout << "Error at line " << line << ": too many tiles in tile bag" << std::endl << std::endl;
         isCorrectFormat = false;
      }
      for (int i = 0; i < tiles.size(); i++) { // Check tile bag format
         if (!checkTileFormat(tiles[i]) && isCorrectFormat) {
            std::cout << "Error at line " << line << ": invalid tile format in grid bag" << std::endl << std::endl;
         
            isCorrectFormat = false;
         }
      }
      // Only get next line while format is correct. This also stops null error if the file doesn't have enough lines
      if (isCorrectFormat) {
         getline(loadFile, nextLine); // Current player
         line++;
      }
      bool playerExists = false;
      for (int i = 0; i < playerNames.size(); i++) {
         if (playerNames[i] == nextLine) {
            playerExists = true;
         }
      }
      if (!playerExists && isCorrectFormat) { // If player exists then the format is also correct
         std::cout << "Error at line " << line << ": invalid current player" << std::endl << std::endl;
         isCorrectFormat = false;
      }

      loadFile.close();
   }
   return isCorrectFormat;
}

bool GameMenu::checkTileFormat(std::string tile) {
   bool isValid = false;
   if ((tile.substr(0,1) == "R" || tile.substr(0,1) == "O" || tile.substr(0,1) == "Y" ||
       tile.substr(0,1) == "G" || tile.substr(0,1) == "B" || tile.substr(0,1) == "P") &&
       isInt(tile.substr(1))) {
         if ((std::stoi(tile.substr(1)) >= 1 && std::stoi(tile.substr(1)) <= 6)) {
            isValid = true;
         }
   }
   return isValid;
}

bool GameMenu::checkGridFormat(std::string grid) {
   bool isValid = false;
   if (isUpper(grid.substr(0,1)) && isAlphabetic(grid.substr(0,1)) && isInt(grid.substr(1))) {
      if (std::stoi(grid.substr(1)) >= 0 && std::stoi(grid.substr(1)) < BOARD_DIMENSION) {
         isValid = true;
      }
   }
   return isValid;
}

bool GameMenu::checkEOF(bool &exit) {
   if (std::cin.eof()) { //Check input for escape character
      std::cout << std::endl;
      exit = true;
   }
   return exit;
}

void GameMenu::checkEmptyInput(std::string &input) {
   if (input.empty()) {
      input = " ";
   }
}

void GameMenu::checkInputIsHelp(std::string input, std::string check) {
   if (input == "help") {
      if (check == "menu") {
      std::cout << std::endl << "Type in a number to select an option:" << std::endl;
      std::cout << "    1 to start a new game" << std::endl;
      std::cout << "    2 to load a game from a save file" << std::endl;
      std::cout << "    3 to view credits" << std::endl;
      std::cout << "    4 to exit game" << std::endl;
      std::cout << "    5 to view high scores" << std::endl << "> ";
      } else if (check == "playerNumberSelection") {
         std::cout << std::endl << "Type in a number to select amount of players:" << std::endl;
         std::cout << "    1 to play against an AI" << std::endl;
         std::cout << "    2 for a two player game" << std::endl;
         std::cout << "    3 for a three player game" << std::endl;
         std::cout << "    4 for a four player game" << std::endl << "> ";
      } else if (check == "playerCreation") {
         std::cout << std::endl << "Enter a unique player name:" << std::endl;
         std::cout << "    Capital letters only" << std::endl;
         std::cout << "    No numbers, spaces or special characters" << std::endl << "> ";
      } else if (check == "playersTurn") {
         std::cout << std::endl << "Commands:" << std::endl;
         std::cout << "    place <tile code> at <grid code>    Places a tile from your hand onto a valid grid coordinate" << std::endl;
         std::cout << "    replace <tile code>                 Replaces a tile in your hand from the tile bag" << std::endl;
         std::cout << "    save <filename>                     Saves your current game to file. It will overwrite an existing file" << std::endl;
         std::cout << "    quit                                Exits the program" << std::endl;
         std::cout << "    hint                                Get a helpful hint if you are stuck on your next move" << std::endl;
      } else if (check == "loadGame") {
         std::cout << std::endl << "Type in the name of the file you wish to load game from" << std::endl << "> ";
      }
   } 
}

void GameMenu::credits() {
   std::cout << std::endl << "-----------------------------------" << std::endl;
   std::cout << "Name: Quoc Dat Tran" << std::endl;
   std::cout << "Student ID: s3827826" << std::endl;
   std::cout << "Email: s3827826@student.rmit.edu.au" << std::endl;
   std::cout << "-----------------------------------" << std::endl << std::endl;
}

void GameMenu::highScores() {
   std::cout << std::endl << "High Scores" << std::endl;
   std::cout << "-----------" << std::endl;
   std::ifstream in;
   in.open("HIGHSCORES.txt");
   if (!in) {
      std::cout << "No high scores recorded" << std::endl << std::endl;
   } else {
      std::string nextLine;
      int count = 0;
      while (count < 10) {
         if (getline(in, nextLine)) {
            std::cout << nextLine << std::endl;
         }
         count++;
      }
      std::cout << std::endl;
   }
}

bool GameMenu::sortByVal(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) { 
   return (a.second > b.second); 
}

void GameMenu::writeToHighScore(std::vector<Player*> players) {
   // Create a highscores file if it doesn't exist
   std::ofstream highScores("HIGHSCORES.txt", std::ios::app);
   highScores.close();

   // Read in highscores file
   std::ifstream in;
   in.open("HIGHSCORES.txt");
   std::string nextLine;

   // Copy scores into a map
   std::map<std::string, int> scores;
   std::vector<std::string> tokens;
   while (getline(in, nextLine)) {
      tokens = splitToTokens(nextLine, ' ');
      scores.insert(std::make_pair(tokens[0],std::stoi(tokens[1])));
   }
   in.close();

   for (std::vector<Player*>::const_iterator it = players.begin(); it != players.end(); it++) {
      Player* player = *it;
      // Check if previous players stored score is less than current score. Update to higher score if it is
      if (scores.count(player->getName()) > 0 && scores.find(player->getName())->second < player->getScore()) {
         scores.at(player->getName()) = player->getScore();
      }
      // Insert new players into the list
      else if (scores.count(player->getName()) == 0) {
         scores.insert(std::make_pair(player->getName(),player->getScore()));
      }
   }
   // create a empty vector of pairs
	std::vector<std::pair<std::string, int> > vec;
	// copy key-value pairs from the map to the vector
   std::map<std::string, int> :: iterator it2;
   for (it2=scores.begin(); it2!=scores.end(); it2++) 
   {
      vec.push_back(make_pair(it2->first, it2->second));
   }
	// sort the vector by increasing order of its pair's second value
   sort(vec.begin(), vec.end(), sortByVal); 

   // New high scores reordered
   highScores.open("HIGHSCORES.txt", std::ios::trunc);
   for (std::vector<std::pair<std::string, int> >::const_iterator it = vec.begin(); it != vec.end(); it++) {
      highScores << it->first + " " + std::to_string(it->second) << std::endl;
   }
   highScores.close();
}
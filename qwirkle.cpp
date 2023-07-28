#include "GameMenu.h"
#include <iostream>

int main(void) {
   bool exit = false;

   std::cout << std::endl << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   GameMenu* gameMenu = new GameMenu();
   while (!exit) {
      gameMenu->menu(exit);
   }
   
   std::cout << std::endl << "Goodbye" << std::endl << std::endl;
   delete gameMenu;
   return EXIT_SUCCESS;
}



#include "LinkedList.h"
#include <iostream>

// Constructor
LinkedList::LinkedList() {
   head = nullptr;
}

// Destructor
LinkedList::~LinkedList() { 
   for (int i = 0; i < size(); i++) {
      deleteAt(0);
   }
}

// Get the size of the linked list
int LinkedList::size() {
   int length = 0;

   Node* current = head;
   while (current != nullptr) {
      length++;
      current = current->next;
   }
   return length;
}

// Get the tile of the linked list
Tile* LinkedList::get(int index) {
   Tile* indexedTile = nullptr;

   if (index >= 0 && index < size()) {
      int counter = 0;
      Node* current = head;

      while (counter < index) {
         counter++;
         current = current->next;
      }
      indexedTile = current->tile;
   }
   return indexedTile;
}

// Add the tile to the back of the linked list
void LinkedList::addBack(Tile* tile) {
   Node* newNode = new Node(tile, nullptr);

   if (head == nullptr) {
      head = newNode;
   }
   else {
      Node* current = head;
      while (current->next != nullptr) {
         current = current ->next;
      }
      current->next = newNode;
   }
}

// Delete the node at the position
void LinkedList::deleteAt(int index) {
   Node* previous = head;
   Node* current = previous->next;
   if (index == 0) {
      head = current;
      delete previous;
   }
   else {
      for (int i = 0; i < index-1; i++) {
         previous = previous->next;
         current = current->next;
      }
      previous->next = current->next;
      delete current;
   }
}
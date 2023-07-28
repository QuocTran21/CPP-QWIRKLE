
#include "Node.h"

// Constructor
Node::Node(Tile* tile, Node* next) {
   this->tile = tile;
   this->next = next;
}

// Copy Constructor
Node::Node(Node& other) {
   this->tile = other.tile;
   this->next = other.next;
}

// Destructor
Node::~Node() {
   delete tile;
}

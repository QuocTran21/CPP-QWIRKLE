
#include "Tile.h"

// Constructor
Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
}

// Copy constructor
Tile::Tile(Tile& other) {
    this->colour = other.colour;
    this->shape = other.shape;
}

// Desctructor
Tile::~Tile() {
}

// Get the colour of the tile
Colour Tile::getColour() {
    return colour;
}

// Get the shape of the tile
Shape Tile::getShape() {
    return shape;
}
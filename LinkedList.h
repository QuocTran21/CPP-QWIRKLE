
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    
    int size();
    Tile* get(int index);
    
    void addBack(Tile* tile);
    void deleteAt(int index);

    void shuffleList();

private:
    Node* head;

    Node* splitAtHalf(Node* first);
    void interleave(Node* first, Node* second);
};

#endif // ASSIGN2_LINKEDLIST_H

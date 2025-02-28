#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

class Node {
public:
    string name;
    int stock;
    Node *next;
    Node *prev;

    Node(string name, int stock) {
        this->name = name;
        this->stock = stock;
        this->next = NULL;
        this->prev = NULL;
    }
};

#endif

#ifndef SORT_H
#define SORT_H

#include "Node.h"

class Sort {
public:
    // Merge Sort
    static Node* mergeSort(Node* head);
    static void binarySearch(Node* head, int target);

private:
    static Node* merge(Node* left, Node* right);
    static void split(Node* source, Node** front, Node** back);
};

#endif

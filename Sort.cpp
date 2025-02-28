#include "Sort.h"
#include <iostream>
using namespace std;

// merge sort
Node* Sort::merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;


    Node* result;
    if (left->stock <= right->stock) {
        result = left;
        cout << "Left Value: " << left->stock << " is less than Right Value " << right->stock << ", switching places..." << endl;
        result->next = merge(left->next, right);
    } else {
        result = right;
        cout << "Right Value: " << right->stock << " is less than Left Value " << left->stock << ", switching places..." << endl;
        result->next = merge(left, right->next);
    }
    return result;
}

void Sort::split(Node* source, Node** front, Node** back) {
    if (!source || !source->next) {
        *front = source;
        *back = NULL;
        return;
    }

    Node* slow = source;
    Node* fast = source->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

Node* Sort::mergeSort(Node* head) {
    if (!head || !head->next) return head;

    Node* left;
    Node* right;

    split(head, &left, &right);

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

void Sort::binarySearch(Node* head, int target) {
    if (!head) {
        cout << "--------------------------------\n";
        cout << "Stock list is empty.\n";
        cout << "--------------------------------\n";
        return;
    }

    Node* leftN = head;
    Node* rightN = NULL;
    Node* match = NULL;

    do {
        Node* mid = leftN;
        Node* fast = leftN;

        while (fast != rightN && fast->next != rightN) {
            mid = mid->next;
            fast = fast->next->next;
        }
        cout << "Checking node with target: " << mid->stock << endl;

        if (mid->stock == target) {
            cout << "Found target: " << target << " at middle " << endl;
            match = mid;
            rightN = mid;
        } else if (mid->stock < target) {
            cout << "Searching right half..." << endl;
            leftN = mid->next;
        } else {
            cout << "Searching left half..." << endl;
            rightN = mid;
        }

    } while (rightN != leftN);

    if (!match) {
        cout << "No stocks found with price: " << target << endl;
        return;
    }

    cout << "--------------------------------\n";
    cout << "Stocks found with price " << target << ":\n";
    cout << "--------------------------------\n";

    while (match->prev && match->prev->stock == target) {
        match = match->prev;
    }

    Node* temp = match;
    while (temp && temp->stock == target) {
        cout << "NAME: " << temp->name << " | PRICE: " << temp->stock << endl;
        temp = temp->next;
    }
}

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

class LinkedList
{
public:
    LinkedList() { head = nullptr; }
    void insert(int value);
    void display() const;
    void remove(int value);

private:
    Node *head;
};
#endif

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
    LinkedList();
    void insertAtEnd(int value);
    void removeFront();
    int front() const;
    bool isEmpty() const;
    void display() const;
    void remove(int value);

private:
    Node *head;
};
#endif

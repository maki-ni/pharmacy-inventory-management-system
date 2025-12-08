#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList()
{
    head = nullptr;
}

void LinkedList::insert(int value)
{
    Node *newNode = new Node{value, head};
    head = newNode;
}

void LinkedList::display() const
{
    Node *current = head;
    while (current)
    {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

void LinkedList::remove(int value)
{
    Node *current = head;
    Node *prev = nullptr;

    while (current && current->data != value)
    {
        prev = current;
        current = current->next;
    }

    if (current)
    {
        if (prev)
            prev->next = current->next;
        else
            head = current->next;
        delete current;
    }
}

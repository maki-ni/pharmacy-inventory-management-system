#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList()
{
    head = nullptr;
}

bool LinkedList::isEmpty() const
{
    return head == nullptr;
}

int LinkedList::front() const
{
    if (head)
        return head->data;
    else
    {
        cout << "List is empty.\n";
        return -1;
    }
}

void LinkedList::insertAtEnd(int value)
{
    Node *newNode = new Node{value, nullptr};

    if (isEmpty())
    {
        head = newNode;
        return;
    }

    Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    current->next = newNode;
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

void LinkedList::removeFront()
{
    if (isEmpty())
        return;

    Node *temp = head;
    head = head->next;
    delete temp;
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

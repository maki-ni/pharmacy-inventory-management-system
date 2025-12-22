#include "PatientQueue.h"
#include <iostream>
using namespace std;

PatientQueue::PatientQueue() : front(nullptr), rear(nullptr) {}

void PatientQueue::enqueue(int id, string name)
{
    Patient *newPatient = new Patient{id, name, nullptr};
    if (rear == nullptr)
    {
        front = rear = newPatient;
    }
    else
    {
        rear->next = newPatient;
        rear = newPatient;
    }
}

void PatientQueue::dequeue()
{
    if (front == nullptr)
    {
        cout << "Queue is empty!" << endl;
        return;
    }
    Patient *temp = front;
    cout << "Serving patient: " << temp->id << " - " << temp->name << endl;
    front = front->next;
    if (front == nullptr)
        rear = nullptr;
    delete temp;
}

void PatientQueue::display()
{
    Patient *current = front;
    cout << "Patients in queue:" << endl;
    while (current != nullptr)
    {
        cout << current->id << " - " << current->name << endl;
        current = current->next;
    }
}
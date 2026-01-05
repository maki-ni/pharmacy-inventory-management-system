#include "PatientQueue.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

PatientQueue::PatientQueue() : front(nullptr), rear(nullptr) {}
bool PatientQueue::idExists(int id)
{
    Patient *current = front;
    while (current != nullptr)
    {
        if (current->id == id)
        {
            return true; // Found a match
        }
        current = current->next;
    }
    return false; // No match found
}

void PatientQueue::enqueue(int id, string name, bool isPregnant)
{
    // Validate ID
    if (id <= 0)
    {
        cout << "Error: Invalid ID. Must be positive." << endl;
        return;
    }

    // Validate name
    if (name.empty())
    {
        cout << "Error: Name cannot be empty." << endl;
        return;
    }

    if (idExists(id))
    {
        cout << "Error: Patient with ID " << id << " already exists. Skipping..." << endl;
        return;
    }

    Patient *newPatient = new Patient{id, name, isPregnant, nullptr};

    // Case 1: Empty queue
    if (front == nullptr)
    {
        front = rear = newPatient;
        return;
    }

    // Case 2: NOT pregnant → normal enqueue
    if (!isPregnant)
    {
        rear->next = newPatient;
        rear = newPatient;
        return;
    }

    // Case 3: Pregnant → priority insertion
    // If front is not pregnant, insert at front
    if (!front->isPregnant)
    {
        newPatient->next = front;
        front = newPatient;
        return;
    }

    // Otherwise, insert after last pregnant patient
    Patient *current = front;
    while (current->next != nullptr && current->next->isPregnant)
    {
        current = current->next;
    }

    newPatient->next = current->next;
    current->next = newPatient;

    // Update rear if inserted at the end
    if (newPatient->next == nullptr)
    {
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
        cout << current->id << " - " << current->name << (current->isPregnant ? " (Pregnant)" : "") << endl;
        current = current->next;
    }
}
// import from file before continuing further
void PatientQueue::importFromFile(const string &filename)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    getline(in, line); // skip header

    while (getline(in, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string idStr, name, pregStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, pregStr);

        int id = stoi(idStr);
        bool isPregnant = (pregStr == "1");

        enqueue(id, name, isPregnant);
    }

    in.close();
    cout << "Patients imported from: " << filename << endl;
}

void PatientQueue::exportToFile(const string &filename) const
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    out << "id,name,isPregnant\n";

    Patient *current = front;
    while (current != nullptr)
    {
        out << current->id << ","
            << current->name << ","
            << current->isPregnant << "\n";
        current = current->next;
    }

    out.close();
}

int PatientQueue::getPatientCount() const
{
    int count = 0;
    Patient *current = front;
    while (current)
    {
        ++count;
        current = current->next;
    }
    return count;
}
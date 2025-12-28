#include "PatientQueue.h"
#include <iostream>
#include <sstream>
#include <fstream>

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
    // Skip header
    getline(in, line);

    int id;
    string name;

    // Read each line as "id,name"
    while (getline(in, line))
    {
        if (line.empty())
            continue;

        // Use a stringstream to parse the line
        stringstream ss(line);
        string idStr;

        // Get id before comma
        getline(ss, idStr, ',');
        // Get name after comma
        getline(ss, name);

        // Convert id string to int
        id = stoi(idStr);

        enqueue(id, name);
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
    // Optional header for clarity
    out << "id,name" << "\n";
    Patient *current = front;
    while (current != nullptr)
    {
        out << current->id << "," << current->name << "\n";
        current = current->next;
    }
    out.close();
    cout << "Patients exported to: " << filename << endl;
}

int PatientQueue::getPatientCount() const {
    int count = 0;
    Patient *current = front;
    while (current != nullptr) {
        ++count;
        current = current->next;
    }
    return count;
}
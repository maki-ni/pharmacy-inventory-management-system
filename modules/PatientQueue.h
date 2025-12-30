#ifndef PATIENTQUEUE_H
#define PATIENTQUEUE_H

#include <string>
using namespace std;

struct Patient
{
    int id;
    string name;
    Patient *next;
};
class PatientQueue
{
private:
    Patient *front;
    Patient *rear;
    bool idExists(int id);

public:
    PatientQueue();
    bool enqueue(int id, string name);
    void dequeue();
    void display();
    void exportToFile(const string &filename) const;
    void importFromFile(const string &filename);
    string getAllPatients();
    string dequeueMessage();
};

#endif
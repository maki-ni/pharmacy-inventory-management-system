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

public:
    PatientQueue();
    void enqueue(int id, string name);
    void dequeue();
    void display();
    void exportToFile(const string &filename) const;
    void importFromFile(const string &filename);
    int getPatientCount() const; // added

};

#endif
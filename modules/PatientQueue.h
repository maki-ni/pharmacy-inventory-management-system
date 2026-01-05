#ifndef PATIENTQUEUE_H
#define PATIENTQUEUE_H

#include <string>
using namespace std;

struct Patient
{
    int id;
    string name;
    bool isPregnant;
    Patient *next;
};
class PatientQueue
{
private:
    Patient *front;
    Patient *rear;

public:
    PatientQueue();
    bool idExists(int id);
    void enqueue(int id, string name, bool isPregnant);
    void dequeue();
    void display();
    void exportToFile(const string &filename) const;
    void importFromFile(const string &filename);
    int getPatientCount() const; //added

};

#endif
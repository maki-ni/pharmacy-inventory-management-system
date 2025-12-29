#include <iostream>
using namespace std;
#include "modules/DrugBST.h"
#include "modules/PatientQueue.h"

int main()
{
    DrugBST dr;
    PatientQueue pq;
    // import pre existing drugs
    dr.importFromFile("drugs.csv");
    pq.importFromFile("patients.csv");
    cout << endl;

    // Added drugs
    dr.addDrug("iboprofien1", 01, 10, "2026-01-01");
    dr.addDrug("paracetamol1", 02, 20, "2026-02-01");
    dr.addDrug("cough drops", 03, 13, "2024-01-01");
    dr.displayDrugs();
    cout << endl;

    // discarding expired drugs and writing files
    dr.discardExpiredFromCSV("drugs.csv");

    // patients added
    pq.enqueue(3, "Mary");
    pq.enqueue(4, "James");
    pq.display();

    // Export current data to files
    pq.exportToFile("patients.csv");
}
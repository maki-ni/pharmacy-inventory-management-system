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
dr.addDrug("Ibuprofen", 01, 10, "2026-01-01");
dr.addDrug("Paracetamol", 02, 20, "2026-02-01");
dr.addDrug("Cough Drops", 03, 13, "2024-01-01");

    dr.displayDrugs();
    cout << endl;

    // discarding expired drugs and writing files
    dr.discardExpiredFromCSV("drugs.csv");

    // patients added
    pq.enqueue(1, "Abel");
    pq.enqueue(2, "Hanna");
    pq.enqueue(3, "Abebe");
    pq.enqueue(4, "Selam");
    pq.display();

    // Export current data to files
    pq.exportToFile("patients.csv");

    // Print totals
    cout << "Total number of drugs: " << dr.getDrugTypeCount() << endl;
    cout << "Total patients registered: " << pq.getPatientCount() << endl;

}
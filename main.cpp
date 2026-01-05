#include <iostream>
using namespace std;
#include "modules/DrugBST.h"
#include "modules/PatientQueue.h"
#include "ctype.h"

void welcome(DrugBST &dr, PatientQueue &pq)
{
    cout << "Welcome to Pharmacy Inventory Management System!" << endl;
    bool running = true;
    while (running)
    {
        cout << "\nMenu:" << endl;
        cout << "1. Add Drug" << endl;
        cout << "2. Find Drug by Name" << endl;
        cout << "3. Find Drug by ID" << endl;
        cout << "4. Display All Drugs" << endl;
        cout << "5. Export Drugs to File" << endl;
        cout << "6. Discard Expired Drugs" << endl;
        cout << "7. Clear Drug Tree" << endl;
        cout << "8. Add Patient" << endl;
        cout << "9. Dequeue Patient" << endl;
        cout << "10. Display Patients" << endl;
        cout << "11. Export Patients to File" << endl;
        cout << "12. Show total number of patients" << endl;
        cout << "13. Show drugs that need restock (qty < 5)" << endl;
        cout << "14. Show price & total value for drug by ID" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose an option: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string name, expiry;
            int id, qty;
            double price;
            cout << "Enter drug name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter quantity: ";
            cin >> qty;
            cout << "Enter price per unit: ";
            cin >> price;
            cout << "Enter expiry date (YYYY-MM-DD): ";
            cin >> expiry;
            dr.addDrug(name, id, qty, expiry, price);
            break;
        }
        case 2:
        {
            string name;
            cout << "Enter drug name: ";
            cin.ignore();
            getline(cin, name);
            dr.findDrugName(name);
            break;
        }
        case 3:
        {
            int id;
            cout << "Enter drug ID: ";
            cin >> id;
            dr.findDrugId(id);
            break;
        }
        case 4:
        {
            int count = dr.getDrugTypeCount();
            cout << "There are a total of " << count << " drugs currently." << endl;
            dr.displayDrugs();
            break;
        }
        case 5:
        {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            dr.exportToFile(filename);
            break;
        }
        case 6:
            dr.discardExpiredFromCSV("drugs.csv");
            break;
        case 7:
            dr.clearTree();
            break;
        case 8:
        {
            string name;
            int id;
            bool isPregnant;
            cout << "Enter patient name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter ID: ";
            cin >> id;
            cout<<"Pregnant? enter : 0 or 1";
            cin>>isPregnant;
            pq.enqueue(id, name, isPregnant);
            break;
        }
        case 9:
            pq.dequeue();
            break;
        case 10:
            pq.display();
            break;
        case 11:
        {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            pq.exportToFile(filename);
            break;
        }
        case 12:
           cout << "Total patients: " << pq.getPatientCount() << endl;
           break;
         case 13:
        {
            cout << "Drugs with quantity < 5 (restock needed):" << endl;
            // we already print restock notices when displaying all; call display
            dr.displayDrugs();
            break;
        }
        case 14:
        {
            int id;
            cout << "Enter drug ID to show price and total value: ";
            cin >> id;
            dr.findDrugId(id);
            break;
        }
        
        case 0:
            running = false;
            break;
        default:
            cout << "Invalid choice." << endl;
        }

        // Check if menue is exited

        if(!running){
            break;
        }

        cout << "Do you want to continue? Y/n" << endl;
        char cont;
        cin >> cont;
        switch(toupper(cont)){
            case 'Y':
                continue;
                break;
            case 'N':
                running = false;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}

int main()
{
    DrugBST dr;
    PatientQueue pq;
    // import pre existing drugs
    dr.importFromFile("drugs.csv");
    pq.importFromFile("patients.csv");
    cout << endl;

    // // Added drugs
    // dr.addDrug("Ibuprofen", 01, 10, "2026-01-01");
    // dr.addDrug("Paracetamol", 02, 20, "2027-02-01");
    // dr.addDrug("Cough Drops", 03, 13, "2024-01-01");

    // dr.displayDrugs();
    // cout << endl;

    // discarding expired drugs and writing files
    // dr.exportToFile("drugs.csv");
    // dr.discardExpiredFromCSV("drugs.csv");

    // patients added
    // pq.enqueue(3, "Mary");
    // pq.enqueue(4, "James");
    // pq.display();
    // count the number of drugs

    // Export current data to files

    welcome(dr, pq);

    // Export current data to files
    dr.exportToFile("drugs.csv");
    pq.exportToFile("patients.csv");



}
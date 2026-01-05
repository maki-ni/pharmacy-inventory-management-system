#ifndef DRUGBST_H
#define DRUGBST_H
#include <string>

#include <fstream>
#include <vector>

using namespace std;

struct Drug
{
    int id;
    string name;
    Drug *left;
    Drug *right;
    int quantity;
    string catagory;
    string expiryDate;
    double price;
    Drug(string n, int i, int quan, string expiry,double priceVal = 0.0); // automatically initiallizes the res
};

class DrugBST
{
private:
    Drug *root;
    Drug *insert(Drug *node, string name, int id, int quantity, string expiry,double price);
    Drug *deleteByName(Drug *node, const string& name);
    Drug* findById(Drug* node, int id);
    bool searchByName(Drug *node, string name);
    bool searchById(Drug *node, int id);
    void inorder(Drug *node);
    void inorderToFile(Drug *node, ofstream &out);
    int countNodes(Drug *node);
    void clear(Drug *node);
    void collectValidDrugs(Drug *node, vector<Drug> &valid, const string &today);
   

public:
    DrugBST();
    void addDrug(string name, int id, int quantity, string expiryDate, double price = 0.0);
    void findDrugName(string name);
    void findDrugId(int id);
    void displayDrugs();
    void exportToFile(const string &filename);
    void importFromFile(const string &filename); 
    int getDrugTypeCount();
    void clearTree();
    void discardExpiredFromCSV(const string &filename);

};

#endif
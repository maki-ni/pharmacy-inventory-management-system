#ifndef DRUGBST_H
#define DRUGBST_H
#include <string>

#include <fstream>
#include <vector>

using namespace std;

struct Batch {
    int quantity;
    string expiryDate;
};

struct Drug
{
    string name;
    int id;
    vector<Batch> batches;
    Drug *left;
    Drug *right;
    Drug(string n, int i, int quan, string expiry); // automatically initiallizes the res
};

class DrugBST
{
private:
    Drug *root;
    Drug *insert(Drug *node, string name, int id, int quantity, string expiry);
    Drug *deleteByName(Drug *node, const string& name);
    bool searchByName(Drug *node, string name);
    bool searchById(Drug *node, int id);
    void inorder(Drug *node);
    void inorderToFile(Drug *node, ofstream &out);
    int countNodes(Drug *node);
    void clear(Drug *node);
    void collectValidDrugs(Drug *node, vector<Drug> &valid, const string &today);
    Drug* findNodeByName(Drug *node, string name);
    Drug* findNodeById(Drug *node, int id);
    void inorderToString(Drug *node, string &str);
    bool idExistsHelper(Drug *node, int id);

public:
    DrugBST();
    bool addDrug(string name, int id, int quantity, string expiryDate);
    void findDrugName(string name);
    void findDrugId(int id);
    void displayDrugs();
    void exportToFile(const string &filename);
    void importFromFile(const string &filename); 
    int getDrugTypeCount();
    void clearTree();
    void discardExpiredFromCSV(const string &filename);
    string getDrugDetailsByName(string name);
    string getDrugDetailsById(int id);
    string getAllDrugs();
    bool nameExists(string name);
    bool idExists(int id);
    void updateQuantity(string name, int newQty, string newExpiry);
    Drug* findNodeByNamePublic(string name);
    Drug* findNodeByIdPublic(int id);
};

#endif
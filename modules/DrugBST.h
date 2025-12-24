#ifndef DRUGBST_H
#define DRUGBST_H
#include <string>
#include <fstream>
using namespace std;

struct Drug
{
    string name;
    Drug *left;
    Drug *right;
    Drug(string n); // automatically initiallizes the res
};

class DrugBST
{
private:
    Drug *root;
    Drug *insert(Drug *node, string name);
    bool search(Drug *node, string name);
    void inorder(Drug *node);
    void inorderToFile(Drug *node, ofstream &out);

public:
    DrugBST();
    void addDrug(string name);
    void findDrug(string name);
    void displayDrugs();
    void exportToFile(const string &filename);
};

#endif
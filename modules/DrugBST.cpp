#include "DrugBST.h"
#include <iostream>
using namespace std;

// Drug constructor
Drug::Drug(string n, int i, int quan, string expiry) : name(n), id(i), quantity(quan), expiryDate(expiry), left(nullptr), right(nullptr) {}

// DrugBST constructor
DrugBST::DrugBST() : root(nullptr) {}

// Insert into BST
Drug *DrugBST::insert(Drug *node, string name, int id, int quantity, string expiryDate)
{
    if (!node)
        return new Drug(name, id, quantity, expiryDate);
    if (name < node->name)
        node->left = insert(node->left, name, id, quantity, expiryDate);
    else if (name > node->name)
        node->right = insert(node->right, name, id, quantity, expiryDate);
    return node;
}

// Search by name in BST
bool DrugBST::searchByName(Drug *node, string name)
{
    if (!node)
        return false;
    if (node->name == name)
        return true;
    if (name < node->name)
        return searchByName(node->left, name);
    return searchByName(node->right, name);
}

// Search by id in BST
bool DrugBST::searchById(Drug *node, int id)
{
    if (!node)
        return false;
    if (node->id == id)
        return true;
    if (id < node->id)
        return searchById(node->left, id);
    return searchById(node->right, id);
}

// In-order traversal
void DrugBST::inorder(Drug *node)
{
    if (!node)
        return;
    inorder(node->left);
    cout << node->name << ", " << node->id << ", " << node->quantity << ", " << node->expiryDate << endl;
    inorder(node->right);
}
// to export in inorder manner
void DrugBST::inorderToFile(Drug *node, ofstream &out)
{
    if (!node)
        return;
    inorderToFile(node->left, out);
    out << node->name << " "
        << node->id << " "
        << node->quantity << " "
        << node->expiryDate << "\n";
    inorderToFile(node->right, out);
}
void DrugBST::exportToFile(const string &filename)
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    out << "name id quantity expiryDate\n";
    inorderToFile(root, out);

    out.close();
    cout << "Drugs exported to: " << filename << endl;
}

// Public methods
void DrugBST::addDrug(string name, int id, int quantity, string expiryDate)
{
    root = insert(root, name, id, quantity, expiryDate);
}

void DrugBST::findDrugName(string name)
{
    cout << "Searching for " << name << ": "
         << (searchByName(root, name) ? "Found" : "Not Found") << endl;
}

void DrugBST::findDrugId(int id)
{
}

void DrugBST::displayDrugs()
{
    cout << "Drug list (sorted):" << endl;
    inorder(root);
}
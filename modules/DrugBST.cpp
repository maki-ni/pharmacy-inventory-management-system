#include "DrugBST.h"
#include "DateUtils.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Drug constructor
Drug::Drug(string n, int i, int quan, string expirty) : name(n), id(i), quantity(quan), expiryDate(expirty), left(nullptr), right(nullptr) {}

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
    else
    {
        // NAME MATCHES: The drug already exists!
        // Increment the quantity instead of creating a new node
        node->quantity += quantity;

        // Optional: Update the expiry date if the new batch is different
        node->expiryDate = expiryDate;

        cout << "Update: Added " << quantity << " to existing stock of " << name << endl;
    }
    return node;
}

Drug *DrugBST::deleteByName(Drug *node, const string &name)
{
    if (!node)
        return nullptr;

    if (name < node->name)
        node->left = deleteByName(node->left, name);
    else if (name > node->name)
        node->right = deleteByName(node->right, name);
    else
    {
        if (!node->left && !node->right)
        {
            delete node;
            return nullptr;
        }

        else if (!node->left)
        {
            Drug *temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right)
        {
            Drug *temp = node->left;
            delete node;
            return temp;
        }

        else
        {

            Drug *succ = node->right;
            while (succ->left)
                succ = succ->left;

            node->name = succ->name;
            node->id = succ->id;
            node->quantity = succ->quantity;
            node->expiryDate = succ->expiryDate;

            node->right = deleteByName(node->right, succ->name);
        }
    }
    return node;
}

// Search in BST
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
// to import before starting the next step
void DrugBST::importFromFile(const string &filename)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string name, expiryDate;
    int id, quantity;

    // Skip header
    string header;
    getline(in, header);

    while (in >> name >> id >> quantity >> expiryDate)
    {
        addDrug(name, id, quantity, expiryDate);
    }

    in.close();
    cout << "Drugs imported from: " << filename << endl;
}

// to export into a separate file
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
    cout << "Searcing for " << id << ": "
         << (searchById(root, id) ? "Found" : "Not Found") << endl;
}

void DrugBST::displayDrugs()
{
    cout << "Drug list (sorted):" << endl;
    inorder(root);
}

void DrugBST::clear(Drug *node)
{
    if (!node)
        return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void DrugBST::clearTree()
{
    clear(root);
    root = nullptr;
}

void DrugBST::collectValidDrugs(Drug *node, vector<Drug> &valid, const string &today)
{
    if (!node)
        return;
    collectValidDrugs(node->left, valid, today);
    if (!isExpired(node->expiryDate, today))
        valid.emplace_back(node->name, node->id, node->quantity, node->expiryDate);
    else
        cout << "Discarded expired drug: " << node->name << endl;
    collectValidDrugs(node->right, valid, today);
}

void DrugBST::discardExpiredFromCSV(const string &filename)
{
    vector<Drug> validDrugs;
    string today = getTodayDate();
    collectValidDrugs(root, validDrugs, today);

    // rebuild BST
    clearTree();
    for (auto &d : validDrugs)
        addDrug(d.name, d.id, d.quantity, d.expiryDate);

    // overwrite CSV
    exportToFile(filename);
}

// returns number of distinct drug nodes
int DrugBST::getDrugTypeCount()
{
    return countNodes(root);
}

// helper to count nodes
int DrugBST::countNodes(Drug *node)
{
    if (!node)
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

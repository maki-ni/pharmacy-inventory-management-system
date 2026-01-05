#include "DrugBST.h"
#include "DateUtils.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include <algorithm>
#include <cctype>

string toLower(const string &s)
{
    string result = s;
    for (char &c : result)
    {
        c = tolower(c);
    }

    return result;
}

// Drug constructor
Drug::Drug(string n, int i, int quan, string expirty, double priceVal) : name(n), id(i), quantity(quan), expiryDate(expirty), price(priceVal), left(nullptr), right(nullptr) {}

// DrugBST constructor
DrugBST::DrugBST() : root(nullptr) {}

// Insert into BST
Drug *DrugBST::insert(Drug *node, string name, int id, int quantity, string expiryDate, double price)
{
    name = toLower(name);
    if (!node)
        return new Drug(name, id, quantity, expiryDate, price);
    if (findById(root, id))
    {
        cerr << "Duplicate ID detected: " << id << endl;
        return node;
    }
    if (quantity <= 0)
    {
        cerr << "Invalid quantity for " << name << endl;
        return node;
    }
    if (price < 0)
    {
        cerr << "Invalid price for " << name << endl;
        return node;
    }

    if (name < node->name)
        node->left = insert(node->left, name, id, quantity, expiryDate, price);
    else if (name > node->name)
        node->right = insert(node->right, name, id, quantity, expiryDate, price);
    else
    {
        // NAME MATCHES: The drug already exists!
        // Increment the quantity instead of creating a new node
        node->quantity += quantity;

        // Optional: Update the expiry date if the new batch is different
        node->expiryDate = expiryDate;
        node->price = price;
        cout << "Update: Added " << quantity << " to existing stock of " << name << endl;
    }
    return node;
}

Drug *DrugBST::deleteByName(Drug *node, const string &name)
{
    if (!node)
        return nullptr;
    string nodeName = toLower(node->name);
    string targetName = toLower(name);

    if (targetName < nodeName)
        node->left = deleteByName(node->left, targetName);
    else if (name > node->name)
        node->right = deleteByName(node->right, targetName);
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
            node->price = succ->price;

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
    string nodeName = toLower(node->name);
    string searchName = toLower(name);
    if (nodeName == searchName)
        return true;
    if (searchName < nodeName)
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

// helper: return pointer to node by id (or nullptr)
Drug *DrugBST::findById(Drug *node, int id)
{
    if (!node)
        return nullptr;
    if (node->id == id)
        return node;

    Drug *leftResult = findById(node->left, id);
    if (leftResult)
        return leftResult;

    return findById(node->right, id);
}

// In-order traversal
void DrugBST::inorder(Drug *node)
{
    if (!node)
        return;
    inorder(node->left);
    cout << "Name: " << node->name
         << " | ID: " << node->id
         << " | Qty: " << node->quantity
         << " | Expiry: " << node->expiryDate
         << " | Price: $" << node->price;
    if (node->quantity < 5)
        cout << "  <-- RESTOCK NEEDED";
    cout << endl;
    inorder(node->right);
}
// to export in inorder manner
void DrugBST::inorderToFile(Drug *node, ofstream &out)
{
    if (!node)
        return;
    inorderToFile(node->left, out);
    // CSV: name,id,quantity,expiry,price
    out << node->name << "," << node->id << "," << node->quantity << "," << node->expiryDate << "," << node->price << "\n";
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

    string line;
    getline(in, line); // skip header

    while (getline(in, line))
    {
        stringstream ss(line);
        string name, expiryDate;
        int id, quantity;
        double price;

        string idStr, quantityStr, priceStr;

        getline(ss, name, ',');
        getline(ss, idStr, ',');
        getline(ss, quantityStr, ',');
        getline(ss, expiryDate, ',');
        getline(ss, priceStr, ',');

        id = stoi(idStr);
        quantity = stoi(quantityStr);
        price = stod(priceStr);

        addDrug(name, id, quantity, expiryDate, price);
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

    out << "name,id,quantity,expiryDate,price\n";
    inorderToFile(root, out);

    out.close();
    cout << "Drugs exported to: " << filename << endl;
}

// Public methods
void DrugBST::addDrug(string name, int id, int quantity, string expiryDate, double price)
{
    root = insert(root, name, id, quantity, expiryDate, price);
}

void DrugBST::findDrugName(string name)
{
    cout << "Searching for " << name << ": "
         << (searchByName(root, name) ? "Found" : "Not Found") << endl;
}

void DrugBST::findDrugId(int id)
{
    Drug *node = findById(root, id);
    if (!node)
    {
        cout << "Drug with ID " << id << " not found." << endl;
        return;
    }

    cout << "Found: " << node->name
         << " | Qty: " << node->quantity
         << " | Price: $" << node->price << endl;

    cout << "Total value: $" << node->quantity * node->price << endl;

    if (node->quantity < 5)
        cout << "RESTOCK NEEDED" << endl;
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
        valid.emplace_back(node->name, node->id, node->quantity, node->expiryDate, node->price);
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
        addDrug(d.name, d.id, d.quantity, d.expiryDate, d.price);

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

#include "DrugBST.h"
#include "DateUtils.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Drug constructor
Drug::Drug(string n, int i, int quan, string expirty) : name(n), id(i), batches({{quan, expirty}}), left(nullptr), right(nullptr) {}

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
            node->batches = succ->batches;

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
    for (auto& b : node->batches) {
        cout << node->name << ", " << node->id << ", " << b.quantity << ", " << b.expiryDate << endl;
    }
    inorder(node->right);
}
// to export in inorder manner
void DrugBST::inorderToFile(Drug *node, ofstream &out)
{
    if (!node)
        return;
    inorderToFile(node->left, out);
    for (auto& b : node->batches) {
        out << node->name << " "
            << node->id << " "
            << b.quantity << " "
            << b.expiryDate << "\n";
    }
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
        Drug* existing = findNodeByIdPublic(id);
        if (existing) {
            existing->batches.push_back({quantity, expiryDate});
        } else {
            addDrug(name, id, quantity, expiryDate);
        }
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

Drug* DrugBST::findNodeByName(Drug *node, string name) {
    if (!node) return nullptr;
    if (node->name == name) return node;
    Drug* left = findNodeByName(node->left, name);
    if (left) return left;
    return findNodeByName(node->right, name);
}

Drug* DrugBST::findNodeById(Drug *node, int id) {
    if (!node) return nullptr;
    if (node->id == id) return node;
    Drug* left = findNodeById(node->left, id);
    if (left) return left;
    return findNodeById(node->right, id);
}

void DrugBST::inorderToString(Drug *node, string &str) {
    if (!node) return;
    inorderToString(node->left, str);
    str += node->name + ", " + to_string(node->id) + "\n";
    for (auto& b : node->batches) {
        str += "  Qty: " + to_string(b.quantity) + ", Expiry: " + b.expiryDate + "\n";
    }
    inorderToString(node->right, str);
}

bool DrugBST::idExists(int id) {
    return idExistsHelper(root, id);
}

bool DrugBST::idExistsHelper(Drug *node, int id) {
    if (!node) return false;
    if (node->id == id) return true;
    return idExistsHelper(node->left, id) || idExistsHelper(node->right, id);
}

bool DrugBST::nameExists(string name) {
    return searchByName(root, name);
}

Drug* DrugBST::findNodeByNamePublic(string name) {
    return findNodeByName(root, name);
}

Drug* DrugBST::findNodeByIdPublic(int id) {
    return findNodeById(root, id);
}

void DrugBST::updateQuantity(string name, int newQty, string newExpiry) {
    Drug* node = findNodeByNamePublic(name);
    if (node) {
        node->batches.push_back({newQty, newExpiry});
        exportToFile("drugs.csv");
    }
}

// Public methods
bool DrugBST::addDrug(string name, int id, int quantity, string expiryDate)
{
    if (idExists(id) || nameExists(name)) return false;
    root = insert(root, name, id, quantity, expiryDate);
    exportToFile("drugs.csv");
    return true;
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
    Drug validDrug(node->name, node->id, 0, ""); // dummy
    validDrug.batches.clear();
    bool hasValid = false;
    for (auto& b : node->batches) {
        if (!isExpired(b.expiryDate, today)) {
            validDrug.batches.push_back(b);
            hasValid = true;
        } else {
            cout << "Discarded expired batch of " << node->name << ": " << b.expiryDate << endl;
        }
    }
    if (hasValid) {
        valid.push_back(validDrug);
    } else {
        cout << "Discarded drug with all expired batches: " << node->name << endl;
    }
    collectValidDrugs(node->right, valid, today);
}

void DrugBST::discardExpiredFromCSV(const string &filename)
{
    vector<Drug> validDrugs;
    string today = getTodayDate();
    collectValidDrugs(root, validDrugs, today);

    // rebuild BST
    clearTree();
    for (auto &d : validDrugs) {
        for (auto &b : d.batches) {
            addDrug(d.name, d.id, b.quantity, b.expiryDate);
        }
    }

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

string DrugBST::getDrugDetailsByName(string name) {
    Drug* node = findNodeByNamePublic(name);
    if (!node) return "Not Found";
    string str = "Drug: " + node->name + ", ID: " + to_string(node->id) + "\n";
    for (size_t i = 0; i < node->batches.size(); ++i) {
        str += "Batch " + to_string(i+1) + ": Qty " + to_string(node->batches[i].quantity) + ", Expiry " + node->batches[i].expiryDate + "\n";
    }
    return str;
}

string DrugBST::getDrugDetailsById(int id) {
    Drug* node = findNodeByIdPublic(id);
    if (!node) return "Not Found";
    string str = "Drug: " + node->name + ", ID: " + to_string(node->id) + "\n";
    for (size_t i = 0; i < node->batches.size(); ++i) {
        str += "Batch " + to_string(i+1) + ": Qty " + to_string(node->batches[i].quantity) + ", Expiry " + node->batches[i].expiryDate + "\n";
    }
    return str;
}

string DrugBST::getAllDrugs() {
    string str = "Drug list (sorted):\n";
    inorderToString(root, str);
    return str;
}

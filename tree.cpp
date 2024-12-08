#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

//---------------------------------------------------------------------------------------------//

class Node {
    public:
    string name;
    string type;
    Node* left;
    Node* right;
    Node* parent;

    // Constructor
    Node(string& nodeName, string nodeType = "River") 
        : name(nodeName), type(nodeType), left(nullptr), right(nullptr), parent(nullptr) {}
};

//---------------------------------------------------------------------------------------------//

class binaryTree {
    private:
    Node* root;

    public:
    // Constructor
    binaryTree() : root(nullptr) {}

//---------------------------------------------------------------------------------------------//

    // Set root node
    void defRoot(Node* node) {
        root = node;
        cout << "Root node set to: " << root->name << endl; // Debugging line
    }

//---------------------------------------------------------------------------------------------//

    // Get starting point
    Node* getRoot() {
        return root;
    }

//---------------------------------------------------------------------------------------------//

    void traverse(Node* node) {
        if (!node) {
            cout << "Tree is empty.\n"; // Debugging line
            return;
        }

        cout << "You are at: " << node->name << " (" << node->type << ")\n";

        // When there is a left or right child
        if (node->left || node->right) {

            cout << "Choose a direction:\n";

            if (node->left) cout << "1. Left (" << node->left->name << ")\n";
            if (node->right) cout << "2. Right (" << node->right->name << ")\n";
            if (node->parent) cout << "3. Backward (" << node->parent->name << ")\n";

            int choice;
            cin >> choice;

            // Choices IO
            if (choice == 1 && node->left) { traverse(node->left); }
            else if (choice == 2 && node->right) { traverse(node->right); }
            else if (choice == 3 && node->parent) { traverse(node->parent); }
            else { cout << "Invalid choice. Try again.\n"; }

        } else {
            cout << "No further tributaries from here.\n";
        }
    }

//---------------------------------------------------------------------------------------------//

    void readCSV(const string& filename) {
        string rootName;

        ifstream file(filename);

        map<string, Node*> nodes;
        string line, name, nameType, left, leftType, right, rightType;

        // Read each row
        while (getline(file, line)) {
            istringstream ss(line);
            getline(ss, name, ',');
            getline(ss, nameType, ',');
            getline(ss, left, ',');
            getline(ss, leftType, ',');
            getline(ss, right, ',');
            getline(ss, rightType, ',');

            // Create/retrieve the current node
            if (nodes.find(name) == nodes.end()) {
                nodes[name] = new Node(name, nameType);
            } else {
                nodes[name]->type = nameType;
            }

            // Create/retrieve the LEFT child
            if (!left.empty()) {
                if (nodes.find(left) == nodes.end()) {
                    nodes[left] = new Node(left, leftType);
                } else {
                    nodes[left]->type = leftType; // Update type if node already exists
                }
                nodes[name]->left = nodes[left];
                nodes[left]->parent = nodes[name];
            }

            // Create/retrieve the RIGHT child
            if (!right.empty()) {
                if (nodes.find(right) == nodes.end()) {
                    nodes[right] = new Node(right, rightType);
                } else {
                    nodes[right]->type = rightType; // Update type if node already exists
                }
                nodes[name]->right = nodes[right];
                nodes[right]->parent = nodes[name];
            }

            // Set root as the first node processed if rootName is empty
            if (rootName.empty()) {
                rootName = name;
            }
        }


        if (!rootName.empty() && nodes.find(rootName) != nodes.end()) {
            defRoot(nodes[rootName]); // Explicitly set root
        }

        file.close();
    }
};

//---------------------------------------------------------------------------------------------//

int main() {
    binaryTree columbiaWatershed;
    columbiaWatershed.readCSV("Columbia.csv");

    // Check if root is set correctly
    if (columbiaWatershed.getRoot() != nullptr) {
        cout << "Starting traversal from root node: " << columbiaWatershed.getRoot()->name << endl; // Debugging line
        columbiaWatershed.traverse(columbiaWatershed.getRoot());
    } else {
        cout << "Root is not set. Exiting program.\n";
    }
    
    return 0;   
}

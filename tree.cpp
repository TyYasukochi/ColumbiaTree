#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

//---------------------------------------------------------------------------------------------//

class Node {
    private:
        string id;
        string parent;
        string left;
        string right;
        string type;
        string name;
        string info;

    public:
        Node(string& nodeID, string& nodeParent, string& nodeLeft, string& nodeRight, string& nodeType, string& nodeName, string& nodeInfo) 
            : id(nodeID), parent(nodeParent), left(nodeLeft), right(nodeRight), type(nodeType), name(nodeName), info(nodeInfo) {}

        string getID() { return id; }
        string getParent() { return parent; }
        string getLeft() { return left; }
        string getRight() { return right; }
        string getType() { return type; }
        string getName() { return name; }
        string getInfo() { return info; }
};

//---------------------------------------------------------------------------------------------//

class BinaryTree {
    private:
        Node* root;
        unordered_map<string, Node*> nodeMap;

    public:
        BinaryTree() : root(nullptr) {}
        BinaryTree(Node* root) : root(root) {}

        void addNode(Node* node) {
            nodeMap[node->getID()] = node;
        }

        Node* getNode(string id) {
            return nodeMap[id];
        }

        Node* getRoot() {
            return root;
        }

        void setRoot(Node* root) {
            this->root = root;
        }

        int size() {
            return nodeMap.size();
        }

        unordered_map<string, Node*> getMap() {
            return nodeMap;
        }
};

//---------------------------------------------------------------------------------------------//

class DataReader {
    public:
        void readCSV(const string& filename, BinaryTree& tree) {
            ifstream file(filename);
            string line, id, parent, left, right, type, name, info;

            while (getline(file, line)) {
                istringstream ss(line);
                getline(ss, id, ',');
                getline(ss, parent, ',');
                getline(ss, left, ',');
                getline(ss, right, ',');
                getline(ss, type, ',');
                getline(ss, name, ',');
                getline(ss, info);

                Node* node = new Node(id, parent, left, right, type, name, info);
                tree.addNode(node);

                if (parent.empty()) {
                    tree.setRoot(node);
                }
            }

            file.close();
        }
};

//---------------------------------------------------------------------------------------------//

class TraversalLogic {
    private:
        Node* currentNode;
        BinaryTree& referenceTree;

        void goToNode(Node* node) {
            currentNode = node;
        }

        void printSplash() {
            cout << endl << "----------------------------------------" << endl;
            cout << "Welcome to the Columbia Watershed Tree!" << endl;
            cout << "This tree is a representation of the Columbia Watershed." << endl;
            cout << "You can navigate the tree by selecting options to go left, right, or back." << endl;
            cout << "Each node has a name and information about the node." << endl;
            cout << "Enjoy exploring the Columbia Watershed!" << endl;
            cout << "----------------------------------------" << endl;
            cout << "Select an option: " << endl << endl;
            cout << "A) Tree Overview" << endl;
            cout << "B) Start Traversal" << endl;
            cout << "Q) Quit" << endl;
        }

        void printOverview() {
            cout << endl;
            cout << "This is a graphical overview of the Columbia Watershed Tree." << endl;
            cout << "This implementation contains " << referenceTree.size() << " explorable branches, including:" << endl;
            
            int branchCount = 0;
            int damCount = 0;
            int tributaryCount = 0;
            for (auto& node : referenceTree.getMap()) {
                if (node.second->getType() == "Branch") {
                    branchCount++;
                } else if (node.second->getType() == "Dam") {
                    damCount++;
                } else if (node.second->getType() == "Tributary") {
                    tributaryCount++;
                }
            }

            cout << "* " << tributaryCount << " tributaries" << endl;
            cout << "* " << damCount << " dams" << endl;
            cout << "* " << branchCount << " branches" << endl << endl;
            cout << "(type anything to return)" << endl;

            string input;
            cin >> input;
        }
        
        void printInfo() {
            cout << endl << "------------- Current Node: -------------" << endl;
            cout << " NAME: " << currentNode->getName() << endl;
            cout << " TYPE: " << currentNode->getType() << endl;
            cout << " INFO: " << currentNode->getInfo() << endl;
            cout << "----------------------------------------" << endl;

            cout << "Select an option: " << endl << endl;
            if (!currentNode->getLeft().empty()) {
                cout << "A) Go Left to " << referenceTree.getNode(currentNode->getLeft())->getName() << endl;
            }
            if (!currentNode->getRight().empty()) {
                cout << "B) Go Right to " << referenceTree.getNode(currentNode->getRight())->getName() << endl;
            }
            if (!currentNode->getParent().empty()) {
                cout << "C) Go Back to " << referenceTree.getNode(currentNode->getParent())->getName() << endl;
            }
            cout << "Q) Quit" << endl;
            
        }
    public:
        TraversalLogic(Node* root, BinaryTree& tree) : currentNode(root), referenceTree(tree) {}

        void printLogic() {
            while (true) {
                printSplash();
                string input;
                cin >> input;

                if (input == "A" || input == "a") {
                    printOverview();
                } else if (input == "B" || input == "b") {
                    break;
                } else if (input == "Q" || input == "q") {
                    return;
                } else {
                    cout << "Invalid input. Please try again." << endl;
                }
            }

            while (true) {
                printInfo();
                string input;
                cin >> input;
                
                if (input == "A" || input == "a") {
                    if (!currentNode->getLeft().empty()) {
                        goToNode(referenceTree.getNode(currentNode->getLeft()));
                    } else {
                        cout << "Invalid input. Please try again." << endl;
                    }
                } else if (input == "B" || input == "b") {
                    if (!currentNode->getRight().empty()) {
                        goToNode(referenceTree.getNode(currentNode->getRight()));
                    } else {
                        cout << "Invalid input. Please try again." << endl;
                    }
                } else if (input == "C" || input == "c") {
                    if (!currentNode->getParent().empty()) {
                        goToNode(referenceTree.getNode(currentNode->getParent()));
                    } else {
                        cout << "Invalid input. Please try again." << endl;
                    }
                } else if (input == "Q" || input == "q") {
                    return;
                } else {
                    cout << "Invalid input. Please try again." << endl;
                }
            }
        }
};

//---------------------------------------------------------------------------------------------//

/*
int main() {
    BinaryTree columbiaWatershed;
    DataReader reader;

    reader.readCSV("Columbia.csv", columbiaWatershed);
    TraversalLogic logic(columbiaWatershed.getRoot(), columbiaWatershed);
    
    logic.printLogic();
    
    return 0;   
}
*/
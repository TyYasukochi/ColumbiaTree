#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "tree.cpp"

using namespace std; 

void testNodeCreateAndGetAttributes() {
    string id = "start", parent = "", left = "branch1", right = "", type = "Branch", name = "Columbia River", info = "Welcome to the entrance of the Columbia River where it connects with the Pacific Ocean.";
    Node node(id, parent, left, right, type, name, info);

    assert(node.getID() == id);
    assert(node.getParent() == parent);
    assert(node.getLeft() == left);
    assert(node.getRight() == right);
    assert(node.getType() == type);
    assert(node.getName() == name);
    assert(node.getInfo() == info);

    cout << "testNodeCreateAndGetAttributes passed.\n";
}

void testBinaryTreeAddAndRetrieveNode() {
    BinaryTree tree;
    string id = "branch1", parent = "start", left = "branch2", right = "river1", type = "Branch", name = "Columbia River", info = "Intersection between Columbia River and Cowlits River.";
    Node* node = new Node(id, parent, left, right, type, name, info);

    tree.addNode(node);

    Node* retrievedNode = tree.getNode(id);
    assert(retrievedNode != nullptr);
    assert(retrievedNode->getID() == id);
    assert(retrievedNode->getName() == name);

    cout << "testBinaryTreeAddAndRetrieveNode passed.\n";
}

void testBinaryTreeSetAndGetRoot() {
    BinaryTree tree;
    string id = "start", parent = "", left = "branch1", right = "", type = "Root", name = "Columbia River", info = "Welcome to the entrance of the Columbia River.";
    Node* root = new Node(id, parent, left, right, type, name, info);

    tree.setRoot(root);
    assert(tree.getRoot() == root);

    cout << "testBinaryTreeSetAndGetRoot passed.\n";
}

void testDataReaderReadCSV() {
    const string filename = "test.csv";
    ofstream file(filename);
    file << "id,parent_id,left_child_id,right_child_id,type,name,info\n";
    file << "start,,,branch1,Branch,Columbia River,Welcome to the entrance of the Columbia River.\n";
    file << "branch1,start,branch2,river1,Branch,Columbia River,Intersection between Columbia River and Cowlits River.\n";
    file << "branch2,branch1,,,Branch,Columbia River,Next intersection.\n";
    file.close();

    BinaryTree tree;
    DataReader reader;
    reader.readCSV(filename, tree);

    Node* root = tree.getRoot();
    assert(root != nullptr);
    assert(root->getID() == "start");
    assert(root->getName() == "Columbia River");

    Node* branch1 = tree.getNode("branch1");
    assert(branch1 != nullptr);
    assert(branch1->getName() == "Columbia River");

    Node* branch2 = tree.getNode("branch2");
    assert(branch2 != nullptr);
    assert(branch2->getName() == "Columbia River");

    remove(filename.c_str());

    cout << "testDataReaderReadCSV passed.\n";
}

int main() {
    testNodeCreateAndGetAttributes();
    testBinaryTreeAddAndRetrieveNode();
    testBinaryTreeSetAndGetRoot();
    testDataReaderReadCSV();

    cout << "All tests passed.\n";
    return 0;
}

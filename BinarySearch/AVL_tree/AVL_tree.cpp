#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <chrono>
using namespace std;
using namespace std::chrono;
// AVL Tree Node Structure
struct Node {
    string key;
    Node* left;
    Node* right;
    int height;
};

// Function to calculate the height of a node
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to update the height of a node
void updateHeight(Node* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

// Function to perform a right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// Function to perform a left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Function to balance the tree
Node* balance(Node* node) {
    updateHeight(node);
    int balanceFactor = height(node->left) - height(node->right);

    // Left heavy, right rotation needed
    if (balanceFactor > 1) {
        if (height(node->left->left) >= height(node->left->right))
            return rightRotate(node);
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    // Right heavy, left rotation needed
    if (balanceFactor < -1) {
        if (height(node->right->right) >= height(node->right->left))
            return leftRotate(node);
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

// Function to insert a key into the AVL tree
Node* insert(Node* root, const string& key) {
    if (root == NULL)
        return new Node{ key, NULL, NULL, 1 };

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;  // Duplicate keys are not allowed

    return balance(root);
}

// Function to search for a key in the AVL tree
bool search(Node* root, const string& key) {
    auto start = high_resolution_clock::now();
    if (root == NULL) {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cout << "Word '" << key << "' not found in the AVL tree." << endl;
        cout << "Search took " << duration.count() << " nanoseconds." << endl;
        return false;
    }
    if (key < root->key) {
        return search(root->left, key);
    }
    else if (key > root->key) {
        return search(root->right, key);
    }
    else {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cout << "Word '" << key << "' found in the AVL tree." << endl;
        cout << "Search took " << duration.count() << " nanoseconds." << endl;
        return true;
    }
}

// Function to read strings from a text file and insert them into the AVL tree
Node* readTextFileAndInsertIntoAVL(const string& filename) {
    Node* root = NULL;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return NULL;
    }

    string line;
    while (getline(file, line)) {
        // Remove leading and trailing whitespaces
        size_t firstNonSpace = line.find_first_not_of(" \t");
        size_t lastNonSpace = line.find_last_not_of(" \t");
        if (firstNonSpace != string::npos && lastNonSpace != string::npos) {
            line = line.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
            root = insert(root, line);
        }
    }

    file.close();
    return root;
}

// Function to perform an in-order traversal of the AVL tree and print its contents
void inOrderTraversal(Node* root) {
    if (root == NULL)
        return;

    inOrderTraversal(root->left);
    cout << root->key << endl;
    inOrderTraversal(root->right);
}

// Function to calculate the height of the AVL tree
int calculateTreeHeight(Node* root) {
    if (root == nullptr)
        return 0;

    int leftHeight = calculateTreeHeight(root->left);
    int rightHeight = calculateTreeHeight(root->right);

    return max(leftHeight, rightHeight) + 1;
}

int main() {
    Node* root = NULL;

    auto start1 = high_resolution_clock::now();
    root = readTextFileAndInsertIntoAVL("dictionary.txt");
    auto stop1 = high_resolution_clock::now();


    cout << "AVL Tree (In-order traversal): ";
    auto start2 = high_resolution_clock::now();
    inOrderTraversal(root);
    auto stop2 = high_resolution_clock::now();
    cout << endl;

    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    auto duration2 = duration_cast<microseconds>(stop2 - start2);


    cout << "Time taken to read file: " << duration1.count() << " microseconds." << endl << endl;
    cout << "Time taken to print file: " << duration2.count() << " microseconds." << endl << endl;

    cout << "Height of the AVL Tree: " << calculateTreeHeight(root) << endl;

    // Search for a words in the AVL Tree
    // This is the exact same testing I did for the simple binary search. I am doing this in order to fairly test execution time
    cout << "Test the first element in the dictionary" << endl;
    search(root, "a");

    cout << "Test the last element in the dictionary" << endl;
    search(root, "zus");

    cout << "Test for the exact middle element" << endl;
    search(root, "lanka");

    cout << "Test for a word that isn't in the dictionary, but is short" << endl;
    search(root, "bha");

    cout << "Test for a  word that isn't in the dictionary, but is long" << endl;
    search(root, "gandienaerljda");

    cout << "Test for a few more words" << endl;
    search(root, "elbows");
    search(root, "symptom");
    search(root, "last");

    return 0;

    string searched;

    while (searched != "quitnow") {
        cout << "-------------------------------------------------" << endl << endl;
        cout << "Enter a word to check if it's in the dictionary. To exit, enter 'quitnow'. ";
        cin >> searched;

        if (search(root, searched)) {
            cout << searched << " found in AVL Tree." << endl;
        }
        else {
            cout << searched << " not found in AVL Tree." << endl;
        }


    }
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Node {
	string data;
	Node* left;
	Node* right;

	Node(string& word) {
		data = word;
		left = NULL;
		right = NULL;
	}
};

Node* insert(Node* root, string& word) {
	if (root == NULL) {
		return new Node(word);
	}
	if (word < root->data) {
		root->left = insert(root->left, word);
	}
	else if (word > root->data) {
		root->right = insert(root->right, word);
	}
	return root;
}

bool search(Node* root, string word) {
	auto start = high_resolution_clock::now();

	if (root == NULL) {
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		cout << "Search took " << duration.count() << " nanoseconds." << endl;
		cout << word << " not found in the dictionary." << endl;

		return false;

	}

	if (word == root->data) {
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		cout << "Search took " << duration.count() << " nanoseconds." << endl;

		cout << word << " found in the dictionary." << endl;
		return true;

	}
	else if (word < root->data) {
		return search(root->left, word);
	}
	else {
		return search(root->right, word);
	}
}

Node* read(string& filename) {
	Node* root = NULL;
	ifstream file(filename);
	string word;

	if (!file.is_open()) {
		cout << "Error opening file: " << filename << endl;
		return NULL;
	}

	while (file >> word) {
		root = insert(root, word);
	}

	file.close();
	return root;
}

void printTree(Node* root) {
	if (root) {
		printTree(root->left);
		cout << root->data << endl;
		printTree(root->right);
	}
}
int countLevels(Node* root) {
	if (root == NULL) {
		return 0;
	}

	int leftLevels = countLevels(root->left);
	int rightLevels = countLevels(root->right);
	return 1 + (leftLevels + rightLevels);
}

int main() {
	// *** I AM READING IN A DIFFERENT FILE THAN THE PROVIDED DICTIONARY FILE. 
	// I PUT THE FIRST 1000 ELEMENTS INTO 'dictionary1000.txt' TO AVOID STACK OVERFLOW ***
	string filename = "dictionary1000.txt";

	auto start1 = high_resolution_clock::now();
	Node* root = read(filename);
	auto stop1 = high_resolution_clock::now();

	auto duration1 = duration_cast<microseconds>(stop1 - start1);

	

	cout << "Words from tree in order: ";
	auto start2 = high_resolution_clock::now();
	printTree(root);
	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2);
	cout << endl;

	cout << "Time taken to read file: " << duration1.count() << " microseconds." << endl << endl;
	cout << "Time taken to print file: " << duration2.count() << " microseconds." << endl << endl;

	int levels = countLevels(root);
	cout << "Levels of the BST: " << levels << endl;

	// Test for words the same was as previous program
	cout << "Test the first element in the dictionary." << endl;
	search(root, "a");

	cout << "Test the last element in the dictionary." << endl;
	search(root, "blocked");

	cout << "Test the middle element in the dictionary." << endl;
	search(root, "arc");

	cout << "Test for a word not in the dictionary." << endl;
	search(root, "elbows");

	cout << "Test for another word not in the dictionary." << endl;
	search(root, "zebras");

	string searched;

	while (searched != "quitnow") {
		cout << "-------------------------------------------------" << endl << endl;
		cout << "Enter a word to check if it's in the dictionary. To exit, enter 'quitnow'. ";
		cin >> searched;

		if (search(root, searched)) {
			cout << searched << " found in BST." << endl;
		}
		else {
			cout << searched << " not found in BST." << endl;
		}


	}
	return 0;
}
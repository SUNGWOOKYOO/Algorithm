#include <iostream>
#include <ctime>
using namespace std;

class Node {
public:
	Node* left = NULL;
	Node* right = NULL;
	int data;
public:
	Node(int _data) {
		data = _data;
	}
};

class BST {
public:
	Node* root;
public:
	BST(int _data) {
		root = new Node(_data);
	}
	
	void deleteAllNodes(Node* current) {
		if (current == NULL) return;
		deleteAllNodes(current->left);
		deleteAllNodes(current->right);
		cout << "delete: " << current->data << " " << endl;
		delete current;
		return;
	}

	~BST() {
		deleteAllNodes(root);
	}
	
	bool search(int _data) {
		Node *cur = root;
		while (true) {
			if (cur->data < _data) {
				if (cur->right == NULL) {
					return false;
				}
				cur = cur->right;
			}
			else if (cur->data > _data) {
				if (cur->left == NULL) {
					return false;
				}
				cur = cur->left;
			}
			else if (cur->data == _data) {
				return true;
			}
		}
	}

	void Insertwhile(int _data) {
		Node *cur = root;
		while (true) {
			if (cur->data < _data) {
				if (cur->right == NULL) {
					cur->right = new Node(_data);
					break;
				}
				cur = cur->right;
			}
			else if (cur->data >_data) {
				if (cur->left == NULL) {
					cur->left = new Node(_data);
					break;
				}
				cur = cur->left;
			}
			else if (cur->data == _data) {
				cout << "already exist " << endl;
				return;
			}
		}
	}

	void insert(int _data) {
		Insertwhile(_data);
	}

	void printallnodes(Node* current) {
		if (current == NULL) return;
		printallnodes(current->left);
		printallnodes(current->right);
		cout << "data: " << current->data << endl;
		return;
	}
};

int main() {
	srand((unsigned int)time(0));
	int randoms[10];
	for (int i = 0; i < 10; ++i) {
		// 5 ~ 20 
		randoms[i] = rand() % (20 - 5) + 5;
	}

	BST bst(randoms[0]);
	cout << "insert ... " << endl;
	for (int k = 1; k < 10; ++k) {
		cout << "insert " << randoms[k] << endl;
		bst.insert(randoms[k]);
	}
	
	bst.printallnodes(bst.root);

	cout << "search ... " << endl;
	for (int k = 0; k < 10; ++k) {
		int num = rand() % (20 - 5 + 1) + 5;
		cout << "find " << num;
		if (bst.search(num)) cout << "  success! " << endl;
		else cout << "  failed! " << endl;
	}
}
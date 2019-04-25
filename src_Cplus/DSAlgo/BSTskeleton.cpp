#include <iostream>
#include <stack>
using namespace std;

class Node {
friend class BinarySearchTree;
public:
    Node() { /* implement here */  }
    Node(int data) { 
		/* implement here */
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}

private:
    int data;
    Node* left;
    Node* right;
};

class BinarySearchTree {
public:
    BinarySearchTree() { 
		/* implement here */
		root = NULL;
	}

	void deleteAllNodes(Node* current) {
		// postorder traversal 
		if (current == NULL) return;
		deleteAllNodes(current->left);
		deleteAllNodes(current->right);
		cout << "delete: " << current->data << " " << endl;
		delete current;
		return;
	}

    ~BinarySearchTree() {
		/* implement here */
		if (root == NULL)
			return;
		deleteAllNodes(root);
	}
    
    void insert(int data) {
        /* implement here */
		if (root == NULL) {
			root = new Node(data);
			return;
		}
		
		Node* cur = root;
		while (true) {
			if (cur->data > data) {
				if (cur->left == NULL) {
					cur->left = new Node(data);
					break;
				}
				cur = cur->left;
			}
			else if (cur->data < data) {
				if (cur->right == NULL) {
					cur->right = new Node(data);
					break;
				}
				cur = cur->right;
			}
			else {
				cout << "data already exists" << endl;
				break;
			}
		}
		return;
    }
   
    bool search(int data) {
        /*implement here */
		if (root == NULL) 
			return false;

		Node *cur = root;
		while (true) {
			if (cur->data < data) {
				if (cur->right == NULL) {
					return false;
				}
				cur = cur->right;
			}
			else if (cur->data > data) {
				if (cur->left == NULL) {
					return false;
				}
				cur = cur->left;
			}
			else if (cur->data == data) {
				return true;
			}
		}
    }

	void remove(int data) {
		/* implement here */
		if (search(data) == false) {
			cout << "data does not exist" << endl;
			return;
		}

		Node* cur = root;
		Node* prev = NULL;
		while (true) {
			if (cur->data < data) {
				prev = cur;
				cur = cur->right;
			}
			else if (cur->data > data) {
				prev = cur;
				cur = cur->left;
			}
			else if (cur->data == data) {
				break;
			}
		}
		// 3 cases
		if (cur->left == NULL && cur->right == NULL) { // case1
			cout << "case1" << endl;
			if (prev->left == cur) {
				delete cur;
				prev->left = NULL;
			}
			else {
				delete cur;
				prev->right = NULL;
			}
			
		}
		else if ((cur->left == NULL) != (cur->right == NULL)) { // case2
			cout << "case2" << endl;
			if (cur->left == NULL) {
				if (prev->left == cur) {
					prev->left = cur->right;
					delete cur;
				}
				else {
					prev->right = cur->right;
					delete cur;
				}
			}
			else {
				if (prev->left == cur) {
					prev->left = cur->left;
					delete cur;
				}
				else {
					prev->right = cur->left;
					delete cur;
				}
			}
		}
		else { //case3
			cout << "case3" << endl;
			Node* prev_predessor = cur;
			Node* predecessor = cur->right;
			while (true) {
				if (predecessor->left == NULL) {
					break;
				}
				prev_predessor = predecessor;
				predecessor = predecessor->left;
			}
			
			//cout << "debug:" << predecessor->data << endl;
			cur->data = predecessor->data;
			if (predecessor->right != NULL) {
				if (prev_predessor->left == predecessor) {
					prev_predessor->left = predecessor->right;
				}
				else {
					prev_predessor->right = predecessor->right;
				}
			}
			delete predecessor;
		}
	}
    
    void print() {
		// post order print iterative version 
		cout << "inorder print iterative version:  ";
		Node *current = root;
        while(current != NULL) {
            if(current->left == NULL) {
                cout << current->data << " ";
                current = current->right;
            }
            else {
                Node *temp = current->left;
                while(temp->right != NULL && temp->right != current) {
                    temp = temp->right;
                }
                
                if(temp->right == NULL) {
                    temp->right = current;
                    current = current->left;
                }
                else {
                    temp->right = NULL;
                    cout << current->data << " ";
                    current = current->right;
                }

            }

        }
    }

	void printallnodes(Node* current) {
		// postorder
		if (current == NULL) return;
		printallnodes(current->left);
		printallnodes(current->right);
		cout << "data: " << current->data << endl;
		return;
	}

	// https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
	void inorderStack() {
		// Base Case 
		if (root == NULL)
			return;

		stack<Node*> s;
		Node* cur = this->root;
		cout << "inorder print using stack version:  ";
		while (cur != NULL || s.empty() == false) {
			// Reach the left most Node of the cur Node 
			while (cur != NULL) {
				s.push(cur);
				cur = cur->left;
			}
			cur = s.top(); s.pop();
			cout << cur->data << " ";

			cur = cur->right;
		}
		cout << endl;
	}

	// https://www.geeksforgeeks.org/iterative-preorder-traversal/
	void preorderStack() {
		// Base Case 
		if (root == NULL)
			return;

		cout << "preorder print using stack version:  ";
		stack<Node*> s;
		//auto cur = this->root;
		s.push(root);
		while (s.empty() == false) {
			auto cur = s.top(); s.pop();
			cout << cur->data << " ";
			if (cur->right != NULL)
				s.push(cur->right);
			if (cur->left != NULL)
				s.push(cur->left );
		}
		cout << endl;
	}

private:
    Node *root;
    int size;
};


int main(int argc, char *argv[]) {
	BinarySearchTree bst;
	
	bst.insert(3);
	bst.insert(5);
	bst.insert(2);
	bst.insert(1);
	bst.insert(4);
	bst.insert(6);
	bst.insert(8);
	bst.insert(10);
	bst.insert(7);
	

	bst.print(); cout << endl;
	//bst.test(); cout << endl;

	cout << "=========== remove =====================" << endl;
	bst.remove(5);
	cout << "=========== remove end =================" << endl;
	
	bst.print(); cout << endl;


	bst.inorderStack();
	bst.preorderStack();
	
	/*
			 3
		   /  \
		  2    6
		 /    /  \
	   1	 4    8
			     / \ 
				7  10
inorder print iterative version:  1 2 3 4 5 6 7 8 10
=========== remove =====================
case3
=========== remove end =================
inorder print iterative version:  1 2 3 4 6 7 8 10
inorder print using stack version:  1 2 3 4 6 7 8 10
preorder print using stack version:  3 2 1 6 4 8 7 10
delete: 1
delete: 2
delete: 4
delete: 7
delete: 10
delete: 8
delete: 6
delete: 3
	*/
    return 0;
}

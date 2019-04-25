#include <iostream>
#include <iomanip>
using namespace std;

class OutofIndexException :public runtime_error {
public:
	OutofIndexException() :runtime_error("") {
		cout << "Out of index" << endl;
	}
};

class Node {
public:
	int data;
	Node* next;
	Node* prev;
	Node(int data) :next(NULL), prev(NULL) {
		this->data = data;
	}
	Node() :next(NULL), prev(NULL) {}
};

class queue {
	Node* head;
	Node* tail;
public:
	queue() {
		head = new Node();
		tail = NULL;
	}

	void push(int value) {
		if (head->next == NULL) {
			head->next = new Node(value);
			head->next->prev = head;
			tail = head->next;
			return;
		}
		Node* tmp = new Node(value);
		tmp->next = head->next;
		tmp->next->prev = tmp;
		head->next = tmp;
		tmp->prev = head;
	}

	int pop() {
		if (head->next == NULL) {
			cout << "data does not exist" << endl;
			throw OutofIndexException();
		}
		if (head->next->next == NULL) {
			int result = tail->data;
			delete tail;
			head->next = NULL;
			return result;
		}
		int result = tail->data;
		tail->prev->next = NULL;
		Node* tmp = tail;
		tail = tail->prev;
		delete tmp;
		return result;
	}

	void display() {
		cout << "[";
		for (auto it = head->next; it != NULL; it = it->next) {
			if (it == head->next)
				cout << it->data;
			else
				cout << setw(15) << it->data;
		}cout << "]" << endl;

		/*
		cout << "[";
		for (auto it = tail; it != head; it = it->prev) {
			if (it == tail)
				cout << it->data;
			else
				cout << setw(15) << it->data;
		}cout << "]" << endl;
		*/
	}
	
	bool empty() {
		if (head->next == NULL)
			return true;
		else
			return false;
	}
	~queue() {
		Node* tmp = head;
		while (true) {
			if (head->next == NULL)
				break;
			head = head->next;
			delete tmp;
			tmp = head;
		}
	}
};
int main() {
	queue Q;
	Q.push(3);
	Q.push(4);
	Q.push(5);
	cout << Q.pop() << endl;
	Q.display();
	cout << Q.pop() << endl;
	Q.display();
	cout << Q.pop() << endl;
	Q.display();
	cout << Q.empty() << endl;

	return 0;
}
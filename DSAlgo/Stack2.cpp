#include<iostream>
#include<iomanip>
using namespace std;

/*
for(1; 2; 4){
	3
}
*/

class OutofIndexException :public runtime_error {
public:
	OutofIndexException() :runtime_error("") {
		cout << "Out of index" << endl;
	}
};

template<class T>
class Node {
public:
	T data;
	Node* next;
	Node* prev;
	Node(T data):next(NULL), prev(NULL) {
		this->data = data;
	}
	Node() :next(NULL), prev(NULL) {}
};

template<class T>
class stack{
	Node<T>* head;
	Node<T>* tail;
public:
	stack() {
		head = new Node<T>();
		tail = NULL;
	}

	void push(T value) {
		/*
		// Insert into the tail position 
		Node<T>* cur = head;
		for (Node<T>* it = head; it!= NULL; it = it->next) {
			cur = it;
		}
		cur->next = new Node<T>(value);
		cur->next->prev = cur ;
		tail = cur->next;
		*/
		if (head->next == NULL) {
			head->next = new Node<T>(value);
			head->next->prev = head;
			tail = head->next;
			return;
		}

		Node<T>* tmp = new Node<T>(value);
		tmp->next = head->next;
		tmp->next->prev = tmp;
		head->next = tmp;
		tmp->prev = head;
	}
	T pop() {
		if (head->next == NULL) {
			cout << "data does not exist" << endl;
			throw OutofIndexException();
		}
		if (head->next->next == NULL) {
			T result = head->next->data;
			delete head->next;
			head->next = NULL;
			return result;
		}
		T result = head->next->data;
		head->next->next->prev = head;
		Node<T>* tmp = head->next;
		head->next = head->next->next;
		delete tmp;
		return result;
	}
	void display() {
		cout << "[";
		for (auto it = head->next; it!= NULL; it = it->next) {
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
	~stack() {
		Node<T>* tmp = head;
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
	stack<int> S;
	S.push(3);
	S.push(4);
	S.push(5);
	cout << S.pop() << endl;
	S.display();
	cout << S.pop() << endl;
	cout << S.empty() << endl;
	cout << S.pop() << endl;
	S.display();
	cout << S.empty() << endl;


	return 0;
}
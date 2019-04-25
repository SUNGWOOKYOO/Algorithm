#include<iostream>
#include<iomanip>
#include<random>
#include<vector>
using namespace std;

class OutofIndexException :public runtime_error {
public:
	OutofIndexException() :runtime_error("") {
		cout << "Out of index" << endl;
	}
};
/*
We should always leave the space pointed to by front.
so, #(capacity - 1) elements can be stored. 
This is because we can differentiate the state between full state and empty state. 
push:	a[++back] = data
pop:	return a[++front]
empty state:	front == back;
full state:		nextidx(back) = front;
*/
class queue {
public:
	int front;
	int back;
	int capacity;
	int* a;
	queue() :front(0), back(0), capacity(0) {
		cout << "default constructor" << endl;
	}
	queue(int _capacity): front(0), back(0){
		if (_capacity < 2) {
			cout<< "capacity should be equal or higher than 2" << endl;
			exit(-1);
		}
		capacity = _capacity;
		a = new int[capacity];
	}

	int nextidx(int idx) {
		if (idx == capacity - 1)
			return 0;
		else
			return idx + 1;
	}
	
	void doubling() {
		// O(capacity)
		int* tmp = new int[2 * capacity];
		int tmp_front = 0;
		int tmp_back = 0;
		for (int idx = nextidx(front); idx != nextidx(back); idx = nextidx(idx)) {
			tmp[++tmp_back] = a[idx];
		}
		front = tmp_front;
		back = tmp_back;
		capacity = 2 * capacity;
		cout << "capacity become " << capacity << endl;
		delete a;
		a = tmp;
	}
	void push(int data) {
		if (capacity == 0) {
			capacity = 2; // #(cap - 1) elements can be stored 
			a = new int[capacity];
			a[++back] = data;
		}
		
		if (nextidx(back) == front) {
			// full state 
			cout << "size doubling" << endl;
			doubling();
			push(data);
		}
		else {
			back = nextidx(back);
			a[back] = data;
			//cout << "push a[" << back << "] = " << a[back] << endl;
		}
	}
	bool empty() {
		return (back == front);
	}
	int pop() {
		if (empty()) {
			throw OutofIndexException();
			exit(-1);
		}
		front = nextidx(front);
		return a[front];
	}
	void display() {
		cout << "[";
		for (int idx = nextidx(front); idx != nextidx(back); idx = nextidx(idx)) {
			if (idx == nextidx(front))
				cout << a[idx];
			else
				cout << setw(15) << a[idx];
		}cout << "]" << endl;
	}
};

int main() {
	srand(unsigned int(time(0)));
	int n = 5;
	queue Q;
	vector<int> vec;
	for (int i = 0; i < 3*n; ++i) {
		int x = rand() % 50;
		vec.push_back(x);
		cout << "generate " << x << endl;
		Q.push(x);
		Q.display();
	}
	
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		Q.pop();
		Q.display();
	}
	return 0;
}
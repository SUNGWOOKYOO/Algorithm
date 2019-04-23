#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

class OutofIndexException :public runtime_error {
public:
	OutofIndexException() :runtime_error("") {
		cout << "Out of index" << endl;
	}
};

template <class T>
class stack {
private:
	int capacity;
	int top_idx;
	T* arr;
public:
	stack() {}
	stack(int size, T initial_value) {
		// O(size)
		capacity = size;
		arr = new T[capacity];
		for (int i = 0; i < capacity; ++i) {
			arr[i] = initial_value;
		}
		top_idx = -1;
	}
	void resize(int new_size, T initial_value) {
		delete arr;
		capacity = new_size;
		arr = new T[capacity];
		for (int i = 0; i < capacity; ++i) {
			arr[i] = initial_value;
		}
		top_idx = -1;
	}
	void resize(int new_size) {
		delete arr;
		capacity = new_size;
		arr = new T[capacity];
		top_idx = -1;
	}
	T operator[](int idx) {
		if (idx > top_idx) {
			throw OutofIndexException();
			return -1;
		}
		return arr[idx];
	}
	T pop() {
		if ((top_idx <= capacity) && (top_idx != -1)) {
			return arr[--top_idx];
		}
		else throw OutofIndexException();
	}
	void push(T value) {
		if (top_idx < capacity) {
			arr[++top_idx] = value;
		}
		else throw OutofIndexException();
	}
	bool empty() {
		if (top_idx == -1) {
			return true;
		}
		else return false;
	}
	void display() {
		cout << "[";
		for (int i = 0; i <= top_idx; ++i) {
			if (i == 0)
				cout << arr[i];
			else
				cout << setw(15) << arr[i];
		}cout << "]" <<endl;
	}
	int getCapacity() {
		return capacity;
	}
	~stack() {
		delete arr;
	}
};

int main() {

	stack<int> S;
	S.resize(3);
	S.push(3);
	S.push(2);
	S.display();
	cout << S.getCapacity() << endl;

	return 0;
}
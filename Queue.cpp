#include <iostream>
#include <iomanip>
using namespace std;

class OutofIndexException :public runtime_error {
public:
	OutofIndexException() :runtime_error("") {
		cout << "Out of index" << endl;
	}
};

template <class T>
class queue {
private:
	int capacity;
	int back_idx;
	int front_idx;
	T* arr;
public:
	queue() {}
	queue(int size, T initial_value) {
		// O(size)
		capacity = size;
		arr = new T[capacity];
		for (int i = 0; i < capacity; ++i) {
			arr[i] = initial_value;
		}
		back_idx = -1;
		front_idx = -1;
	}
	void resize(int new_size, T initial_value) {
		delete arr;
		capacity = new_size;
		arr = new T[capacity];
		for (int i = 0; i < capacity; ++i) {
			arr[i] = initial_value;
		}
		back_idx = -1;
		front_idx = -1;
	}
	void resize(int new_size) {
		delete arr;
		capacity = new_size;
		arr = new T[capacity];
		back_idx = -1;
		front_idx = -1;
	}
	T operator[](int idx) {
		if (idx > back_idx) {
			throw OutofIndexException();
			return -1;
		}
		return arr[idx];
	}
	T pop() {
		if ((back_idx <= capacity) && (front_idx < back_idx )) {
			return arr[++front_idx];
		}
		else throw OutofIndexException();
	}
	void push(T value) {
		if (back_idx < capacity) {
			arr[++back_idx] = value;
		}
		else throw OutofIndexException();
	}
	bool empty() {
		if (front_idx == back_idx) {
			return true;
		}
		else return false;
	}
	void display() {
		cout << "[";
		for (int i = (front_idx + 1); i <= back_idx; ++i) {
			if (i == (front_idx + 1))
				cout << arr[i];
			else
				cout << setw(15) << arr[i];
		}cout << "]" << endl;
	}
	int getCapacity() {
		return capacity;
	}
	~queue() {
		delete arr;
	}
};

int main() {
	queue<int> Q;
	Q.resize(100);
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
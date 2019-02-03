#include<iostream>
#include<vector>
using namespace std;

/*
using stl, we can use heap easily
https://www.geeksforgeeks.org/heap-using-stl-c/
*/
// https://www.geeksforgeeks.org/binary-heap/
class priority_queue {
private:
	int n;
	vector<int> A;
public:
	priority_queue(vector<int> _A) {
		//cout << "Constructor!" << endl;
		n = _A.size();
		//cout << "n: " << n << endl;
		A.resize(n);
		for (int i = 0; i < n; ++i) {
			A[i] = _A[i];
			//cout << A[i] << " ";
		}//cout << endl;
		
		build_min_heap();
	}
	~priority_queue() {
		//cout << "Destructor! " << endl;
	}

	void swap(int i, int j) {
		//cout << "swap " << "A[" << i << "]" << " with " << "A[" << j << "]" << endl;
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}

	// O(V) 
	void build_min_heap() {
		//cout << "build max heap! " << endl;
		for (int i = ((n - 1)>> 1); i >= 0; --i)
			heapify(i);
	}
	void print_pq() {
		//cout << "print heap size " << n << endl;
		for (int i = 0; i < n; ++i) {
			cout << A[i];
			if (i < n - 1) cout << " ";
		}
		cout << endl;
	}

	// O(logV)
	void heapify(int i) {
		//cout << "heapify" << endl;
		if (i > n - 1) return;
		int left = (i << 1) + 1;
		int right = (i << 1) + 2;
		int smallest = i;

		if ((left < n) && (A[i] > A[left])) smallest = left;
		if ((right < n) && (A[smallest] > A[right])) smallest = right;

		if (smallest < n) {
			swap(i, smallest);
		}
		if (smallest != i) {
			//cout << "heapify(" << i << ") called!" << endl;
			heapify(smallest);
		}
	}

	// O(logV)
	void upheapify(int i) {
		int parent = i;
		if ((0 < i) && (i < n))
			parent = (i - 1) >> 1;

		if (parent == i)
			return;

		if (A[parent] > A[i]) {
			swap(parent, i);
			upheapify(parent);
		}
	}

	// O(V)
	int find(int key) {
		int idx = -1;
		for (int i = 0; i < n; ++i) {
			if (A[i] == key) {
				idx = i;
				break;
			}
		}
		return idx;
	}
	
	// O(logV)
	void decrease_key(int i, int new_key) {
		if (new_key > A[i]) {
			cout << "new key is bigger than current key " << endl;
			exit(-1);
		}
		A[i] = new_key;
		upheapify(i);
	}

	// O(logV)
	int pop() {
		if (n < 1) {
			cout << "heap under flow" << endl;
			exit(-1);
		}
		int maxv = A[0];
		A[0] = A[n - 1];
		n = n - 1;
		A.pop_back();
		heapify(0);

		return  maxv;
	}

	// O(logV)
	void push(int data) {
		A.push_back(data);
		n = n + 1;
		upheapify(n - 1);
	}
};

int main() {
	vector<int> A = { 3,1,4,1,5,9 };
	

	priority_queue pq(A);
	pq.print_pq();
	pq.push(2);
	pq.print_pq();
	pq.decrease_key(pq.find(9), 1);
	pq.print_pq();
	cout << pq.find(4) << endl;
	/*
1 1 4 3 5 9
1 1 2 3 5 9 4
1 1 1 3 5 2 4
	*/
	return 0;
}
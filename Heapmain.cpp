#include <iostream>
using namespace std;

class Heap {
private:
	int n;
	int* A;
public:
	Heap(int _A[], int _n) {
		cout << "Constructor!" << endl;
		n = _n;
		cout << "n: " << n << endl;
		A = new int[n];
		for (int i = 0; i < n; ++i) {
			A[i] = _A[i];
			cout << A[i] << " ";
		}cout << endl;
	}
	~Heap() {
		cout << "Destructor! " << endl;
		delete[]A;
	}

	void swap(int i, int j) {
		cout << "swap " << "A[" << i << "]" << " with " << "A[" << j << "]" << endl;
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}

	// Build Max heap through Divide and Conquer approach 
	void make_heap(int i) {
		cout << "make_heap(" << i << ")  ";

		int left = (i << 1) + 1;
		int right = (i << 1) + 2;
		int largest = i;

		// base case
		if (left > n - 1) {
			cout << "leaf node! " << endl;
			return;
		}

		make_heap(left);
		make_heap(right);

		//cout << A[left] << " " << A[i] << " " << A[right] << endl;
		if (A[i] < A[left])	largest = left;
		else largest = i;
		if (A[largest] < A[right]) largest = right;

		//debug 
		/*
		cout << "(left: " << left << ",";
		cout << "right: " << right << ",";
		cout << "largest: " << largest << ")" <<endl;
		*/

		//cout << "before swap: ";
		//print_heap();
		if(largest < n) {
		swap(i, largest);
		}
		//cout << "after swap: ";
		//print_heap();

		if (largest != i) {

			// T(n) = 2(2/n) + logn
			// T(n) = O(n) algorithm 
			heapify(largest);

			// T(n) = 3T(2/n) + 1 
			// T(n) = O(n^(log3/log2)) algorithm 
			//make_heap(largest);
		}
	}
	void print_heap(){
		//cout << "print heap size " << n << endl;
		for (int i = 0; i < n; ++i) {
			cout << A[i];
			if (i < n - 1) cout << " ";
		}
		cout << endl;
	}
	
	void heapify(int i) {
		if (i > n - 1) return;
		int left = (i << 1) + 1;
		int right = (i << 1) + 2;
		int largest = i;
		
		if (A[i] < A[left]) largest = left;
		if (A[largest] < A[right]) largest = right;

		if (largest < n) {
			swap(i, largest);
		}
		if (largest != i) {
			cout << "heapify(" << i << ") called!" << endl;
			heapify(largest);
		}
	}
};

int main() {
	int array[] = {5,9,1,3,5,7,6,11,17,10};
	int n = 10;

	Heap h(array, n);
	h.make_heap(0);
	h.print_heap();

}
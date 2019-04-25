#include <iostream>
using namespace std;

// Insertion sort 
#if 0

void insertion_sort(int *A, int N)
{
	int i;
	for (int j = 1; j < N; j++)
	{
		int key = A[j];
		i = j - 1;
		while (i >= 0 && A[i] > key)
		{
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}
#if 0
template<typename T, size_t N>
void func(T(&a)[N]) {
	for (int i = 0; i < N; i++)
	{
		a[i] = a[i] + i;
	}
	cout << a[1] << endl;
}
#endif

int main() 
{
	int A[] = { 31, 41, 59,	26, 41, 58 };
	int N = size(A);
#if 0	
	cout << size(A) << endl;
	for(int i = 0; i<size(A); i++)
	{
		cout << A[i] << endl;
	}

	int *p = A;
	int  (&rf)[size(A)] = A;
	cout << size(rf) << endl;

	cout << "배열 길이 " << sizeof(A)/sizeof(A[0]) << endl;
	cout << "배열 길이 " << size(A) << endl;
	cout << "배열 길이 " << sizeof(p)/sizeof(*p) << endl;

	func(A);

#endif
	for (int i = 0; i < size(A); i++)
	{
		cout << A[i] << endl;
	}

	insertion_sort(A, N);
	cout << "after sorting" << endl;

	for (int i = 0; i < size(A); i++)
	{
		cout << A[i] << endl;
	}

	return 0;
}

#endif 

// merge sort 
#if 1

void merge(int *A, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	// Let L[0 .. n1] and R[0 ..n2] be new arrays
	int *L = new int[n1+1];
	int *R = new int[n2+1];
	for (int i = 0; i < n1; i++)
	{
		L[i] = A[p + i];
	}
	for (int j=0; j < n2; j++)
	{
		R[j] = A[q + j + 1];
	}
	L[n1] = numeric_limits<int>::max();
	R[n2] = numeric_limits<int>::max();
	int i = 1;
	int j = 1;
	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i += 1;
		}
		else
		{
			A[k] = R[j];
			j += 1;
		}
	}

	delete[]L;
	delete[]R;

}

int main()
{
	int A[] = {3,41,52,26,38,57,9,49,8,2,4,5,1,2,3 };
	merge(A, 9, 11, 14);
	//int a = numeric_limits<int>::max();
	//cout << a << endl;

	for (int i = 0; i < size(A); i++)
	{
		cout << A[i] << endl;
	}

	return 0;
}
#endif

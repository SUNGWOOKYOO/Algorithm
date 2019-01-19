#include <iostream>
using namespace std;

class Sort
{
private:
	int *A;
	int N;
public:

	//class definition
#if 1
	Sort(int *a, int sizeofa)
	{
		N = sizeofa;
		A = new int[N];
		for (int i = 0; i < N; i++)
		{
			A[i] = a[i]; //Deep copy
		}
	}
	~Sort()
	{
		delete[]A;
	}
#endif
	void showarray()
	{
		for (int i = 0; i < N; i++)
		{
			cout << A[i] << '\0';
		}
		cout << endl;
	}

	// insertion sort 
#if 1
	void insertion_sort()
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
#endif

	// merger sort 
#if 1
	void merge(int p, int q, int r)
	{
		int n1 = q - p + 1;
		int n2 = r - q;
		// Let L[0 .. n1] and R[0 ..n2] be new arrays
		int *L = new int[n1 + 1];
		int *R = new int[n2 + 1];
		for (int i = 0; i < n1; i++)
		{
			L[i] = A[p + i];
		}
		for (int j = 0; j < n2; j++)
		{
			R[j] = A[q + j + 1];
		}
		L[n1] = numeric_limits<int>::max();
		R[n2] = numeric_limits<int>::max();

		int i = 0;
		int j = 0;
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

	void merge_sort(int p, int r)
	{
		if (p < r)
		{
			int q = (p + r) / 2;
			merge_sort(p, q);
			merge_sort(q + 1, r);
			merge(p, q, r);
		}
	}
#endif 

	// binary search
#if 1
	int binary_search(int low, int high, int X)
	{
		if (low == high)
		{
			if (A[low] == X)
				return low;
			else
				cout << "Not Found" << endl;
			return 0;
		}
		else
		{
			int mid = (low + high) / 2;
			if (A[mid] > X)
				return binary_search(low, mid - 1, X);
			else
				return binary_search(mid + 1, high, X);

		}
	}
#endif

};

int main()
{
	int a[] = { 3,41,52,26,38,57,9,49,8,2,4,5,1,2,3 };
	Sort ob(a, size(a));
	ob.showarray();

	cout << "select a sorting algorithm : " << endl;
	cout << "[a] insertion sort" << "\n" << "[b] merge sort " << endl;
	char select_num;
	cin >> select_num;

	switch (select_num)
	{
	case 'a':
		cout << "insertion sort! " << endl;
		ob.insertion_sort();
		ob.showarray();
		break;

	case 'b':
		cout << "merge sort! " << endl;
		ob.merge_sort(0, size(a) - 1);
		ob.showarray();
		break;
	}

	cout << "Input a number that you wanna find " << endl;
	int wannaFindValue;
	cin >> wannaFindValue;
	cout << ob.binary_search(0, size(a) - 1, wannaFindValue) << "th order[0~ ] " << endl;
	return 0;
}

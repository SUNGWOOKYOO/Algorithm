#include <iostream>
using namespace std;

int find_max_crossing_subarray(int *A, int low, int mid, int high)
{
	// indices for max_sum
	int max_left = low;
	int max_right = low;

	int left_sum = numeric_limits<int>::min();
	int sum = 0;
	for (int i = mid; i > low; i--)
	{
		sum = sum + A[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}
	int right_sum = numeric_limits<int>::min();
	sum = 0;
	for (int j = mid + 1; j < high; j++)
	{
		sum = sum + A[j];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = j;
		}
	}
	return left_sum + right_sum;
}

int find_maximum_subarray(int *A, int low, int high)
{
	int mid;
	int left_sum;
	int right_sum;
	int cross_sum;

	if (high == low)
		return A[low];
	else
	{
		mid = (low + high) / 2;
		left_sum = find_maximum_subarray(A, low, mid);
		right_sum = find_maximum_subarray(A, mid + 1, high);
		cross_sum = find_max_crossing_subarray(A, low, mid, high);

		if (left_sum >= right_sum && left_sum >= cross_sum)
			return left_sum;
		if (right_sum >= left_sum && right_sum >= cross_sum)
			return right_sum;
		return cross_sum;
	}
}


int main()
{
	int A[] = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
	//find_max_crossing_subarray(A, 0, (0+(size(A)-1))/2 ,size(A)-1);
	cout << find_maximum_subarray(A, 0, 14) << endl;

	return 0;
}
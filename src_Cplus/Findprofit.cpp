#include <iostream>
#include <tuple>
#include <algorithm>
using namespace std;

// Divide and Conquer approach
// return (max_profit, min_v, max_v) 
tuple<double, double, double> Findprofit(double* a, int i, int j){
	if (i == j)	return make_tuple(0, a[i], a[i]);

	int mid = (i + j) / 2;
	double left_profit, left_min, left_max;
	tie(left_profit, left_min, left_max) = Findprofit(a, i, mid);

	double right_profit, right_min, right_max;
	tie(right_profit, right_min, right_max) = Findprofit(a, mid + 1, j);

	// algorithm library ... 
	cout << "Debug: " << i << " ~ " << j << endl;
	cout << "(left_profit, min, max): " << left_profit << " " << left_min << " " << left_max << endl;
	cout << "(right_profit, min, max): " << right_profit << " " << right_min << " " << right_max << endl;
	cout << "(cross_profit, min, max): " << (right_max - left_min) << " " << min(left_min, right_min) << " " << max(left_max, right_max) << endl;

	double tmp = std::max(left_profit, right_profit);
	double max_profit = std::max(tmp, (right_max - left_min));
	cout << "maxprofit: " << max_profit << endl;

	return make_tuple(max_profit, min(left_min,right_min), max(left_max, right_max));
}

// incremental approach
double Incremental(double* a, int n) {
	double max_profit = 0;
	double min_v = a[0];
	for (int i = 0; i < n; ++i) {
		min_v = min(a[i], min_v);
		max_profit = max(max_profit, a[i] - min_v);
	}
	return max_profit;
}

int main() {
	int n;
	double* a;
	cout << "Enter n: ";
	cin >> n;
	a = new double[n];
	cout << "Enter input sequence: ";
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	tuple<int, int, int> result = Findprofit(a, 0, n - 1);
	cout << "(max_profit, min, max): " << get<0>(result) << " " << get<1>(result) << " " << get<2>(result) << endl;

	// incremental
	double result2 = Incremental(a, n);
	cout << "max_profit: " << result2 << endl;

	delete[]a;
	return 0;
}
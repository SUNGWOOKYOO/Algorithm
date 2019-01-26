#include <iostream>
#include <tuple>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>
using namespace std;
// 0 - 1 knapsack
int lookup(vector<tuple<int, int>>& items, int** c, int i, int w);
int knapack(vector<tuple<int, int>>& items, int n, int maxw) {
	int** c = new int*[n + 1];
	for (int i = 0; i <= n; ++i) {
		c[i] = new int[maxw + 1];
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= maxw; ++j) {
			c[i][j] = std::numeric_limits<int>::min();
			//cout << setw(10) << "c["<<i<<"]["<<j<<"]";
		}//cout << endl;
	}
	int result = lookup(items, c, n, maxw);

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= maxw; ++j) {
			cout << setw(15) << c[i][j] ;
		}cout << endl;
	}
	return result;
}
int lookup(vector<tuple<int, int>>& items, int** c, int i, int w) {
	cout << "lookup(" << i << "," << w << ")" << endl;
 	if (c[i][w] >= 0) {
		return c[i][w];
	}
	if (i == 0 || w == 0) {
		c[i][w] = 0;
		return 0;
	}
	if (get<1>(items[i]) > w) {
		//c[i][w] = c[i - 1][w];
		c[i][w] = lookup(items, c, i - 1, w);
		return c[i][w];
	}
	else {
		//c[i][w] = max(get<0>(items[i]) + c[i - 1][w - get<1>(items[i])], c[i - 1][w]);
		c[i][w] = max(get<0>(items[i]) + lookup(items, c, i - 1, w - get<1>(items[i])), lookup(items, c, i - 1, w));
		return c[i][w];
	}
}

// iterative 
int knapack_iterative(vector<tuple<int, int>>& items, int n, int maxw) {
	int** c = new int*[n + 1];
	for (int i = 0; i <= n; ++i) {
		c[i] = new int[maxw + 1];
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= maxw; ++j) {
			c[i][j] = std::numeric_limits<int>::min();
			//cout << setw(10) << "c["<<i<<"]["<<j<<"]";
		}//cout << endl;
	}

	for (int i = 0; i <= n; ++i) {
		for (int w = 0; w <= maxw; ++w) {
			if (i == 0 || w == 0)
				c[i][w] = 0;
			else {
				if (get<1>(items[i]) > w) {
					c[i][w] = c[i - 1][w];
				}
				else {
					c[i][w] = max(get<0>(items[i]) + c[i - 1][w - get<1>(items[i])], c[i - 1][w]);
				}
			}

		}
	}
	int result = c[n][maxw];

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= maxw; ++j) {
			cout << setw(15) << c[i][j];
		}cout << endl;
	}
	return result;
}

int main() {
	vector<tuple<int, int>> items;
	int n; 
	cin >> n; 
	int maxw;
	cin >> maxw;

	int* prices = new int[n];
	int* weights = new int[n];
	for (int i = 0; i < n; ++i) 
		cin >> prices[i];
	for (int i = 0; i < n; ++i)
		cin >> weights[i];
	for (int i = 0; i < n; ++i) {
		items.push_back(make_tuple(prices[i], weights[i]));
	}

	items.insert(items.begin(), make_tuple(-1, -1));

	int p = 0;
	for (auto pair : items) {
		cout << setw(10)<< "price[" << p << "]: " << get<0>(pair) << setw(10) << " weight[" << p << "]: " << get<1>(pair) << endl;
		++p;
	}

	int result = knapack(items, n, maxw);
	cout << result;
	int result2 = knapack_iterative(items, n, maxw);
	cout << result2;
	/*
	3
	5
	60 100 120
	1 2 3
	*/
	/*
	    price[0]: -1   weight[0]: -1
    price[1]: 60   weight[1]: 1
    price[2]: 100   weight[2]: 2
    price[3]: 120   weight[3]: 3
lookup(3,5)
lookup(2,5)
lookup(1,5)
lookup(0,5)
lookup(0,4)
lookup(1,3)
lookup(0,3)
lookup(0,2)
lookup(2,2)
lookup(1,2)
lookup(0,2)
lookup(0,1)
lookup(1,0)
    -2147483648              0              0              0              0              0
              0    -2147483648             60             60    -2147483648             60
    -2147483648    -2147483648            100    -2147483648    -2147483648            160
    -2147483648    -2147483648    -2147483648    -2147483648    -2147483648            220
220
			  0             60             60             60             60             60
			  0             60            100            160            160            160
			  0             60            100            160            180            220
220
	*/

}

#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
using namespace std;

void floyd(vector<vector<int>>& w) {
	int n = w.size();
	int INF = 100000;
	vector<int> init_row(n, INF);
	vector<vector<int>> dk(n, init_row);
	vector<vector<vector<int>>> d(n, dk);

	// update shortest path for vertex 0
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			d[0][i][j] = min(d[0][i][j], min(w[i][j], w[i][0] + w[0][j]));
		}
	}

	// update for remainder vertices(1 ~ n-1)
	for (int k = 1; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				d[k][i][j] = min(d[k][i][j], min(d[k-1][i][j], d[k-1][i][k] + d[k-1][k][j]));
			}
		}
	}

	for (auto rows : d[n-1]) {
		for (auto e : rows) {
			cout << setw(10) << e;
		}cout << endl;
	}
	
}

int main() {
	int n;
	cin >> n;
	int INF = 100000;
	vector <int> init_row(n, INF);
	vector<vector<int>> Weight(n, init_row);
	for (auto& rows : Weight) {
		for (auto& e : rows) {
			cin >> e;
		}
	}
	/*
	for (auto rows : Weight) {
		for (auto e : rows) {
			cout << setw(10) << e;
		}cout << endl;
	}
	*/
	/*
input:
	5
	0 3 8 100000 -4
	100000 0 100000 1 7
	100000 4 0 100000 100000
	2 100000 -5 0 100000
	100000 100000 100000 6 0

output:
		 0         1        -3         2        -4
		 3         0        -4         1        -1
		 7         4         0         5         3
		 2        -1        -5         0        -2
		 8         5         1         6         0
	*/
	floyd(Weight);

	return 0;
}
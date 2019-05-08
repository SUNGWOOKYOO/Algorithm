#include<iostream>
#include<tuple>
#include<vector>
#include <algorithm>

using namespace std;

void swap(vector<double>& a, vector<double>::iterator p, vector<double>::iterator r) {
	double tmp = *r;
	*r = *p;
	*p = tmp;
}
vector<double>::iterator find(vector<double>&a, double pivot) {
	for (auto it = a.begin(); it != a.end(); ++it) {
		if (*it == pivot) {
			return it;
		}
	}
	cout << "Not founded" << endl;
	return a.begin();
}

double median_of_medians(vector<double>& a, int z) {
	cout << "======== median_of_medians(vector<double>& a, int " << z << ") ========" << endl;
	vector<vector<double>> partitions;
	for (int j = 0; j < a.size(); j += 5) {
		vector<double>* partition = new vector<double>;
		for (int i = 0; i < 5 && (j + i) < a.size(); ++i) {
			partition->push_back(a[j + i]);
		}
		partitions.push_back(*partition);
	}

	cout << "paritions.size : " << partitions.size() << endl;
	cout << "partitions: " << endl;
	for (auto partition : partitions) {
		for (auto e : partition) {
			cout << e << " ";
		}cout << endl;
	}

	cout << "medians: " << endl;
	vector<double> medians;
	for (auto partition : partitions) {
		sort(partition.begin(), partition.end());
		medians.push_back(partition[partition.size() / 2]);
		/*for (auto e : partition) {
			cout << e << " ";
		}cout << endl;*/
	}

	for (auto e : medians) {
		cout << e << " ";
	}cout << endl;


	for (int i = 0; i < partitions.size(); ++i) {
		partitions.pop_back();
	}

	double pivot;
	if (medians.size() <= 5) {
		sort(medians.begin(), medians.end());
		pivot = medians[medians.size() / 2];
	}
	else {
		pivot = median_of_medians(medians, medians.size() / 2);
	}
	cout << "pivot: " << pivot << endl;

	for (auto e : a) {
		cout << e << " ";
	}cout << endl;

	// https://en.cppreference.com/w/cpp/algorithm/partition
	auto q1 = std::partition(a.begin(), a.end(), [pivot](auto em)->bool {return em < pivot; });
	//cout << "*pivot position: "<< *q1 << endl;
	vector<double>::iterator pivot_pointer = find(a, pivot);
	swap(a, pivot_pointer, q1);

	cout << "after partition:";
	for (auto e : a) {
		cout << e << " ";
	}cout << endl;

	vector<double> low;
	vector<double> high;

	for (auto it = a.begin(); it != q1; it++) {
		low.push_back(*it);
	}

	for (auto it = q1+1; it != a.end(); it++) {
		high.push_back(*it);
	}

	cout << "low list: ";
	for (auto e : low) {
		cout << e << " ";
	}cout << endl;

	cout << "high list: ";
	for (auto e : high) {
		cout << e << " ";
	}cout << endl;

	int k = low.size();
	cout << "z: " << z << endl;
	cout << "k: " << k << endl;
	if (z < k) {
		cout << "z < k" << endl;
		return median_of_medians(low, z);
	}
	else if (z > k) {
		cout << "z > k" << endl;
		return median_of_medians(high, z - k - 1);
	}
	else {
		cout << "z == k" << endl;
		return pivot;
	}
}

int main() {
	/*12
	3 2 1 6 13 5 12 15 11 10 4 9*/
	freopen("input.txt", "r", stdin);
	cout << "Enter input size n : ";
	int n;
	cin >> n;
	cout << n << endl;
	vector<double> p(n);
	for (int i = 0; i < n; ++i) {
		double a;
		cin >> p[i];
	}cout << endl;

	//cout << "result: " << median_of_medians(p, p.size() / 2) << endl;
	cout << "result: " << median_of_medians(p, 3) << endl;
	return 0;
}


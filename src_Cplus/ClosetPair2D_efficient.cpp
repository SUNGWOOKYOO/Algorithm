#include<iostream>
#include<tuple>
#include<vector>
#include<algorithm>

using namespace std;

#define MAXV 1e+8
typedef tuple<double, double> Point;

void print(Point a) {
	cout << "(" << get<0>(a) << "," << get<1>(a) << ")";
}

double distance(Point& a, Point& b) {
	return sqrt(pow(get<0>(a) - get<0>(b), 2) + pow(get<1>(a) - get<1>(b), 2));;
}

Point median_of_medians(vector<Point>& a, int z);

class Comp {
public:
	bool flag;
	Comp(bool b) : flag(b) {}
	bool operator()(Point& a, Point& b) {
		return (this->flag ? get<0>(a) < get<0>(b) : get<1>(a) > get<1>(b));
	}
};

void swap(vector<Point>& a, vector<Point>::iterator p, vector<Point>::iterator r) {
	Point tmp = *r;
	*r = *p;
	*p = tmp;
}
vector<Point>::iterator find(vector<Point>&a, Point point) {
	for (auto it = a.begin(); it != a.end(); ++it) {
		if (*it == point) {
			return it;
		}
	}
	cout << "Not founded" << endl;
	return a.begin();
}

// referenece: https://www.cs.mcgill.ca/~cs251/ClosestPair/ClosestPairDQ.html
// rf2: https://www.geeksforgeeks.org/closest-pair-of-points-onlogn-implementation/
double CloestPairUntil(vector<Point>& p, int n) {
	//cout << "======= CloestPairUntil(p, " << n << ") ========" << endl;

	// Base cases 
	if (n == 1) {
		return MAXV;
	}
	if (n == 2) {
		sort(p.begin(), p.end(), Comp(false));
		/*cout << "p: ";
		for (auto o : p) {
			print(o); cout << " ";
		}cout << endl;*/
		return distance(p[0], p[1]);
	}
	if (n == 3) {
		sort(p.begin(), p.end(), Comp(false));
		/*cout << "p: ";
		for (auto o : p) {
			print(o); cout << " ";
		}cout << endl;*/
		return min({ distance(p[0], p[1]), distance(p[1], p[2]), distance(p[0], p[2]) });
	}

	// Median Of Median algorithm: O(n)
	// 중간값을 O(n) 안에 찾는다. 
	Point pivot = median_of_medians(p, p.size() / 2);

	// Partition : O(n)
	// x 축에대한 approximated 된 pivot 으로 partition 하여 low 와 high list를 얻음.
	auto q1 = std::partition(p.begin(), p.end(), [pivot](Point em)->bool {return get<0>(em) < get<0>(pivot); });
	vector<Point>::iterator pivot_pointer = find(p, pivot);
	swap(p, pivot_pointer, q1);

	vector<Point> low;
	vector<Point> high;
	for (auto it = p.begin(); it != q1; it++) {
		low.push_back(*it);
	}
	for (auto it = q1 + 1; it != p.end(); it++) {
		high.push_back(*it);
	}

	// exception 
	if (abs(low.size() - high.size() >= 2) && (n <= 5)) {
		// duplicate 이 median 주변에 있는경우 1개와 3개로 나눠질 수 있는데 이는 error를 발생시키므로 예외처리
		//cout << "duplicate exist, redistribution" << endl;
		low.clear();
		high.clear();
		sort(p.begin(), p.end(), Comp(true));
		for (auto it = p.begin(); it != p.begin() + p.size() / 2; it++) {
			low.push_back(*it);
		}
		for (auto it = p.begin() + p.size() / 2 + 1; it != p.end(); it++) {
			high.push_back(*it);
		}
		pivot = *(p.begin() + p.size() / 2);
		q1 = p.begin() + p.size() / 2;
	}

	/*cout << "pivot: "; print(pivot); cout << endl;
	cout << "after partiition: ";
	for (auto o : p) {
		print(o); cout << " ";
	}cout << endl;
	cout << "*q1:"; print(*q1); cout << endl;
	cout << "low list: ";
	for (auto o : low) {
		print(o); cout << " ";
	}cout << endl;
	cout << "high list: ";
	for (auto o : high) {
		print(o); cout << " ";
	}cout << endl;*/

	// Divide and Conquer: low와 high를 넣은 것에 주목!
	double dl = CloestPairUntil(low, low.size());
	double dr = CloestPairUntil(high, n - low.size() - 1);
	double d = min(dl, dr);

	/*cout << "======= cond: CloestPairUntil(p, " << n << ") ========" << endl;
	cout << "d: " << d << endl;
	cout << "pivot: "; print(pivot); cout << endl;
	cout << "changed low list: ";
	for (auto o : low) {
		print(o); cout << " ";
	}cout << endl;
	cout << "changed high list: ";
	for (auto o : high) {
		print(o); cout << " ";
	}cout << endl;*/

	// Merge: O(n)
	// low와 high 를 merge()하여 sorted list를 만든다.
	*(p.end() - 1) = pivot;
	std::merge(low.begin(), low.end(), high.begin(), high.end(), p.begin(), Comp(false));
	auto f = [pivot](Point em)->bool {return get<1>(em) > get<1>(pivot); };
	// find pivot index
	for (q1 = p.begin(); f(*q1); q1++);
	// shift 
	if(q1 != p.end() - 1) {
		for (auto it = p.end() - 2; it != q1; --it) {
			*(it + 1) = *it;
		}
		*(q1 + 1) = *q1;
		*q1 = pivot;
	}

	/*cout << "chaged p: ";
	for (auto o : p) {
		print(o); cout << " ";
	}cout << endl;*/

	vector<Point> strip;
	for (int i = 0; i < n; i++) {
		if (abs(get<0>(pivot) - get<0>(p[i])) < d)
			strip.push_back(p[i]);
	}

	/*cout << "strip: ";
	for (auto o : strip) {
		print(o); cout << " ";
	}cout << endl;*/

	// merge 방법을 사용하지 않을 경우, strip은  y 에 대해서 sorted 되어있지 않으므로 sort해야한다.  
	// sort(strip.begin(), strip.end(), Comp(false)); // O(nlogn)
	/*cout << "after strip sort" << endl;
	cout << "strip: ";
	for (auto o : strip) {
		print(o); cout << " ";
	}cout << endl;*/

	// O(n) guaranteed 
	int strip_sz = strip.size();
	for (int i = 0; i < strip_sz - 1; i++) {
		// abs(get<1>(strip[i]) - get<1>(strip[j])) < d 를 만족하는 j는 6개를 넘지 못한다.
		for (int j = i + 1; j < strip_sz && abs(get<1>(strip[i]) - get<1>(strip[j])) < d; j++) {
			d = min(d, distance(strip[i], strip[j]));
		}
	}
	//cout << "update d: " << d << endl;
	return d;
}

int main() {
	//(-4,4) (-3,2) (-2,-1) (-1.5,4) (-1,-2) (0,1) (1.5,2) (2,4) (3,2) (3,0) (4,3) (4,-2)
	freopen("input.txt", "r", stdin);
	/*cout << "Enter input size n : ";*/
	int n;
	cin >> n;
	//cout << endl;
	vector<Point> p(n);
	//cout << "Enter input seq: ";
	for (int i = 0; i < n; ++i) {
		double a, b;
		cin >> a;
		cin >> b;
		p[i] = { a,b };
	}
	//cout << endl;

	cout << CloestPairUntil(p, n) << endl;

	return 0;
}

// referenece: https://brilliant.org/wiki/median-finding-algorithm/
Point median_of_medians(vector<Point>& a, int z) {
	vector<vector<Point>> partitions;
	for (int j = 0; j < a.size(); j += 5) {
		vector<Point>* partition = new vector<Point>;
		for (int i = 0; i < 5 && (j + i) < a.size(); ++i) {
			partition->push_back(a[j + i]);
		}
		partitions.push_back(*partition);
	}

	vector<Point> medians;
	for (auto partition : partitions) {
		sort(partition.begin(), partition.end(), Comp(true));
		medians.push_back(partition[partition.size() / 2]);
	}

	for (int i = 0; i < partitions.size(); ++i) {
		partitions.pop_back();
	}

	Point pivot;
	if (medians.size() <= 5) {
		sort(medians.begin(), medians.end(), Comp(true));
		pivot = medians[medians.size() / 2];
	}
	else {
		pivot = median_of_medians(medians, medians.size() / 2);
	}

	auto q1 = std::partition(a.begin(), a.end(), [pivot](Point em)->bool {return get<0>(em) < get<0>(pivot); });
	vector<Point>::iterator pivot_pointer = find(a, pivot);
	swap(a, pivot_pointer, q1);

	vector<Point> low;
	vector<Point> high;
	for (auto it = a.begin(); it != q1; it++) {
		low.push_back(*it);
	}
	for (auto it = q1 + 1; it != a.end(); it++) {
		high.push_back(*it);
	}

	int k = low.size();
	if (z < k) {
		return median_of_medians(low, z);
	}
	else if (z > k) {
		return median_of_medians(high, z - k - 1);
	}
	else {
		return pivot;
	}
}
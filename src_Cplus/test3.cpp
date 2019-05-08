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
vector<Point>::iterator find(vector<Point>&a, Point pivot) {
	for (auto it = a.begin(); it != a.end(); ++it) {
		if (*it == pivot) {
			return it;
		}
	}
	cout << "Not founded" << endl;
	return a.begin();
}

double CloestPairUntil(vector<Point>& p, vector<Point>::iterator s, vector<Point>::iterator e, int n) {
	if (n == 2) {
		return distance(*s, *e);
	}
	if (n == 3) {
		return min({ distance(*s, *(s+1)), distance(*(s+1), *e), distance(*s, *e) });
	}

	// O(n)
	Point pivot = median_of_medians(p, p.size() / 2);
	//cout << "pivot: "; print(pivot); cout << endl;

	auto q1 = std::partition(p.begin(), p.end(), [pivot](Point em)->bool {return get<0>(em) < get<0>(pivot); });
	vector<Point>::iterator pivot_pointer = find(p, pivot);
	swap(p, pivot_pointer, q1);

	/*cout << "after partiition: ";
	for (auto o : p) {
		print(o); cout << " ";
	}cout << endl;

	cout << "*q1:"; print(*q1); cout << endl;*/

	vector<Point> low;
	vector<Point> high;

	for (auto it = p.begin(); it != q1; it++) {
		low.push_back(*it);
	}

	for (auto it = q1 + 1; it != p.end(); it++) {
		high.push_back(*it);
	}

	/*cout << "low list: ";
	for (auto o : low) {
		print(o); cout << " ";
	}cout << endl;

	cout << "high list: ";
	for (auto o : high) {
		print(o); cout << " ";
	}cout << endl;*/

	//exception 
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
		q1 = p.begin() + p.size() / 2;

		/*cout << "low list: ";
		for (auto o : low) {
			print(o); cout << " ";
		}cout << endl;

		cout << "high list: ";
		for (auto o : high) {
			print(o); cout << " ";
		}cout << endl;*/
	}

	// Divide and Conquer
	double dl = CloestPairUntil(low, s, e,low.size());
	double dr = CloestPairUntil(high, s, e, n - low.size() - 1);
	double d = min(dl, dr);

	cout << "======= CloestPairUntil(p, " << n << ") ========" << endl;
	cout << "low list: ";
	for (auto o : low) {
		print(o); cout << " ";
	}cout << endl;

	cout << "high list: ";
	for (auto o : high) {
		print(o); cout << " ";
	}cout << endl;

	cout << "d: " << d << endl;

	// merge
	vector<Point> L, R;
	for (auto o : low) {
		L.push_back(o);
	}L.push_back({ MAXV ,MAXV });
	for (auto o : high) {
		R.push_back(o);
	}R.push_back({ MAXV ,MAXV });

	vector<Point> strip;
	for (int i = 0; i < n; i++) {
		if (abs(get<0>(pivot) - get<0>(p[i])) < d)
			strip.push_back(p[i]);
	}

	for (auto o : strip) {
		print(o); cout << " ";
	}cout << endl;

	// Implement sorted(by y axis) list using merge method: O(n) 
	sort(strip.begin(), strip.end(), Comp(false)); //O(nlogn)
	// low와 high 를 merge()하여 sorted list를 만든다.
	cout << "after merge" << endl;

	for (auto o : strip) {
		print(o); cout << " ";
	}cout << endl;

	int strip_sz = strip.size();
	for (int i = 0; i < strip_sz - 1; i++)
		// it takes constant time because of break condition 
		for (int j = i + 1; j < strip_sz && get<1>(strip[j]) - get<1>(strip[i]) < d; j++)
			d = min(d, distance(strip[i], strip[j]));
	cout << "update d: " << d << endl;
	return d;
}

//double CloestPair(vector<Point>& p, int n) {
//	median_of_medians(p, p.size() / 2);
//	return CloestPairUntil(p, n);
//}

int main() {
	//(-4,4) (2,4) (1.5,2) (-3,2) (4,3) (3,2) (0,1) (-1,-2) (-1.5,4) (-2,-1) (4,-2) (3,0)
	//(-4,4) (-3,2) (-2,-1) (-1.5,4) (-1,-2) (0,1) (1.5,2) (2,4) (3,2) (3,0) (4,3) (4,-2)
	freopen("input.txt", "r", stdin);
	cout << "Enter input size n : ";
	int n;
	cin >> n;
	cout << endl;
	vector<Point> p(n);
	cout << "Enter input seq: ";
	for (int i = 0; i < n; ++i) {
		double a, b;
		cin >> a;
		cin >> b;
		p[i] = { a,b };
	}cout << endl;

	for (auto o : p) {
		print(o); cout << " ";
	}cout << endl;
	/*print(*(p.end()-1)); cout << endl;*/
	cout << CloestPairUntil(p, p.begin(), p.end() - 1, n) << endl;

	return 0;
}

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
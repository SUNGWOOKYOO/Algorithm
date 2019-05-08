#include<iostream>
#include<tuple>
#include<vector>
#include <algorithm>

using namespace std;
typedef tuple<double, double> Point;

void print(Point a) {
	cout << "(" << get<0>(a) << "," << get<1>(a) << ")";
}

double distance(Point& a, Point& b) {
	return sqrt(pow(get<0>(a) - get<0>(b), 2) + pow(get<1>(a) - get<1>(b), 2));;
}

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

int main() {
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

	//sort(p.begin(), p.end(), Comp(true));
	//(-4,4) (-3,2) (-2,-1) (-1.5,4) (-1,-2) (0,1) (1.5,2) (2,4) (3,2) (3,0) (4,3) (4,-2)
	for (auto o : p) {
		print(o); cout << " ";
	}cout << endl;
	/*swap(p, p.begin() + 1, p.begin() + 4);*/
	Point pivot = p[3];
	cout << "pivot: "; print(pivot); cout << endl;
	auto q1 = std::partition(p.begin(), p.end(), [pivot](auto em)->bool {return em < pivot; });
	for (auto o : p) {
		print(o); cout << " ";
	}cout << endl;
	cout << "*q1: "; print(*q1); cout << endl;
	vector<Point>::iterator pivot_pointer = find(p, pivot);
	swap(p, pivot_pointer, q1);

	for (auto o : p) {
		print(o); cout << " ";
	}cout << endl;

	vector<Point> low;
	vector<Point> high;

	for (auto it = p.begin(); it != q1; it++) {
		low.push_back(*it);
	}

	for (auto it = q1+1; it != p.end(); it++) {
		high.push_back(*it);
	}

	cout << "low list: ";
	for (auto o : low) {
		print(o); cout << " ";; 
	}cout << endl;

	cout << "high list: ";
	for (auto o : high) {
		print(o); cout << " ";;
	}cout << endl;

	return 0;
}
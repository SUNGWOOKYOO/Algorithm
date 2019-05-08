#include<iostream>
#include<tuple>
#include<vector>
#include<algorithm>
using namespace std;
#define FLT_MAX 1e+8
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

double CloestPairUntil(vector<Point>::iterator it, int n) {
	if (n == 2)
		return distance(it[0], it[1]);
	if (n == 3)
		return min({ distance(it[0], it[1]), distance(it[1], it[2]), distance(it[2], it[0]) });
	
	/*nth_element(p.begin(), p.begin() + n / 2 , p.end(), Comp(true));
	print(p[n/2]); cout << endl;*/
	int mid = n / 2;
	double dl = CloestPairUntil(it, mid);
	double dr = CloestPairUntil(it + mid, n - mid);

	//int line = (get<0>(it[n / 2 - 1]) + get<0>(it[n / 2])) / 2;
	Point midPoint = it[mid];
	double d = min(dl, dr);

	vector<Point> strip;
	for (int i = 0; i < n; i++) {		
		if (abs(get<0>(midPoint) - get<0>(it[i])) < d)
			strip.push_back(it[i]);
	}

	sort(strip.begin(), strip.end(), Comp(false));

	int strip_sz = strip.size();
	for (int i = 0; i < strip_sz - 1; i++)
		for (int j = i + 1; j < strip_sz && get<1>(strip[j]) - get<1>(strip[i]) < d; j++)
			d = min(d, distance(strip[i], strip[j]));

	return d;
}

double CloestPair(vector<Point>& p, int n) {
	sort(p.begin(), p.end(), Comp(true));
	return CloestPairUntil(p.begin(), n);
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

	/*nth_element(p.begin(), p.begin() + p.size()/2, p.end(), Comp(true));
	print(p[p.size() / 2]); cout << endl;*/

	/*for (auto pair : p) {
		print(pair);
	}cout << endl; */

	cout << CloestPair(p, n) << endl;

	return 0;
}
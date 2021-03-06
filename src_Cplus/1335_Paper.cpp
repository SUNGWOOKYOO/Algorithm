#include <iostream>
#include <array>
#include <tuple>
using namespace std;

tuple<int,bool> blue(int** a, int i1, int i2, int j1, int j2) {
	//cout << "blue(" << i1 << "," << i2 << "," << j1 << "," << j2 << ")" << endl;
	if ((i1 == i2) && (j1 == j2)) {
		if(a[i1][j1] == 1) return make_tuple(a[i1][j1], true);
		else return make_tuple(a[i1][j1], false);
	}
	tuple<int,bool> o1, o2, o3, o4;
	int midi = i1 + ((i2 - i1) >> 1);
	int midj = j1 + ((j2 - j1) >> 1);
	o1 = blue(a, i1, midi, j1, midj);
	o2 = blue(a, i1, midi, midj + 1, j2);
	o3 = blue(a, midi + 1, i2, j1, midj);
	o4 = blue(a, midi + 1, i2, midj + 1, j2);
	if ((get<1>(o1) == true) && (get<1>(o2) == true) && (get<1>(o3) == true) && (get<1>(o4) == true)) {
		return make_tuple(1,true);
	}
	else {
		return make_tuple(get<0>(o1) + get<0>(o2) + get<0>(o3) + get<0>(o4), false);
	}
}

tuple<int, bool> white(int** a, int i1, int i2, int j1, int j2) {
	//cout << "white(" << i1 << "," << i2 << "," << j1 << "," << j2 << ")" << endl;
	if ((i1 == i2) && (j1 == j2)) {
		if(a[i1][j1] == 0) return make_tuple(1, true);
		else return make_tuple(0, false);
	}
	
	tuple<int, bool> o1, o2, o3, o4;
	int midi = i1 + ((i2 - i1) >> 1);
	int midj = j1 + ((j2 - j1) >> 1);
	o1 = white(a, i1, midi, j1, midj);
	o2 = white(a, i1, midi, midj + 1, j2);
	o3 = white(a, midi + 1, i2, j1, midj);
	o4 = white(a, midi + 1, i2, midj + 1, j2);
	if ((get<1>(o1) == true) && (get<1>(o2) == true) && (get<1>(o3) == true) && (get<1>(o4) == true)) {
		return make_tuple(1, true);
	}
	else {
		return make_tuple(get<0>(o1) + get<0>(o2) + get<0>(o3) + get<0>(o4), false);
	}
}

tuple<int,int> paper(int** a, int i1, int i2, int j1, int j2) {
	return make_tuple(get<0>(blue(a, i1, i2, j1, j2)), get<0>(white(a, i1, i2, j1, j2)));
}


tuple<int, bool, int, bool> paper2(int** a, int i1, int i2, int j1, int j2) {
	//cout << "blue(" << i1 << "," << i2 << "," << j1 << "," << j2 << ")" << endl;
	if ((i1 == i2) && (j1 == j2)) {
		if(a[i1][j1] == 0) return make_tuple(1, true, 0, false);
		else return make_tuple(0, false, 1, true);
	}
	tuple<int, bool, int, bool> o1, o2, o3, o4;
	int midi = i1 + ((i2 - i1) >> 1);
	int midj = j1 + ((j2 - j1) >> 1);
	o1 = paper2(a, i1, midi, j1, midj);
	o2 = paper2(a, i1, midi, midj + 1, j2);
	o3 = paper2(a, midi + 1, i2, j1, midj);
	o4 = paper2(a, midi + 1, i2, midj + 1, j2);
	if ((get<1>(o1) == true) && (get<1>(o2) == true) && (get<1>(o3) == true) && (get<1>(o4) == true)) {
		// if all are white 
		return make_tuple(1, true, 0, false);
	}
	else if ((get<3>(o1) == true) && (get<3>(o2) == true) && (get<3>(o3) == true) && (get<3>(o4) == true)) {
		// if all are blue 
		return make_tuple(0, false, 1, true);
	}
	else {
		int NofW = get<0>(o1) + get<0>(o2) + get<0>(o3) + get<0>(o4);
		int NofB = get<2>(o1) + get<2>(o2) + get<2>(o3) + get<2>(o4);

		return make_tuple(NofW, false, NofB, false);
	}
}

tuple<int, int, int> paper3(int** a, int i1, int i2, int j1, int j2) {
	//cout << "blue(" << i1 << "," << i2 << "," << j1 << "," << j2 << ")" << endl;
	if ((i1 == i2) && (j1 == j2)) {
		if (a[i1][j1] == 0) return make_tuple(1, 0, 0);
		else return make_tuple(0, 1, 1);
	}
	tuple<int, int, int> o1, o2, o3, o4;
	int midi = i1 + ((i2 - i1) >> 1);
	int midj = j1 + ((j2 - j1) >> 1);
	o1 = paper3(a, i1, midi, j1, midj);
	o2 = paper3(a, i1, midi, midj + 1, j2);
	o3 = paper3(a, midi + 1, i2, j1, midj);
	o4 = paper3(a, midi + 1, i2, midj + 1, j2);
	if ((get<2>(o1) == 0) && (get<2>(o2) == 0) && (get<2>(o3) == 0) && (get<2>(o4) == 0)) {
		// if all are white 
		return make_tuple(1, 0, 0);
	}
	else if ((get<2>(o1) == 1) && (get<2>(o2) == 1) && (get<2>(o3) == 1) && (get<2>(o4) == 1)) {
		// if all are blue 
		return make_tuple(0, 1, 1);
	}
	else {
		int NofW = get<0>(o1) + get<0>(o2) + get<0>(o3) + get<0>(o4);
		int NofB = get<1>(o1) + get<1>(o2) + get<1>(o3) + get<1>(o4);

		return make_tuple(NofW, NofB, 2);
	}
}

int main()
{
	/*
	array<array<int, 8>, 8> a = {{{ 1, 1, 0, 0, 0, 0, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 1, 1 },
	{ 0, 0, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 0, 0 },
	{ 1, 0, 0, 0, 1, 1, 1, 1 },
	{ 0, 1, 0, 0, 1, 1, 1, 1 },
	{ 0, 0, 1, 1, 1, 1, 1, 1 },
	{0, 0, 1, 1, 1, 1, 1, 1}} };
	*/
	int n;
	cin >> n;
	int **a = new int*[n];
	for (int i = 0; i < n; ++i) {
		a[i] = new int[n];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> a[i][j];
		}
	}

	//auto result = paper(a, 0, n-1, 0, n-1);
	//cout << "the num of blue paper : " << get<0>(result)<< endl;
	//cout << "the num of white paper : " << get<1>(result) << endl;
	//cout << get<1>(result) << endl;
	//cout << get<0>(result) << endl;

	//auto result2 = paper2(a, 0, n - 1, 0, n - 1);
	//cout << get<0>(result2) << endl;
	//cout << get<2>(result2) << endl;

	auto result3 = paper3(a, 0, n - 1, 0, n - 1);
	cout << get<0>(result3) << endl;
	cout << get<1>(result3) << endl;

	return 0;
}

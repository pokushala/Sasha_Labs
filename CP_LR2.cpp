// CP_SashaLaba2.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <locale.h>
#include<string>
#include <vector>

using namespace std;

const double R2GRAPH_EPSILON = 0.0000001;

#define DEBUG 1

class Zp {
public:
	int p;
	Zp() :p(3) {};
	Zp(int num) : p(num) {};
	~Zp() {};
	const vector<int> remainder() {
		vector<int> v;
		for (int i = 0;i < p;i++) {
			v.push_back(i);
		}
		return v;
	}
	int neg(int a) {
		if (a < 0) {
			//cout << " a: " << a << " p-a:" << p - a;
			return p + a;
		}
		return a;
	}
	int operator+( int& num) {
		num = neg((num) % p);
		return num;
	}

};


class R3vector {

public:
	int x;
	int y;
	int z;
	int p;
	R3vector() : x(0), y(0), z(0), p(3) {};
	//R3vector(double a, double b, double c) : x(a), y(b), z(c) {};
	R3vector(int x, int y, int z, int p) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->p = p;
	}
	R3vector(const R3vector& v) : x(v.x), y(v.y), z(v.z), p(v.p) {};
	~R3vector() {}                              // Destructor

	int neg(int a) {
		if (a < 0) {
			//cout << " a: " << a << " p-a:" << p - a;
			return p + a;
		}
		return a;
	}
	R3vector operator+(const R3vector& v) {
		x = x + v.x;//neg((x + v.x) % p);
		y = y + v.y;//neg((y + v.y) % p);
		z = z + v.z;//neg((z + v.z) % p);
		return *this;
	}

	R3vector& operator+=(const R3vector& v) {
		x = neg((x + v.x) % p);
		y = neg((x + v.y) % p);
		z = neg((x + v.z) % p);
		return *this;
	}

	R3vector operator-(const R3vector& v) {
		//return R3vector(x - v.x, y - v.y, z - v.z);
		x = neg((x - v.x) % p);
		y = neg((y - v.y) % p);
		z = neg((z - v.z) % p);
		return *this;
	}

	R3vector& operator-=(const R3vector& v) {
		x = neg((x - v.x) % p);
		y = neg((y - v.y) % p);
		z = neg((z - v.z) % p);
		return *this;
	}

	R3vector operator*(int num) {
		return R3vector(neg((x*num)%p), neg((y*num)%p), neg((z*num)%p), p);
	}

	R3vector& operator*=(int num) {
		x = neg((x*num) % p);
		y = neg((y*num) % p);
		z = neg((z*num) % p);
		return *this;
	}

	//скалярное произведение

	int operator*(const R3vector& v) { // Scalar product
		return neg((x*v.x + y*v.y + z*v.z) % p);
	}


	// Comparings
	bool operator==(const R3vector& v) const {
		//... return (x == v.x && y == v.y);
		return (
			fabs(x - v.x) <= R2GRAPH_EPSILON &&
			fabs(y - v.y) <= R2GRAPH_EPSILON &&
			fabs(z - v.z) <= R2GRAPH_EPSILON
			);
	}
	bool operator!=(const R3vector& v) const { return !operator==(v); }
	bool operator>=(const R3vector& v) const {
		//... return (x > v.x || (x == v.x && y >= v.y));
		return (x > v.x || (x >= v.x && y >= v.y && z >= v.z));
	}
	bool operator>(const R3vector& v) const {
		//... return (x > v.x || (x == v.x && y > v.y));
		return (x > v.x || (x >= v.x && y > v.y));
	}
	bool operator<(const R3vector& v) const { return !operator>=(v); }
	bool operator<=(const R3vector& v) const { return !operator>(v); }

	void display_vector(string name) {
		cout << name << "=( " << x << " , " << y << " , " << z << " );\n" << endl;
	}
};

inline R3vector operator*(int num, R3vector &v) {
	return R3vector(v.neg((num*v.x) % v.p), v.neg((num*v.y) % v.p), v.neg((num*v.z) % v.p), v.p);
	//v.x = (num*v.x) % v.p;
}


void test1() {
	int x1, y1, z1, p, x2, y2, z2;
	cout << "Число p: ";
	cin >> p;
	cout << endl << "Кординаты первого: ";
	cin >> x1 >> y1 >> z1;
	cout << endl << "Кординаты второго: ";
	cin >> x2 >> y2 >> z2;
	R3vector a(x1, y1, z1, p), b(x2, y2, z2, p);
	cout << "Скалярное произведение: ";
	(a + b).display_vector("jj");
}

bool test2() {
	vector<R3vector> basis;
	int p, n, x, y, z;
	cout << "Значения p и n: ";
	cin >> p >> n;
	for (int i = 0;i < n;i++) {
		cout << endl << "Кординаты "<<i<<"-го: ";
		cin >> x >> y >> z;
		if ((x%p != 0) || (y%p != 0) || (z%p) != 0) {

			basis.push_back(R3vector(x, y, z, p));
		}
		else {
			cout << 0 << endl;
			return 0;
		}
	}
	if (basis.size() > 3) {
		cout << 0 << endl;
		return 0;
	}
	else if (basis.size()==3){
		int a = basis[0].x*basis[1].y*basis[2].z + basis[0].y*basis[1].z*basis[2].x + basis[0].x*basis[1].x*basis[2].y;
		int b = basis[0].z*basis[1].y*basis[2].x + basis[0].x*basis[1].z*basis[2].y + basis[0].y*basis[1].x*basis[2].z;
		if ((a - b) % p == 0) {
			cout << 1 << endl;
			return 1;
		}
		cout << 0 << endl;
		return 0;
	}
	else if (basis.size()==2){
		/*//if ((basis[0].x / basis[1].x == basis[0].y / basis[1].y) && (basis[0].x / basis[1].x == basis[0].z / basis[1].z)) {
		if ((basis[1].x != 0) && (basis[1].y != 0) && (basis[1].z != 0)) {
			if ((basis[0].x / basis[1].x == basis[0].y / basis[1].y) && (basis[0].x / basis[1].x == basis[0].z / basis[1].z)) {
				cout << 0 << endl;
				return 0;
			}
		}
		cout << 1 << endl;
		return 1;
		*/
		if ((basis[0].x == basis[0].y) && (basis[0].x == basis[0].z)) {
			if ((basis[1].x == basis[1].y) && (basis[1].x == basis[1].z)) {
				cout << 0 << endl;
				return 0;
			}
			else {
				cout << 1 << endl;
				return 1;
			}
		}
		basis.push_back(R3vector(1, 1, 1, p));
		int a = basis[0].x*basis[1].y*basis[2].z + basis[0].y*basis[1].z*basis[2].x + basis[0].x*basis[1].x*basis[2].y;
		int b = basis[0].z*basis[1].y*basis[2].x + basis[0].x*basis[1].z*basis[2].y + basis[0].y*basis[1].x*basis[2].z;
		if ((a - b) % p == 0) {
			cout << 1 << endl;
			return 1;
		}
		cout << 0 << endl;
		return 0;

	}
	else {
		cout << 0 << endl;
		return 0;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
#if DEBUG
	test1();
	test1();
	test1();
#else
	test2();
	test2();
	test2();
#endif
	return 0;
}
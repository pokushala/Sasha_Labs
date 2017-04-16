// CP_SashaLaba1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <vector>
#include <string>
#include <locale.h>

using namespace std;

const double R2GRAPH_EPSILON = 0.0000001;


class R3vector{
	
public:
	double x;
	double y;
	double z;
	R3vector() : x(0), y(0), z(0) {};
	//R3vector(double a, double b, double c) : x(a), y(b), z(c) {};
	R3vector(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	R3vector(const R3vector& v) : x(v.x), y(v.y), z(v.z) {};
	~R3vector() {}                              // Destructor

	R3vector operator+(const R3vector& v) const {
		return R3vector(x + v.x, y + v.y, z + v.z);
	}

	R3vector& operator+=(const R3vector& v) {
		x += v.x;
		y += v.y;
		x += v.z;
		return *this;
	}

	R3vector operator-(const R3vector& v) const {
		return R3vector(x - v.x, y - v.y, z - v.z);
	}

	R3vector& operator-=(const R3vector& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	R3vector operator*(double num) const {
		return R3vector(x*num, y*num, z*num);
	}

	R3vector& operator*=(double num) {
		x *= num;
		y *= num;
		z *= num;
		return *this;
	}

//скалярное произведение

	double operator*(const R3vector& v) const { // Scalar product
		return x*v.x + y*v.y + z*v.z;
	}

//длина вектора

	double length() const {
		return sqrt(x*x + y*y + z*z);
	}

//векторное произведение

	R3vector cross(const R3vector &v) const {
		return R3vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	}

//смешанное произведение

	double triple(const R3vector& v1, const R3vector& v2)const {
		return (*this)*v1.cross(v2);
	}

	bool complanar(const R3vector& v1, const R3vector& v2) {
		return (*this).triple(v1, v2) == 0;
	}

//норма

	R3vector& normalize() {
		double l = length();
		if (l >= R2GRAPH_EPSILON) {
			x /= l;
			y /= l;
			z /= l;
		}
		return *this;
	}


//нормаль

	R3vector normal() const {           // Normal to this vector
		return R3vector(y*z, x*z, -2 * x*y);
	}

//угол между векторами

	double angle(const R3vector& v) const {  // Angle from this vector to v
		double a = v * (*this);
		double b = v.length()*(*this).length();
		cout << "verh=" << a << " niz=" << b << endl;
		//double yy = v * normal();
		//return atan2(yy, xx);
		return acos(a / b);
	}

	double vcos(const R3vector& v) const {  // cos from this vector to v
		double a = v * (*this);
		double b = v.length()*(*this).length();
		//cout << "Косинус между векторами = " << a / b;
		if (b == 0) {
			return 0;
		}
		return a / b;
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

inline R3vector operator*(double num, const R3vector& v) {
	return R3vector(num*v.x, num*v.y, num*v.z);
}

class R3point {
public:
	double x;
	double y;
	double z;

	R3point() :                         // Default constructor
		x(0.),
		y(0.),
		z(0.)
	{}

	R3point(const R3point& p) :        // Copy-constructor
		x(p.x),
		y(p.y),
		z(p.z)
	{}

	R3point(double xx, double yy, double zz) :
		x(xx),
		y(yy),
		z(zz)

	{}

	R3point& operator=(const R3point& p) {    // Copy-operator
		x = p.x; 
		y = p.y;
		z = p.z;
		return *this;
	}

	~R3point() {}                              // Destructor

	R3point operator+(const R3point& p) const {
		return R3point(x + p.x, y + p.y, z + p.z);
	}

	R3point operator+(const R3vector& v) const {
		return R3point(x + v.x, y + v.y, z + v.z);
	}

	R3point& operator+=(const R3point& p) {
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}

	R3point& operator+=(const R3vector& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	R3vector operator-(const R3point& p) const {
		return R3vector(x - p.x, y - p.y, z - p.z);
	}

	R3point operator-(const R3vector& v) const {
		return R3point(x - v.x, y - v.y, z - v.z);
	}

	R3point& operator-=(const R3vector& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	R3point& operator-=(const R3point& p) {
		x -= p.x;
		y -= p.y;
		x -= p.z;
		return *this;
	}

	R3point operator*(double num) const {
		return R3point(x*num, y*num, z*num);
	}

	R3point& operator*=(double num) {
		x *= num;
		y *= num;
		z *= num;
		return *this;
	}

	// Comparings
	bool operator==(const R3point& p) const {
		//... return (x == p.x && y == p.y);
		return (
			fabs(x - p.x) <= R2GRAPH_EPSILON &&
			fabs(y - p.y) <= R2GRAPH_EPSILON &&
			fabs(z - p.z) <= R2GRAPH_EPSILON
			);
	}
	bool operator!=(const R3point& p) const { return !operator==(p); }
	bool operator>=(const R3point& p) const {
		//... return (x > p.x || (x == p.x && y >= p.y));
		return (x > p.x || (x >= p.x && y >= p.y));
	}
	bool operator>(const R3point& p) const {
		//... return (x > p.x || (x == p.x && y > p.y));
		return (x > p.x || (x >= p.x && y > p.y));
	}
	bool operator<(const R3point& p) const { return !operator>=(p); }
	bool operator<=(const R3point& p) const { return !operator>(p); }

	double operator*(const R3vector& v) const { // Scalar product
		return x*v.x + y*v.y + z*v.z;
	}

	R3vector& cross(const R3vector &v) const {
		return R3vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	}

	double triple(const R3vector& v1, const R3vector& v2)const {
		return (*this)*v1.cross(v2);
	}

	

	double d_flat_point(R3vector& v, R3vector& n) {
		double result = ((*this)-v)*n / n.length();
		if (n.length() == 0) {
			cout << "Расстояние между точкой и прямой = " << 0 << endl;
			return 0;
		}
		else {
			cout << "Расстояние между точкой и прямой = " << result << endl;
		}
		return result;
	}

	double d_line_line(R3vector& n1, R3vector& n2, R3point& p) {
		
		double result = (*this - p).triple(n1, n2);
		R3vector zero(0, 0, 0);
		if (result == 0) {
			if (n1.cross(n2) == zero) {
				//paralel
				result = (n1.cross((*this) - p)).length() / n1.length();
			}
		}
		cout << "Растояние между прямыми = " << result << endl;
		return result;
	}

	void display_point(string name) {
		cout << name << "=( " << x << " , " << y << " , " << z << " );\n" << endl;
	}
};

inline R3point operator*(double num, const R3point& p) {
	return R3point(num*p.x, num*p.y, num*p.z);
}



R3vector init_v (string name) {
	R3vector v;
	cout << "Введите вектор " << name << ": ";
	cin >> v.x >> v.y >> v.z;
	cout << endl;
	return v;
}

R3point init_p(string name) {
	R3point p;
	cout << "Введите вектор " << name << ": ";
	cin >> p.x >> p.y >> p.z;
	cout << endl;
	return p;
}

int main()
{
	setlocale(LC_ALL, "RU");
	
	//cout << "Задание 1. Косинус между векторами." << endl;
	
	//R3vector a1, b1;
	//a1 = init_v("a1");
	//b1 = init_v("b1");
	//cout << "Косинус между a1 и b1 = " << a1.vcos(b1) << endl;

	/*cout << endl << "Задание 2. Найти расстояние от точки до плоскости по точке и нормали." << endl;
	R3vector c, n;
	R3point p;
	c = init_v("c");
	n = init_v("n");
	p = init_p("p");
	

	
	p.d_flat_point(c, n);
	
	*/
	cout <<endl<< "Задание 3. Найти расстояние между прямыми по нормалям и точкам." << endl;
	
	R3vector v1, v2;
	R3point t1, t2;
	t1 = init_p("t1");
	v1 = init_v("v1");
	t2 = init_p("t2");
	v2 = init_v("v2");
	
	t1.d_line_line(v1, v2, t2);
	
	/*cout <<endl<< "Задание 4. По заданым трем векторам определить являютмя ли они комплонарными." << endl;
	
	R3vector w1, w2, w3;
	w1 = init_v("w1");
	w2 = init_v("w2");
	w3 = init_v("w3");
	cout << "Компланарность векторов: " << w1.complanar(w2, w3) << endl;
	
	*/
	return 0;
}


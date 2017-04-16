// SashaLaba3.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include <iostream>
#include <algorithm>
#include <locale.h>
#include <vector>
/*
class Coord{
private:
	int x;
	int y;
public:
	int getX() {
		return this->x;
	}

	int getY() {
		return this->y;
	}
};*/

typedef struct Coord {//структура дл€ координат вершин и центра
	int x;
	int y;
	void printCoord() {
		std::cout << "(" << x << "," << y << ")" << std::endl;
	}
};

class Polygon {//абстрактный базовый класс
protected:
	int width, height;
	std::vector<Coord> coord;
	//Coord one, two, three, four, center;//координаты вершин и центра
public:
	Polygon(Coord a, int b, int c) : width(b), height(c) {//конструктор дл€ пр€моугольника, коорд. центра и стороны
		coord.push_back(a);
		coord.push_back({ a.x + width / 2, a.y + height / 2 });
		coord.push_back({ a.x + width / 2,a.y - height / 2 });
		coord.push_back({ a.x - width / 2, a.y + height / 2 });
		coord.push_back({ a.x - width / 2,a.y - height / 2 });
	}
	Polygon(Coord a, Coord b, Coord c) { //one(a), two(b), three(c) {//конструктор дл€ треугольника, коорд. вершин
		coord.push_back(a);
		coord.push_back(b);
		coord.push_back(c);
		height = abs(b.y - a.x);
		width = abs(c.x - a.x);
	}
	Polygon(Coord a, int b) : width(b) {
		coord.push_back(a);
	}//конструктор дл€ круга, коорд. центра и радиус
	virtual ~Polygon() {}//виртуальный диструктор
	virtual void param(void) = 0;//виртуальна€ ф-€ вывода параметров
	virtual int area(void) = 0;//виртуальна€ ф-€ площади
	virtual std::vector<Coord> shift(Coord xy) = 0;//виртуальна€ ф-€ переноса
	void printparam() {

		 this->param();
	}
	void printarea(){
		
		std::cout << "ѕлощадь" << this->area() << std::endl;
	}
	void printShift(Coord xy) {
		this->shift(xy);
	}
};

class Rectangle : public Polygon {
public:
	Rectangle(Coord a, int b, int c) : Polygon(a, b, c) {}
	int area()
	{
		return width*height;
	}
	std::vector<Coord> shift(Coord xy) {
		std::cout << "___»змененные координаты пр€моугольника сдвиг ";
		xy.printCoord();
		for each (Coord var in coord) {
			var.x += xy.x;
			var.y += xy.y;
			//std::cout << var.x << var.y << std::endl;
			var.printCoord();
		}
		return coord;
	}
	void param() {
		
		std::cout << "___ѕ–яћќ”√ќЋ№Ќ» ___" << std::endl << "ширина: " << width << std::endl << "высота: " << height << std::endl;
		//std::cout << "координаты вершин: (" << coord[1].x << ',' << coord[1].y << "); (" << coord[2].x << ',' << coord[2].y << "); (" << coord[3].x << ',' << coord[3].y << "); (" << coord[4].x << ',' << coord[4].y << "); " << std::endl;
		//std::cout << "координаты центра: (" << coord[0].x << ',' << coord[0].y << "); " << std::endl;
		std::cout << "координаты центра: ";
		coord[0].printCoord();
		std::cout << "координаты вершин: " << std::endl;
		for (int i = 1;i < coord.size();i++) {
			coord[i].printCoord();
		}
	}
};

class Triangle : public Polygon {
public:
	Triangle(Coord a, Coord b, Coord c) : Polygon(a, b, c) {}
	int area()
	{
		return width*height / 2;
	}
	std::vector<Coord> shift(Coord xy) {
		for each (Coord var in coord) {
			var.x += xy.x;
			var.y += xy.y;
			//std::cout << var.x << var.y << std::endl;
			var.printCoord();
		}
		return coord;
	}
	void param() {
		std::cout << "___“–≈”√ќЋ№Ќ» ___"<< std::endl << "ширина: " << width << std::endl << "высота: " << height << std::endl;
		std::cout << "координаты вершин: " << std::endl;//(" << coord[1].x << ',' << coord[1].y << "); (" << coord[2].x << ',' << coord[2].y << "); (" << coord[3].x << ',' << coord[3].y << "); " << std::endl;
		for (int i = 0;i < coord.size();i++) {
			coord[i].printCoord();
		}
	}
};


class Circle : public Polygon {
public:
	Circle(Coord a, int b) : Polygon(a, b) {}
	int area()
	{
		return 3 * pow(width, 2);
	}
	void param() {
		std::cout << "___ –”√___ " << std::endl << "радиус: " << width << std::endl;
		std::cout << "координаты центра: (" << coord[0].x << ',' << coord[0].y << "); " << std::endl;
	}
	std::vector<Coord> shift(Coord xy) {
		coord[0].x += xy.x;
		coord[0].y += xy.y;
		return coord;
	}
};

int main() {
	setlocale(LC_ALL, "RU");
	Polygon * poly1 = new Rectangle({ 4, 5 }, 18, 20);
	Polygon * poly2 = new Triangle({1,1} ,{100,100}, {-1,-5});
	Polygon * poly3 = new Circle({ 4,7 }, 12);
	poly1->printarea();
	poly2->printarea();
	poly3->printarea();
	poly1->param();
	poly2->printparam();
	poly3->printparam();
	poly1->printShift({200,200});
	poly2->printShift({ 12,-5 });
	poly3->printShift({ -8,-3 });
	delete poly1;
	delete poly2;
	delete poly3;
	return 0;
}

// SashaLaba4.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <locale.h>
#include <vector>
#include<algorithm>
#include<list>
#include <functional>


void arrayListToList(const std::vector <std::list<int> > &src, std::list<int> &dst);
void displayVector(const std::vector <std::list<int> > &src);
//void displayList(std::list<int> &l);
std::list<int> randomList();
std::vector< std::list<int> > randomVector();

std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)//для распечатки списка
{
	for (auto &i : list) {
		ostr << " " << i;
	}
	return ostr;
}

int main()
{
	setlocale(LC_ALL, "RU");
	std::cout << "Лабораторная работа #4. Вариант 13. Александра Якименко" << std::endl;
	std::cout << "Создать и протестить функцию которая формирует список целых чисел dst из массива списков целых чисел scr по правилам:" << \
		std::endl << "-dst содержит только числа из списков, содержащих менее четырех элементов" << std::endl\
		<< "-числа, принадлежащие одному списку отсортированы в порядке убывания" << std::endl \
		<< "-числа принадлежащие разным спискам отсортированы в порядке убывания минимальных элементов списков," \
		<< std::endl << "которым они принадлежали" << std::endl;
	
	const std::vector<std::list<int> > src = { {4,2,1,2},{4,5,3,6},{2,5,6},{13,31},{88,1} };
	std::list<int> dst, dst1;
	std::cout << "\nINITIAL VECTOR\n";
	displayVector(src);
	arrayListToList(src, dst);
	const std::vector<std::list<int> > src1 = randomVector();
	arrayListToList(src1, dst1);
	return 0;
}

void displayVector(const std::vector <std::list<int> > &src) {
	for each (std::list<int> l in src) {
		//displayList(l);
		std::cout << l;
		std::cout << std::endl;
	}
}


/*
void displayList(std::list<int> &l) {
	for each (int elem in l) {
		std::cout << elem << " ";
	}
}
*/

void arrayListToList(const std::vector <std::list<int> > &src, std::list<int> &dst) {
	std::vector <std::list<int> > tmp;

	//sorting function for vector (comare min elements in sortes lists)
	struct {
		bool operator()(const std::list<int> &a, const std::list<int> &b)
		{
			return (a.back() > b.back());
		}
	} cmp;

	for each (std::list<int> l in src) {
		if (l.size() < 4) {
			l.sort(std::greater<int>());
			tmp.push_back(l);
			std::cout << l;
		}
	}
	
	std::cout << "\nSORTED VECTOR\n";
	std::sort(tmp.begin(), tmp.end(), cmp);
	displayVector(tmp);
	
	std::cout << "\nAFTER INSERTING\n";
	std::list<int>::iterator where_insert;
	where_insert = dst.begin();	
	//for each (std::list<int> l in tmp) {
//dst.splice(where_insert, l);
	//}
	for (size_t i = 0; i < tmp.size();i++) {
		dst.splice(where_insert, tmp[i]);
	}
	std::cout << dst;
	tmp.clear();
	std::cout << std::endl;
}

std::list<int> randomList() {
	int length = rand() % 8;
	std::list<int> randList;
	for (int i=0; i < length; i++) {
		randList.push_back(rand() % 100);
	}
	//std::cout << randList;
	return randList;
}

std::vector< std::list<int> > randomVector() {
	int vlength = rand() % 11;
	std::vector< std::list<int> > randVector;
	for (int j = 0;j < vlength;j++) {
		randVector.push_back(randomList());
	}
	std::cout << "\nRANDOM TEST\n";
	displayVector(randVector);
	return randVector;
}
// Sasha_Laba5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <locale.h>
#include <vector>
#include <string>
#include <numeric>


int divided_by_11(std::string num);
bool check(std::vector<int> vnum, int length);
int sum_pow(std::vector<int> seq, int p);
void display_vector(std::vector<int> v);
double average_speed(int num);
std::vector<int> str_to_vec(std::string num);


int main()
{
	setlocale(LC_ALL, "RU");
	std::cout << "Вариант 13. Якименко Александра" << std::endl;
	std::cout << "13. Рассчитать сколько чисел, полученных перестановкой цифр в числе 12345, кратны 11." << std::endl << \
		"Написать версию программы, определяющую это для произвольных заданных чисел." << std::endl;
	divided_by_11("12345");
	std::string num;
	std::cout << "Введите число: ";
	std::cin >> num;
	divided_by_11(num);
	std::cout << "Ввести вектор чисел и значение степени.Вывести сумму степеней чисел." << std::endl;
	sum_pow({ 1,2,10,4,5 }, 3);
	average_speed(15952);
	return 0;
}

void display_vector(std::vector<int> v) {
	for each (int elem in v) {
		std::cout << elem<<" ";
	}
	std::cout << std::endl;
}

std::vector<int> str_to_vec(std::string num){
	std::vector<int> vnum;
	for each(char let in num) {
		vnum.push_back((int)let - '0');
	}
	return vnum;
}

//check does the number devided by 11

bool check(std::vector<int> vnum, int length) {
	int even = 0;
	int odd = 0;
	for (int i = 0;i < length;i++) {
		if (i % 2 == 0) {
			odd += vnum[i];
		}
		else {
			even += vnum[i];
		}
	}
	return (abs(even - odd) % 11 == 0);
}

//find all permutations and check conditions

int divided_by_11(std::string num) {
	int count = 0;
	std::vector<int> vnum = str_to_vec(num);
	int length = vnum.size();
	std::sort(vnum.begin(), vnum.end());
	do {
		if (check(vnum, length)) {
			display_vector(vnum);
			count += 1;
		}
	} while (std::next_permutation(vnum.begin(), vnum.end()));
	std::cout << "Количество кратных 11: " << count << std::endl;
	return count;
}

// task 2

int sum_pow(std::vector<int> seq, int p) {
	//std::transform(seq.begin(), seq.end(), [&p](int& x) { x = static_cast<int>(pow(x, p));});
	for_each(seq.begin(), seq.end(), [&p](int& x) { x = (pow(x, p));});
	display_vector(seq);
	int sum = std::accumulate(seq.begin(), seq.end(), 0);
	std::cout << std::endl << "Сумма:" << sum << std::endl;
	return sum;
}



bool polindrom(int num) {
	std::string snum = std::to_string(num);
	int len = snum.length();
	/*for (int i=0;i < len/2;i++) {
		if (snum[i] != snum[len - i - 1]) {
			return false;
		}
	}
	return true;
	*/
	return std::equal(snum.begin(), snum.begin() + len / 2, snum.rbegin());
}



double average_speed (int num) {
	int newnum;
	std::cout << "Введите новое значение скорости" << std::endl;
	std::cin >> newnum;
	if (newnum < num) {
		std::cout << "Новое показание не может быть меньше начального" << std::endl;
		return 0;
	}
	while (!polindrom(newnum)) {
		newnum++;
	}
	std::cout << "Ближайший палиндром: " << newnum << std::endl;
	std::cout << "Средняя скорость: " << (newnum - num) / 2 << std::endl;
	return (newnum-num)/2;
}
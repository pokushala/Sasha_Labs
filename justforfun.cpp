// SashaLaba2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>
#include <string>
#include <locale.h>
#include <vector>
#include<algorithm>

#define DEBUG 1

std::string incrementSingles(std::string str);
std::string maximizeNumbers(std::string str);


class Number {
public:
	int first_index;
	int last_index;
	int num;
	Number(int first_index, int last_index, int num) {
		this->first_index = first_index;
		this->last_index = last_index;
		this->num = num;
	}
	bool operator== (Number num) {
		return this->num == num.num;
	}
	bool operator== (int num) {
		return this->num == num;
	}
};


std::vector<Number> get_number1(std::string str);

int main()
{
	setlocale(LC_ALL, "RU");
	std::string str;
	std::cout << "������� 13.\n �������� ����������\n 1)��������� ����� ������������� ���� ��� �� 1\n 2)�������� ��� ����� �� ���\n";
#if DEBUG
	std::cout << "������� ������ : ";
	std::getline(std::cin, str);
#else
	str = "9 hey you 9999 lalala 56 some 5 and 56 hoho 0";
	std::cout << "��������� ������: " << str;
#endif
	std::cout << std::endl << "���������� ������1: " << incrementSingles(str) << std::endl;
	std::cout << std::endl << "���������� ������2: " << maximizeNumbers(str) << std::endl;
	return 0;
}

std::string incrementSingles(std::string str) {

	std::vector<Number> number = get_number1(str);
	std::string current_num;
	
	int difference = 0;//������� � ����� ������ � ����� ������
	for each (Number var in number){
		if ((std::count(number.begin(), number.end(), var.num)) == 1) {//���� ���������� ������ �����=1
			var.num++;
			current_num = std::to_string(var.num);
			str.replace(var.first_index + difference, var.last_index - var.first_index, current_num);//��������������
			difference += current_num.size() - (var.last_index - var.first_index);//������� �������
		}

	}
	return str;
}

std::string maximizeNumbers(std::string str) {

	int max_num = 0;
	std::vector<Number> number = get_number1(str);
	std::string current_num;
	for each (Number var in number) {
		max_num = std::max(max_num, var.num);
	}
	current_num = std::to_string(max_num);
	int max_len = current_num.size();
	int difference = 0;
	for (int t = 0;t < number.size();t++) {
		str.replace(number[t].first_index + difference, number[t].last_index - number[t].first_index, current_num);
		//std::cout << "\nfirst " << number[t].first_index << " last " << number[t].last_index << " dif " << difference;
		difference += max_len - (number[t].last_index - number[t].first_index);
	}
	return str;
}

std::vector<Number> get_number1(std::string str) {
	std::vector<Number> number;
	std::string nums = "1234567890";
	std::string current_num;
	size_t i = 0, j = 0;
	while ((i = str.find_first_of(nums, j)) != std::string::npos) {	//���� ���� �����
		j = str.find_first_not_of(nums, i);//������� ��� ��������� �����
		if (j == std::string::npos) {//������ ����� ����� � �����
			j = str.size();
		}
		for (int k = i;k < j;k++) {//���� ����� ���������� � ������� �����
			current_num.push_back(str[k]);
		}
		number.push_back(Number(i, j, std::stoi(current_num)));//���������� ����� � ������ �����
		current_num.clear();
	}
	return number;
}
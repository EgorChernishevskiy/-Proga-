#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;


int num_lines(string file_name) { //подсчёт строк в массиве
	ifstream file(file_name);
	string line;
	int result = 0;
	if (file.is_open()) {
		while (getline(file, line)) {
			result++;
		}
	}
	file.close();
	return result;
}

void Shet(int* a, int n)//сортировка подсчетом
{
	int min = a[0], max = a[0];
	int i, k;
	for (i = 0; i < n; i++)
	{
		if (a[i] < min) min = a[i];
		if (a[i] > max) max = a[i];
	}
	k = max - min + 1;
	int* d = new int[k];//создаем доп массив, заполняем нулями
	for (i = 0; i < k; i++)
		d[i] = 0;
	for (i = 0; i < n; i++)//увеличиваем
		d[a[i] - min]++;
	int q = 0, j;
	for (i = 0; i < k; i++)
	{
		for (j = 1; j <= d[i]; j++)
		{
			a[q] = i + min;
			q++;
		}
	}
}


int main()
{
	
	int size = num_lines("input.txt"); //n-мерность 
	int** array = new int* [size];//инициализация массива 
	for (int i = 0; i < size; i++)
	{
		array[i] = new int[size];
	}
	fstream fi;
	fi.open("input.txt", ios::in);
	
	
	int j, i;
	
	for (i = 0; i < size; i++)//считываем массив из файла
		for (j = 0; j < size; j++)
			fi >> array[i][j];
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			cout << array[i][j] << ' ';
		cout << endl;
	}
	fi.close();

	for (int i = 0; i < size; i++)
		Shet(array[i], size);


	ofstream file;
	file.open("output.txt");
	if (file.is_open()) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				file << array[i][j] << ' ';
			}
			file << endl;
		}
	}
	file.close();

	
	

	return 0;
}

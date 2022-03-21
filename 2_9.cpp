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

int* gapSort1(int*& l, int n) {//по убыванию (сравнивать не соседние элементы, а элементы, находящиеся на каком-то расстоянии. И потом это расстояние сокращать,
											//до тех пор, пока оно не станет равно единицы.)
	int gap = (1.0 * n) / 1.247;
	if (gap < 1) {
		gap = 1;
	}
	while (gap >= 1) {

		for (int j = 0; j < n - gap; j++) {
			if (l[j] < l[j + gap]) {
				int tmp = l[j];
				l[j] = l[j + gap];
				l[j + gap] = tmp;
			}
		}
		gap /= 1.247;
	}
	
	return l;

}

int* gapSort2(int*& l, int n) {//по возрастанию
	int gap = (1.0 * n) / 1.247;
	if (gap < 1) {
		gap = 1;
	}
	while (gap >= 1) {

		for (int j = 0; j < n - gap; j++) {
			if (l[j] > l[j + gap]) {
				int tmp = l[j];
				l[j] = l[j + gap];
				l[j + gap] = tmp;
			}
		}
		gap /= 1.247;
	}

	return l;

}

int** gapSort_start(int**& mas, int n) {
	for (int col = 0; col < n; col++) {
		if (col % 3 == 2) {
			int* a = new int[n];
			for (int i = 0; i < n; i++) {//для каждого 3-его столбца
				a[i] = mas[i][col];
			}

			a = gapSort1(a, n); 

			for (int i = 0; i < n; i++) { 
				mas[i][col] = a[i];
			}
			delete[] a; 
		}
		else////для остальных
		{
			int* b = new int[n];
			for (int i = 0; i < n; i++) {
				b[i] = mas[i][col];
			}

			b = gapSort2(b, n);

			for (int i = 0; i < n; i++) {
				mas[i][col] = b[i];
			}
			delete[] b;
		}
	}
	return mas;

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

	array = gapSort_start(array, size); //применение сортировки


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

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


int* bubbleSort(int* d, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j >= i; j--) {
			if (d[j - 1] > d[j]) {
				int tmp = d[j - 1];
				d[j - 1] = d[j];
				d[j] = tmp;
			}
		}
	}
	return d;
}
int** bubbleSort_start(int** mas, int n) {

	for (int i = 1; i < n; i++) {//сортируем выше побочной диагонали
		int* a = new int[i + 1];
		for (int j = 0; j <= i; j++) {
			a[j] = mas[i - j][j];
		}

		a = bubbleSort(a, i + 1);

		for (int j = 0; j <= i; j++) {
			mas[i - j][j] = a[j];
		}
		delete[] a;
	}

	for (int i = 1; i < n; i++) {//сортируем ниже побочной диагонали
		int* a = new int[n - i];
		int k = 0;
		for (int j = i; j < n; j++) {
			a[k] = mas[n - j][j];
			k++;
		}

		a = bubbleSort(a, n - i);

		k = 0;
		for (int j = i; j < n; j++) {
			mas[n - j][j] = a[k];
			k++;
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

	array = bubbleSort_start(array, size); //применение сортировки


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

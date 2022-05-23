#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

ifstream in("input.txt");

struct People {//структура людей
	string name, duty;
	int stage, salary;
	int day, month, year;
};

void find(vector<People>& hash, int m) {//функция поиска
	int x = 0; cout << "Input salary: "; cin >> x;
	int j = 0;
	int p = 0;
	while (true) {
		p = (x + j) % m;
		j++;
		if (hash[p].salary == x) {
			cout << "Found " << hash[p].name << " " << hash[p].duty << " " << hash[p].day << " " << hash[p].month << " " << hash[p].year << " " << hash[p].stage << " " << hash[p].salary << "\n";
			return;
		}
	}
	cout << "Not found\n";
}

void _run() {
	string str = "";
	vector<People> base;

	for (int i = 0; in.peek() != EOF; ++i) {//считываем файл
		base.resize(i + 1);
		getline(in, str);
		istringstream input(str);
		input >> base[i].name >> base[i].duty >> base[i].day >> base[i].month >> base[i].year >> base[i].stage >> base[i].salary;
	}

	int m = 0; cout << "Input M = "; cin >> m;
	vector<People> hash; hash.resize(m);
	People r;
	r.salary = -1;
	for (int i = 0; i < m; hash[i] = r, ++i);

	for (int i = 0; i < base.size(); ++i) {
		int j = 0;
		int p = 0;
		while (true) {
			p = (base[i].year + j) % m;
			if (hash[p].salary == r.salary) {
				hash[p] = base[i];
				break;
			}
			else
				j++;
		}
	}

	for (int i = 0; i < m; ++i) {
		cout << i << ": ";
		if (hash[i].salary != r.salary)
			cout << hash[i].salary << "\n";
		else
			cout << "NULL\n";
	}

	find(hash, m);
}

int main() {
	_run();

	return 0;
}

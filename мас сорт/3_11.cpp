#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct date {//дата
	int dd, mm, yy;
};

struct people {//данные о человеке
	string Surname; //фамилия
	date DateOfBirth; //дата рождения
	int Salary; //зарплата
	string Position;//должность
	int Experience;//стаж (в мес)

};

date Str_to_Date(string str) {//из строки в дату
	date x;
	string temp = str.substr(0, 2);//день
	x.dd = atoi(temp.c_str());
	temp = str.substr(3, 2);//месяц
	x.mm = atoi(temp.c_str());
	temp = str.substr(6, 4);//год
	x.yy = atoi(temp.c_str());
	return x;
}

vector<people> inFile() {//ввод из файла
	vector<people> x;
	people temp;
	while (in.peek() != EOF) {
		in >> temp.Surname;//фамилия
		in >> temp.Position;//должность
		string tmp;//дата рождения
		in >> tmp;
		temp.DateOfBirth = Str_to_Date(tmp);
		in >> temp.Experience;
		in >> temp.Salary;//зарплата
		x.push_back(temp);
	}
	return x;
}

void print(people x) {//вывод в файл
	out << setw(10) << left << x.Surname;//по левому краю, 10 позиций для фамилии
	out << left << setw(10) << x.Position;
	if (x.DateOfBirth.dd < 10) out << left << '0' << x.DateOfBirth.dd << '.';//добавляем 0
	else out << left << x.DateOfBirth.dd << '.';
	if (x.DateOfBirth.mm < 10) out << '0' << x.DateOfBirth.mm << '.';
	else out << x.DateOfBirth.mm << '.';
	out << left << setw(6) << x.DateOfBirth.yy;//на год 6 позиций
	out << left << setw(3) << x.Experience;
	out << left << setw(10) << x.Salary << endl;//запрлата
	
}

bool operator < (people a, people b) {//переопределяем оператор < в соотвествии с условием
	if (a.Position < b.Position) return true;
	if (a.Position == b.Position && a.Experience < b.Experience) return true;
	if (a.Position == b.Position && a.Experience == b.Experience && a.Salary < b.Salary) return true;
	return false;
}

bool operator > (people a, people b) {
	if (a.Position > b.Position) return true;
	if (a.Position == b.Position && a.Experience > b.Experience) return true;
	if (a.Position == b.Position && a.Experience == b.Experience && a.Salary > b.Salary) return true;
	return false;
}

void bubble_sort(vector<people>& vArray)
{
	for (int i = 0; i < vArray.size(); ++i)
	{
		for (int j = vArray.size() - 1; j > i; --j)
		{
			if (vArray[i] > vArray[j])
			{
				swap(vArray[i], vArray[j]);
			}
		}
	}
}

int main() {
	vector<people> x;
	x = inFile();
	
	bubble_sort(x);
	for (int i = 0; i < x.size(); i++)
		print(x[i]);
	return 0;
}

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <Map>
#include <queue>
#include <fstream>
#include <string>
#include <stack>
#include "Graph.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	vector<Graph> GraphM;
	GraphM.push_back(Graph());
	int now = 0;

	bool w, o;
	int option;
	int optInt;
	int weight;
	int num1, num2;
	string name;
	string name1;
	string name2;
	string name3;
	string opt;


	while (true) {
		cout << endl << "0 - Создать граф " << endl
			<< "1 - Вывести список смежности графа " << endl
			<< "2 - Добавить вершину " << endl
			<< "3 - Удалить вершину " << endl
			<< "4 - Добавить ребро " << endl
			<< "5 - Удалить ребро " << endl
			<< "6 - Вывести список смежности графа в файл " << endl
			<< "7 - Очистить граф " << endl
			<< "8 - Выход " << endl 
			<< "9 - Выберете задание " << endl << endl;
		cout << "Введите номер действия, которое вы хотите сделать: ";
		cin >> option;
		switch (option)
		{
		case 0:
			cout << "Вы хотите загрузить граф из файла? (y - Да, n - Нет): ";
			cin >> opt;
			if (opt == "y") {
				cout << "Введите имя файла: ";
				cin >> name;
				GraphM.push_back(Graph(name));
				now = GraphM.size() - 1;
			}
			else {
				cout << "Введите параметры графа (взвешенность, ориентированность): ";
				cin >> w >> o;
				/*cout << "Введите имя графа: ";
				cin >> name;*/
				GraphM.push_back(Graph(w, o));
				now = GraphM.size() - 1;
			}
			break;
		case 1:
			GraphM[now].Print();
			break;
		case 2:
			cout << "Введите имя вершины которую хотите добавить: ";
			cin >> name;
			GraphM[now].NodeAdd(name);
			break;
		case 3:
			cout << "Введите имя вершины которую хотите удалить: ";
			cin >> name;
			GraphM[now].NodeDel(name);
			break;
		case 4:
			cout << "Введите имена вершин которые хотите соединить (если орграф то в порядке 1 -> 2): " << endl;
			cout << "Имя первой вершины: ";
			cin >> name1;
			cout << "Имя второй вершины: ";
			cin >> name2;
			if (GraphM[now].isWeighted()) {
				cout << "Вес ребра: ";
				cin >> weight;
				GraphM[now].NodeConnect(name1, name2, weight);
			}
			else {
				GraphM[now].NodeConnect(name1, name2, 0);
			}
			break;
		case 5:
			cout << "Введите имена вершин которые хотите разъединить (если орграф то в порядке 1 -> 2): " << endl;
			cout << "Имя первой вершины: ";
			cin >> name1;
			cout << "Имя второй вершины: ";
			cin >> name2;
			GraphM[now].NodeDisconnect(name1, name2);
			break;
		case 6:
			cout << "Введите имя файла: ";
			cin >> name;
			GraphM[now].Writefile(name);
			break;
		case 7:
			GraphM[now].Remove();
			break;
		case 8:
			cout << "Вы действительно хотите выйти? (y - Да, n - Нет): ";
			cin >> opt;
			if (opt == "y") {
				exit(0);
			}
			else {
				cout << "Выход отменен." << endl;
			}
			break;
		case 9:
			cout << endl << "1 - Вывести те вершины орграфа, которые являются одновременно заходящими и выходящими для заданной вершины. " << endl
				<< "2 - Для каждой вершины графа вывести её степень. " << endl
				<< "3 - Построить граф, полученный однократным удалением вершин с нечётными степенями. " << endl
				<< "4 - Проверить, является ли заданный орграф ацикличным. " << endl
				<< "5 - Найти все достижимые из данной вершины орграфа, из которых можно попасть обратно в данную вершину. " << endl
				<< "6 - Требуется найти каркас минимального веса. " << endl
				<< "7 - Вывести кратчайшие пути из вершины u до v1 и v2. " << endl
				<< "9 - Выйти из меню " << endl;
			cout << "Введите номер действия, которое вы хотите сделать: ";
			cin >> optInt;
			switch (optInt) {
			case 1:
				cout << "Введите вершину: ";
				cin >> name1; 
				cout << GraphM[now].task1(name1);
				break;
			case 2:
				GraphM[now].task2();
				break;
			case 3:
				GraphM.push_back(Graph(GraphM[now]));
				now = GraphM.size() - 1;
				GraphM[now].task3();
				break;
			case 4:
				
				if (GraphM[now].isAcyclic() == true) {
					cout << "граф является ацикличным " << endl;
				}
				else
					cout << "граф НЕ является ацикличным " << endl;
				break;
			case 5:
				if (GraphM[now].isOriented()) {
					cout << "Введите вершину: ";
					cin >> name1;
					GraphM[now].findReachableAndBacktrackableVertices(name1);
				}
				else cout << "Граф неориентированный! ";
				break;
			case 6:
				GraphM[now].findMinimumSpanningTree();
				break;
			case 7:
				cout << "Введите вершину u: ";
				cin >> name1;
				cout << "Введите вершину v1: ";
				cin >> name2;
				cout << "Введите вершину v2: ";
				cin >> name3;
				GraphM[now].shortestPaths(name1, name2, name3);
				break;
			case 10:
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
	return 0;
}
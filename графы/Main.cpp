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
		cout << endl << "0 - ������� ���� " << endl
			<< "1 - ������� ������ ��������� ����� " << endl
			<< "2 - �������� ������� " << endl
			<< "3 - ������� ������� " << endl
			<< "4 - �������� ����� " << endl
			<< "5 - ������� ����� " << endl
			<< "6 - ������� ������ ��������� ����� � ���� " << endl
			<< "7 - �������� ���� " << endl
			<< "8 - ����� " << endl 
			<< "9 - �������� ������� " << endl << endl;
		cout << "������� ����� ��������, ������� �� ������ �������: ";
		cin >> option;
		switch (option)
		{
		case 0:
			cout << "�� ������ ��������� ���� �� �����? (y - ��, n - ���): ";
			cin >> opt;
			if (opt == "y") {
				cout << "������� ��� �����: ";
				cin >> name;
				GraphM.push_back(Graph(name));
				now = GraphM.size() - 1;
			}
			else {
				cout << "������� ��������� ����� (������������, �����������������): ";
				cin >> w >> o;
				/*cout << "������� ��� �����: ";
				cin >> name;*/
				GraphM.push_back(Graph(w, o));
				now = GraphM.size() - 1;
			}
			break;
		case 1:
			GraphM[now].Print();
			break;
		case 2:
			cout << "������� ��� ������� ������� ������ ��������: ";
			cin >> name;
			GraphM[now].NodeAdd(name);
			break;
		case 3:
			cout << "������� ��� ������� ������� ������ �������: ";
			cin >> name;
			GraphM[now].NodeDel(name);
			break;
		case 4:
			cout << "������� ����� ������ ������� ������ ��������� (���� ������ �� � ������� 1 -> 2): " << endl;
			cout << "��� ������ �������: ";
			cin >> name1;
			cout << "��� ������ �������: ";
			cin >> name2;
			if (GraphM[now].isWeighted()) {
				cout << "��� �����: ";
				cin >> weight;
				GraphM[now].NodeConnect(name1, name2, weight);
			}
			else {
				GraphM[now].NodeConnect(name1, name2, 0);
			}
			break;
		case 5:
			cout << "������� ����� ������ ������� ������ ����������� (���� ������ �� � ������� 1 -> 2): " << endl;
			cout << "��� ������ �������: ";
			cin >> name1;
			cout << "��� ������ �������: ";
			cin >> name2;
			GraphM[now].NodeDisconnect(name1, name2);
			break;
		case 6:
			cout << "������� ��� �����: ";
			cin >> name;
			GraphM[now].Writefile(name);
			break;
		case 7:
			GraphM[now].Remove();
			break;
		case 8:
			cout << "�� ������������� ������ �����? (y - ��, n - ���): ";
			cin >> opt;
			if (opt == "y") {
				exit(0);
			}
			else {
				cout << "����� �������." << endl;
			}
			break;
		case 9:
			cout << endl << "1 - ������� �� ������� �������, ������� �������� ������������ ���������� � ���������� ��� �������� �������. " << endl
				<< "2 - ��� ������ ������� ����� ������� � �������. " << endl
				<< "3 - ��������� ����, ���������� ����������� ��������� ������ � ��������� ���������. " << endl
				<< "4 - ���������, �������� �� �������� ������ ����������. " << endl
				<< "5 - ����� ��� ���������� �� ������ ������� �������, �� ������� ����� ������� ������� � ������ �������. " << endl
				<< "6 - ��������� ����� ������ ������������ ����. " << endl
				<< "7 - ������� ���������� ���� �� ������� u �� v1 � v2. " << endl
				<< "9 - ����� �� ���� " << endl;
			cout << "������� ����� ��������, ������� �� ������ �������: ";
			cin >> optInt;
			switch (optInt) {
			case 1:
				cout << "������� �������: ";
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
					cout << "���� �������� ���������� " << endl;
				}
				else
					cout << "���� �� �������� ���������� " << endl;
				break;
			case 5:
				if (GraphM[now].isOriented()) {
					cout << "������� �������: ";
					cin >> name1;
					GraphM[now].findReachableAndBacktrackableVertices(name1);
				}
				else cout << "���� �����������������! ";
				break;
			case 6:
				GraphM[now].findMinimumSpanningTree();
				break;
			case 7:
				cout << "������� ������� u: ";
				cin >> name1;
				cout << "������� ������� v1: ";
				cin >> name2;
				cout << "������� ������� v2: ";
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
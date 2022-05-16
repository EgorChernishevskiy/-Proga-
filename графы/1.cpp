#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
	int N, M; //кол-во вершин и рёбер
	cout << "Enter N, M: ";
	cin >> N >> M; //ввод кол-ва рёбер и вершин
	int x, y; //две вершины 
	vector<vector<int>> gr;
	gr.resize(N);
	for (int i = 0; i < M; i++) {//заполнение
		cin >> x >> y;
		if (x < N && y < N) {
			gr[x].push_back(y);
			gr[y].push_back(x);
		}
	}
	for (int i = 0; i < gr.size(); i++) {
		sort(gr[i].begin(), gr[i].end());
		gr[i].erase(unique(gr[i].begin(), gr[i].end()), gr[i].end());
	}

	int s; //врешина 
	cout << "Enter s: "; cin >> s;
	cout << gr[s].size() << endl;
  return 0;
}

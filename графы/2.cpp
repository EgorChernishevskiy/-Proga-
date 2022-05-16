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
	for (int i = 0; i < M; i++) {
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
	int a, b; //вершины
	cout << "Enter A, B: "; cin >> a >> b;
	gr[a].push_back(b);
	gr[b].push_back(a);
	sort(gr[a].begin(), gr[a].end());
	gr[a].erase(unique(gr[a].begin(), gr[a].end()), gr[a].end());
	sort(gr[b].begin(), gr[b].end());
	gr[b].erase(unique(gr[b].begin(), gr[b].end()), gr[b].end());

	for (int i = 0; i < gr.size(); i++) {
		for (int j = 0; j < gr[i].size(); j++) {
			cout << gr[i][j] << ' ';
		}
		cout << endl;
	}
  return 0;
}

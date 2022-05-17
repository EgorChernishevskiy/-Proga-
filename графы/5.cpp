#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

vector < vector<int> > g, gr;
vector<char> used;
vector<int> order, component;

void dfs1(int v) {
	used[v] = true;
	for (size_t i = 0; i < g[v].size(); ++i)
		if (!used[g[v][i]])
			dfs1(g[v][i]);
	order.push_back(v);
}

void dfs2(int v) {
	used[v] = true;
	component.push_back(v);
	for (size_t i = 0; i < gr[v].size(); ++i)
		if (!used[gr[v][i]])
			dfs2(gr[v][i]);
}

int main() {
	int n, M; //кол-во вершин и рёбер
	cout << "Enter N, M: ";
	cin >> n >> M; //ввод кол-ва рёбер и вершин
	int x, y; //две вершины 
	used.resize(n);
	gr.resize(n);//транспонированный
	g.resize(n);//обычный
	for (int i = 0; i < M; i++) {
		cin >> x >> y;
		if (x < n && y < n) {
			gr[y].push_back(x);
			g[x].push_back(y);
		}
	}
	used.assign(n, false);
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs1(i);
	used.assign(n, false);
	for (int i = 0; i < n; ++i) {
		int v = order[n - 1 - i];
		if (!used[v]) {
			dfs2(v);
			//... вывод очередной component ...
			for (vector<int>::iterator it = component.begin(); it != component.end(); ++it)
				cout << *it << " ";
			cout << endl;
			component.clear();
		}
	}
}

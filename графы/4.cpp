#include <iostream>
#include <vector>
#include <queue>
using namespace std;



int main()
{
    int m, n;
    cin >> n >> m;
    vector < vector<int> > g(n); // граф
    int s = 0; // начальная вершина
    for (int i = 0; i < m; i++ ) // считывание графа
    {
        int u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    queue<int> q; // очередь с вершинами, которые мы рассматриваем на данном этапе
    q.push(s);
    vector<bool> used(n); // логический массив, указывающий, посещена ли вершина
    used[s] = true;
    while (!q.empty()) // пока мы не обойдем все вершины, которые можно достигнуть из данной
    {
        int v = q.front();
        q.pop(); // достаем из головы очереди одну вершину
        for (size_t i = 0; i < g[v].size(); ++i) //просмотрим все ребра, исходящие из данной вершины
        {
            int to = g[v][i];
            if (!used[to]) // если текущая вершина еще не была посещена
            {
                used[to] = true; //отмечаем, что мы ее посетили
                q.push(to); // помещаем в очередь
            }
        }
    }
    vector<bool>::iterator it;
    it = find(used.begin(), used.end(), false); // проверяем, остались ли еще непосещенные вершины
    if (it == used.end())
        cout << "YES"; // если все вершины посещены, то граф связный
    else
        cout << "NO";
    return 0;
}

#pragma once
using namespace std;

ifstream in;
ofstream out;

class Graph {
public:
	Graph(bool w, bool o) {
		Weighted = w;
		Oriented = o;
	}

	Graph() {
		Weighted = false;
		Oriented = false;
	}

	Graph(string name) {
		in.open(name);
		string versh;
		string strMain;
		getline(in, strMain);
		Weighted = stoi(strMain.substr(2, 1));
		Oriented = stoi(strMain.substr(0, 1));
		while (getline(in, strMain)) {

			int i = 0;
			string strDop;
			string strDopWeight;

			while (strMain[i] != ':') {
				strDop += strMain[i];
				i++;
			}
			i += 2;
			versh = strDop;
			this->NodeAdd(versh);
			while (i < strMain.size()) {
				strDop = "";
				strDopWeight = "";
				while (strMain[i] != '_') {
					strDop += strMain[i];
					i++;
				}
				i++;
				while (strMain[i] != ' ') {
					strDopWeight += strMain[i];
					i++;
				}
				this->NodeAdd(strDop);
				this->NodeConnect(versh, strDop, stoi(strDopWeight));
				i++;
			}
		}
		in.close();
		cout << "Граф из файла успешно загружен" << endl;
	}

	Graph(const Graph& g)
	{
		Weighted = g.Weighted;
		Oriented = g.Oriented;
		v = g.v;
	}

	bool isWeighted() {
		return Weighted;
	}
	bool isOriented() {
		return Oriented;
	}

	bool Remove() {
		string choice;
		cout << "Удалить весь граф? (y - Да, n - Нет): ";
		cin >> choice;
		if (choice == "y") {
			v.clear();
		}
		else {
			cout << "Удаление отменено." << endl;
		}
		return true;
	}
	bool NodeDel(string node) {
		if (v.find(node) != v.end()) {
			v.erase(node);
			for (auto& element : v) {
				for (auto it = element.second.begin(); it != element.second.end(); it++) {
					if (it->first == node) {
						element.second.erase(it);
						break;
					}
				}
				//element.second.erase(find(element.second.begin(), element.second.end(), NodeName(node));
			}
			return true;
		}
		else {
			cout << "узел не найден" << endl;
			return false;
		}
	}
	bool NodeAdd(string node) {										//добавить вершину
		v.insert(make_pair(node, set<pair<string, int>>()));
		return true;
	}
	bool NodeConnect(string node1, string node2, int w) {         //добавить ребро
		if (v.find(node1) != v.end() && v.find(node2) != v.end()) {
			if (findInCertainNode(node1, node2)) {
				cout << "Вершины уже соединины" << endl;
				return false;
			}
			if (!Oriented) {
				if (!Weighted) {
					v[node1].insert(make_pair(node2, 0));
					v[node2].insert(make_pair(node1, 0));
					return true;
				}
				else {
					/*cout << node1 << "-" << node2 << " Type Weight: ";
					int w;
					cin >> w;*/
					v[node1].insert(make_pair(node2, w));
					v[node2].insert(make_pair(node1, w));
					return true;
				}
			}
			else {
				if (!Weighted) {
					v[node1].insert(make_pair(node2, 0));
					return true;
				}
				else {
					/*cout << node1 << "-" << node2 << " Type Weight: ";
					int w;
					cin >> w;*/
					v[node1].insert(make_pair(node2, w));
					return true;
				}
			}
		}
		else {
			cout << "Вершины не найдены" << endl;
			return false;
		}

	}

	bool NodeDisconnect(string node1, string node2) {				//удалить ребро
		if (v.find(node1) != v.end() && v.find(node2) != v.end()) {
			if (!Oriented) {
				for (auto it = v[node1].begin(); it != v[node1].end(); it++) {
					if (it->first == node2) {
						v[node1].erase(it);
						break;
					}
				}
				for (auto it = v[node2].begin(); it != v[node2].end(); it++) {
					if (it->first == node1) {
						v[node2].erase(it);
						break;
					}
				}
				return true;
			}
			else {
				int f = 0;
				auto it = v[node1].begin();
				for (; it != v[node1].end(); it++) {
					if (it->first == node2) {
						v[node1].erase(it);
						f = 1;
						break;
					}
				}
				if (f) {
					return true;
				}
				else {
					cout << "Пути не существует" << endl;
					return false;
				}
			}
		}
		else {
			cout << "Вершины не найдены";
			return false;
		}

	}

	bool findInNodeList(string nodeToFind) {
		for (auto element : v) {
			if (findInCertainNode(element.first, nodeToFind)) {
				return true;
			}
		}
		return false;
	}

	bool findInCertainNode(string nodeMain, string nodeToFind) {
		set<pair<string, int>> v2 = v[nodeMain];
		for (auto it = v2.begin(); it != v2.end(); it++) {
			if (it->first == nodeToFind) {
				return true;
			}
		}
		return false;
	}


	void Print() {
		cout << "Граф: ";
		if (Oriented) cout << "Ориентированный, ";
		else cout << "Неориентированный, ";
		if (Weighted) cout << "Взвешенный" << endl;
		else cout << "Невзвешенный" << endl;
		for (auto element : v) {
			cout << element.first << ": ";
			for (auto it = element.second.begin(); it != element.second.end(); it++) {
				cout << it->first << "_" << it->second << " ";
			}
			cout << endl;
		}
	}

	void Readfile(string name) {
		cout << "Текущий граф будет удален" << endl;
		this->Remove();
		in.open(name);
		string versh;
		string strMain;
		getline(in, strMain);
		Weighted = stoi(strMain.substr(2, 1));
		Oriented = stoi(strMain.substr(0, 1));
		while (getline(in, strMain)) {

			int i = 0;
			string strDop;
			string strDopWeight;

			while (strMain[i] != ':') {
				strDop += strMain[i];
				i++;
			}
			i += 2;
			versh = strDop;
			this->NodeAdd(versh);
			while (i < strMain.size()) {
				strDop = "";
				strDopWeight = "";
				while (strMain[i] != '_') {
					strDop += strMain[i];
					i++;
				}
				i++;
				while (strMain[i] != ' ') {
					strDopWeight += strMain[i];
					i++;
				}
				this->NodeAdd(strDop);
				this->NodeConnect(versh, strDop, stoi(strDopWeight));
				i++;
			}
		}
		in.close();
		cout << "Граф из файла успешно загружен" << endl;
	}
	void Writefile(string name) {
		out.open(name);
		out << Weighted << " " << Oriented << endl;
		for (auto element : v) {
			out << element.first << ": ";
			for (auto it = element.second.begin(); it != element.second.end(); it++) {
				out << it->first << "_" << it->second << " ";
			}
			out << endl;
		}
		out.close();
	}
	string task1(string Node) {
		string String1 = "";
		set<pair<string, int>> v2 = v[Node];
		for (auto it = v2.begin(); it != v2.end(); it++) {
			if (findInCertainNode(it->first, Node) == true) {
				String1 += it->first + " ";
			}
		}
		return String1;
	}
	int Degree(string node) {
		set<pair<string, int>> v2 = v[node];
		int c = 0;
		for (auto it = v2.begin(); it != v2.end(); it++) {
			if (it->first == node) {
				c += 2;
			}
			else c += 1;
		}
		return c;
	}
	void task2() {

		for (auto element : v) {
			cout << element.first << ": " << Degree(element.first) << endl;
		}
	}
	void task3() {
		vector<string> nodes;
		for (auto element : v) {
			if (Degree(element.first) % 2 == 1) {
				nodes.push_back(element.first);
			}
		}
		for (vector<int>::size_type i = 0; i != nodes.size(); i++) {
			NodeDel(nodes[i]);
		}
	}

	bool isAcyclicDFS(string vertex, map<string, bool>& visited, map<string, bool>& recStack) {
		visited[vertex] = true;
		recStack[vertex] = true;

		// Рекурсивный обход соседних вершин
		for (auto it = v[vertex].begin(); it != v[vertex].end(); ++it) {
			if (!visited[it->first]) {
				if (isAcyclicDFS(it->first, visited, recStack)) {
					return true; // Если найден цикл, то возвращаем true
				}
			}
			else if (recStack[it->first]) {
				return true; // Если вершина уже была посещена в текущем обходе, то возвращаем true
			}
		}

		recStack[vertex] = false; // Убираем вершину из текущего обхода
		return false;
	}

	bool isAcyclic() {
		map<string, bool> visited;  // Мапа для отслеживания посещенных вершин
		map<string, bool> recStack; // Мапа для отслеживания вершин в текущем обходе

		// Инициализация мапы visited
		for (auto it = v.begin(); it != v.end(); ++it) {
			visited[it->first] = false;
			recStack[it->first] = false;
		}

		// Запуск DFS для каждой вершины графа
		for (auto it = v.begin(); it != v.end(); ++it) {
			if (!visited[it->first]) {
				if (isAcyclicDFS(it->first, visited, recStack)) {
					return false; // Если найден цикл, то граф не является ацикличным
				}
			}
		}

		return true; // Если циклов не найдено, то граф является ацикличным
	}
	// Метод для нахождения всех достижимых из данной вершины вершин, из которых можно попасть обратно
	void findReachableAndReturnable1(string startVertex) {
		set<string> reachableAndReturnable; // Множество для хранения всех достижимых и обратно достижимых вершин
		queue<string> forwardQ; // Очередь для обхода графа в прямом направлении
		queue<string> backwardQ; // Очередь для обхода графа в обратном направлении

		forwardQ.push(startVertex);
		backwardQ.push(startVertex);
		reachableAndReturnable.insert(startVertex);

		while (!forwardQ.empty() && !backwardQ.empty()) {
			string forwardVertex = forwardQ.front();
			forwardQ.pop();

			string backwardVertex = backwardQ.front();
			backwardQ.pop();

			for (auto it = v[forwardVertex].begin(); it != v[forwardVertex].end(); ++it) {
				string forwardNeighbor = it->first;
				if (reachableAndReturnable.find(forwardNeighbor) == reachableAndReturnable.end()) {
					forwardQ.push(forwardNeighbor);
					reachableAndReturnable.insert(forwardNeighbor);
				}
			}

			for (auto it = v[backwardVertex].rbegin(); it != v[backwardVertex].rend(); ++it) {
				string backwardNeighbor = it->first;
				if (reachableAndReturnable.find(backwardNeighbor) == reachableAndReturnable.end()) {
					backwardQ.push(backwardNeighbor);
					reachableAndReturnable.insert(backwardNeighbor);
				}
			}
		}
		cout << "Вершины, достижимые из A и обратно в A:" << endl;
		for (auto it = reachableAndReturnable.begin(); it != reachableAndReturnable.end(); ++it) {
			cout << *it << endl;
		}
	}
	void getVerticesReachableAndReturnableFrom1(string startVertex) {
		set<string> reachableAndReturnableVertices;
		queue<string> bfsQueue;
		set<string> visitedVertices;
		visitedVertices.insert(startVertex);
		bfsQueue.push(startVertex);

		while (!bfsQueue.empty()) {
			string currentVertex = bfsQueue.front();
			bfsQueue.pop();

			// Check if we can reach the current vertex from the start vertex
			if (v[currentVertex].find({ startVertex, 0 }) != v[currentVertex].end()) {
				reachableAndReturnableVertices.insert(currentVertex);
			}

			// Explore unvisited neighbors
			for (const auto& neighbor : v[currentVertex]) {
				if (visitedVertices.find(neighbor.first) == visitedVertices.end()) {
					visitedVertices.insert(neighbor.first);
					bfsQueue.push(neighbor.first);
				}
			}
		}

		cout << "Vertices reachable and returnable from " << startVertex << ":" << endl;
		for (const auto& vertex : reachableAndReturnableVertices) {
			cout << vertex << endl;
		}
	}


	void findReachableAndBacktrackableVertices(const string& startVertex) {
		set<string> reachableVertices;
		set<string> visited;

		queue<string> q;
		q.push(startVertex);
		visited.insert(startVertex);

		while (!q.empty()) {
			string currentVertex = q.front();
			q.pop();

			for (const pair<string, int>& neighbor : v[currentVertex]) {
				string nextVertex = neighbor.first;
				if (visited.find(nextVertex) == visited.end()) {
					visited.insert(nextVertex);
					q.push(nextVertex);
					reachableVertices.insert(nextVertex);
				}
			}
		}

		set<string> backtrackableVertices;
		for (const string& vertex : reachableVertices) {
			if (isBacktrackable(startVertex, vertex)) {
				backtrackableVertices.insert(vertex);
			}
		}


		cout << "Вершины, достижимые из данной и обратно:" << endl;
		for (auto it = backtrackableVertices.begin(); it != backtrackableVertices.end(); ++it) {
			cout << *it << endl;
		}
	}

	bool isBacktrackable(const string& startVertex, const string& currentVertex) {
		set<string> visited;
		queue<string> q;
		q.push(currentVertex);
		visited.insert(currentVertex);

		while (!q.empty()) {
			string vertex = q.front();
			q.pop();
			for (const pair<string, int>& neighbor : v[vertex]) {
				string nextVertex = neighbor.first;
				if (visited.find(nextVertex) == visited.end() && nextVertex != startVertex) {
					visited.insert(nextVertex);
					q.push(nextVertex);
				}
				else if (nextVertex == startVertex) {
					return true;
				}
			}
		}
		return false;
	}

	bool isGraphDirected() {
		for (const auto& vertex : v) {
			for (const auto& edge : vertex.second) {
				const string& neighbor = edge.first;
				if (v.find(neighbor) != v.end() && v[neighbor].count({ vertex.first, edge.second }) == 0) {
					// Íàéäåíî îðèåíòèðîâàííîå ðåáðî
					return true;
				}
			}
		}
		return false;
	}
	bool isGrWeighted() {
		// проверяем, есть ли хотя бы одно ребро, вес которого отличается от 1
		for (const auto& vertex : v) {
			for (const auto& neighbor : vertex.second) {
				if (neighbor.second != 1) {
					return true;
				}
			}
		}
		return false;
	}

	void findMinimumSpanningTree() {
		if (isGraphDirected()) {
			cout << "Ошибка: Граф ориентированный. Алгоритм Прима применяется только к неориентированным графам." << endl;
			return;
		}
		map<string, bool> visited; // Пометка вершин
		map<string, string> parent; // Родительские вершины
		map<string, int> key; // Минимальные веса вершин

		// Инициализация структур данных
		for (const auto& vertex : v) {
			visited[vertex.first] = false;
			key[vertex.first] = INT_MAX;
		}

		// Начнем с произвольной вершины
		string startVertex = v.begin()->first;
		key[startVertex] = 0;

		// Создаем приоритетную очередь для вершин
		priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
		pq.push({ 0, startVertex });

		while (!pq.empty()) {
			string u = pq.top().second;
			pq.pop();
			visited[u] = true;

			for (const auto& edge : v[u]) {
				string v = edge.first;
				int weight = edge.second;

				if (!visited[v] && weight < key[v]) {
					key[v] = weight;
					parent[v] = u;
					pq.push({ key[v], v });
				}
			}
		}

		// Вывод минимального остовного дерева
		for (const auto& vertex : v) {
			if (parent.find(vertex.first) != parent.end()) {
				string u = parent[vertex.first];
				string v = vertex.first;
				int weight = key[v];
				cout << u << " -> " << v << "(" << weight << ")" << endl;
			}
		}
	}



	void shortestPaths(const string& u, const string& v1, const string& v2) {
		if (isGrWeighted()) {
			map<string, int> distance;
			map<string, string> previous;
			set<string> visited;
			priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

			for (const auto& vertex : v) {
				distance[vertex.first] = INT_MAX;
				previous[vertex.first] = "";
			}

			distance[u] = 0;
			pq.push(make_pair(0, u));

			while (!pq.empty()) {
				string current = pq.top().second;
				pq.pop();

				if (visited.find(current) != visited.end()) {
					continue;
				}

				visited.insert(current);

				for (const auto& neighbor : v[current]) {
					int alt = distance[current] + neighbor.second;
					if (alt < distance[neighbor.first]) {
						distance[neighbor.first] = alt;
						previous[neighbor.first] = current;
						pq.push(make_pair(alt, neighbor.first));
					}
				}
			}

			// Вывод кратчайших путей из u до v1 и v2
			if (distance[v1] == INT_MAX) {
				cout << "There is no path from " << u << " to " << v1 << endl;
			}
			else {
				cout << "Shortest path from " << u << " to " << v1 << ": ";
				string path = v1;
				while (path != u) {
					cout << path << " <- ";
					path = previous[path];
				}
				cout << u << " (distance: " << distance[v1] << ")" << endl;
			}

			if (distance[v2] == INT_MAX) {
				cout << "There is no path from " << u << " to " << v2 << endl;
			}
			else {
				cout << "Shortest path from " << u << " to " << v2 << ": ";
				string path = v2;
				while (path != u) {
					cout << path << " <- ";
					path = previous[path];
				}
				cout << u << " (distance: " << distance[v2] << ")" << endl;
			}
		}
		else cout << "Ошибка: Граф невзвешенный. Алгоритм применяется только к взвешенным графам." << endl;
	}

	void findNPeriphery(const std::string& start, int N) {
		std::map<std::string, int> distances;
		std::set<std::string> periphery;

		// Инициализация расстояний
		for (const auto& vertex : v) {
			if (vertex.first == start)
				distances[vertex.first] = 0;
			else
				distances[vertex.first] = INT_MAX;
		}

		// Выполнение N итераций алгоритма Беллмана-Форда
		for (int i = 0; i < N; ++i) {
			for (const auto& vertex : v) {
				const std::string& src = vertex.first;

				for (const auto& edge : vertex.second) {
					const std::string& dest = edge.first;
					int weight = edge.second;

					if (distances[src] != INT_MAX && distances[src] + weight < distances[dest]) {
						distances[dest] = distances[src] + weight;
					}
				}
			}
		}

		// Поиск вершин с расстоянием больше N
		for (const auto& vertex : v) {
			if (distances[vertex.first] > N) {
				periphery.insert(vertex.first);
			}
		}

		// Вывод периферии на экран
		std::cout << "N-перефириря  " << ":\n";
		for (const auto& vertex : periphery) {
			std::cout << vertex << " ";
		}
		std::cout << std::endl;
	}




	void printKShortestPaths(string u, string v1, int k) {
		priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;//Создаётся приоритетная очередь с парами (вес, вершина) в порядке возрастания веса.
		map<string, vector<pair<int, vector<string>>>> shortestPaths;//создаётся  shortestPaths для хранения кратчайших путей.

		pq.push(make_pair(0, u));//Добавляется начальная вершина в приоритетную очередь и в shortestPaths.
		shortestPaths[u].push_back(make_pair(0, vector<string>{u}));

		while (!pq.empty()) {
			string currentVertex = pq.top().second;//Извлекается вершина с наименьшим весом из приоритетной очереди.
			int currentWeight = pq.top().first;
			pq.pop();

			if (currentVertex == v1) {// Если это конечная вершина и количество найденных кратчайших путей уже равно k, то выходим из цикла
				if (shortestPaths[currentVertex].size() >= k) {
					break;
				}
			}

			for (auto neighbor : v[currentVertex]) {//Для каждого соседа текущей вершины
				string nextVertex = neighbor.first;
				int nextWeight = neighbor.second;//Вычисляется вес нового пути через этого соседа
				int weight = currentWeight + nextWeight;

				vector<pair<int, vector<string>>>& paths = shortestPaths[nextVertex];//Получаем список кратчайших путей до соседа из словаря shortestPaths

				if (paths.size() < k || weight < paths.back().first) {//Если список пустой или новый путь короче последнего в списке, 
					vector<string> path = shortestPaths[currentVertex].back().second;//то добавляем новый путь в список и обрезаем список до k элементов.
					path.push_back(nextVertex);
					paths.push_back(make_pair(weight, path));

					sort(paths.begin(), paths.end(),
						[](const pair<int, vector<string>>& a, const pair<int, vector<string>>& b) {
							return a.first < b.first;
						});

					if (paths.size() > k) {
						paths.pop_back();
					}

					pq.push(make_pair(weight, nextVertex));//Добавляем новую пару (вес, сосед) в приоритетную очередь.
				}
			}
		}

		cout << "K кратчайших путей между " << u << " и " << v1 << ":" << endl;//. Выводим результаты

		if (shortestPaths[v1].size() < k) {
			cout << "Путей не найдено" << endl;
		}
		else {
			for (const auto& path : shortestPaths[v1]) {
				cout << "Путь: ";
				for (const auto& vertex : path.second) {
					cout << vertex << " -> ";
				}
				cout << "Вес: " << path.first << endl;
			}
		}
	}
	//Форда-Фалкерсона
	bool bfs(map<string, pair<string, int>>& parent, string source, string sink) {
		map<string, bool> visited;//Создаётся словарь visited для хранения информации о посещении вершин.
		queue<string> q;//Создаётся очередь q и добавляется в неё начальная вершина source.
		q.push(source);
		visited[source] = true;//Помечаем начальную вершину как посещённую.

		while (!q.empty()) {
			string current = q.front();//Извлекаем вершину current из очереди.
			q.pop();

			for (const auto& neighbor : v[current]) {//Для каждого соседа neighbor текущей вершины:
				string v1 = neighbor.first;//Получаем вершину v1 и её пропускную способность capacity.
				int capacity = neighbor.second;
				// Если v1 ещё не была посещена и capacity > 0, то помечаем её как посещённую, добавляем её в очередь, 
				if (!visited[v1] && capacity > 0) {//записываем информацию о родительской вершине 													
					q.push(v1);						//и пропускной способности в словарь parent.
					visited[v1] = true;
					parent[v1] = { current, capacity };

					if (v1 == sink) {//Если v1 равна sink, то мы нашли путь и возвращаем true.
						return true;
					}
				}
			}
		}

		return false;
	}



	int findMaxFlow(const string& source, const string& sink) {
		map<string, pair<string, int>> parent;

		//Создаётся словарь parent для хранения информации о найденных путях
		for (const auto& vertex : v) {
			parent[vertex.first] = { "", 0 };//Инициализируем parent для каждой вершины графа.
		}

		int maxFlow = 0;//Создаём переменную maxFlow для хранения максимального потока, изначально равную 0.

		while (bfs(parent, source, sink)) {//Пока существует путь между истоком и стоком:
			int pathFlow = INT_MAX;//Инициализируем pathFlow значением INT_MAX.

			//  Находим минимальную пропускную способность на пути от стока к истоку, используя информацию из словаря parent.
			string v1 = sink;
			while (v1 != source) {
				string u = parent[v1].first;
				int capacity = parent[v1].second;
				pathFlow = min(pathFlow, capacity);
				v1 = u;
			}

			// Обновляем остаточные пропускные способности и обратные рёбра в графе, используя 
			v1 = sink; //информацию из словаря parent и найденную минимальную пропускную способность
			while (v1 != source) {
				string u = parent[v1].first;
				v[u].erase({ v1, parent[v1].second });
				v[v1].insert({ u, parent[v1].second });
				v[u].insert({ v1, parent[v1].second - pathFlow });
				v1 = u;
			}

			maxFlow += pathFlow;//Добавляем найденную пропускную способность к maxFlow
		}

		return maxFlow;
	}

private:
	map<string, set<pair<string, int>>> v;
	bool Weighted;
	bool Oriented;

};
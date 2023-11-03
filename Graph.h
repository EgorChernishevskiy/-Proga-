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
		cout << "���� �� ����� ������� ��������" << endl;
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
		cout << "������� ���� ����? (y - ��, n - ���): ";
		cin >> choice;
		if (choice == "y") {
			v.clear();
		}
		else {
			cout << "�������� ��������." << endl;
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
			cout << "���� �� ������" << endl;
			return false;
		}
	}
	bool NodeAdd(string node) {										//�������� �������
		v.insert(make_pair(node, set<pair<string, int>>()));
		return true;
	}
	bool NodeConnect(string node1, string node2, int w) {         //�������� �����
		if (v.find(node1) != v.end() && v.find(node2) != v.end()) {
			if (findInCertainNode(node1, node2)) {
				cout << "������� ��� ���������" << endl;
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
			cout << "������� �� �������" << endl;
			return false;
		}

	}

	bool NodeDisconnect(string node1, string node2) {				//������� �����
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
					cout << "���� �� ����������" << endl;
					return false;
				}
			}
		}
		else {
			cout << "������� �� �������";
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
		cout << "����: ";
		if (Oriented) cout << "���������������, ";
		else cout << "�����������������, ";
		if (Weighted) cout << "����������" << endl;
		else cout << "������������" << endl;
		for (auto element : v) {
			cout << element.first << ": ";
			for (auto it = element.second.begin(); it != element.second.end(); it++) {
				cout << it->first << "_" << it->second << " ";
			}
			cout << endl;
		}
	}

	void Readfile(string name) {
		cout << "������� ���� ����� ������" << endl;
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
		cout << "���� �� ����� ������� ��������" << endl;
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

		// ����������� ����� �������� ������
		for (auto it = v[vertex].begin(); it != v[vertex].end(); ++it) {
			if (!visited[it->first]) {
				if (isAcyclicDFS(it->first, visited, recStack)) {
					return true; // ���� ������ ����, �� ���������� true
				}
			}
			else if (recStack[it->first]) {
				return true; // ���� ������� ��� ���� �������� � ������� ������, �� ���������� true
			}
		}

		recStack[vertex] = false; // ������� ������� �� �������� ������
		return false;
	}

	bool isAcyclic() {
		map<string, bool> visited;  // ���� ��� ������������ ���������� ������
		map<string, bool> recStack; // ���� ��� ������������ ������ � ������� ������

		// ������������� ���� visited
		for (auto it = v.begin(); it != v.end(); ++it) {
			visited[it->first] = false;
			recStack[it->first] = false;
		}

		// ������ DFS ��� ������ ������� �����
		for (auto it = v.begin(); it != v.end(); ++it) {
			if (!visited[it->first]) {
				if (isAcyclicDFS(it->first, visited, recStack)) {
					return false; // ���� ������ ����, �� ���� �� �������� ����������
				}
			}
		}

		return true; // ���� ������ �� �������, �� ���� �������� ����������
	}

	bool isGraphDirected() {
		for (const auto& vertex : v) {
			for (const auto& edge : vertex.second) {
				const string& neighbor = edge.first;
				if (v.find(neighbor) != v.end() && v[neighbor].count({ vertex.first, edge.second }) == 0) {
					// ������� ��������������� �����
					return true;
				}
			}
		}
		return false;
	}

	void findReachableAndBacktrackableVertices(const string& startVertex) {
		if (isGraphDirected()) {


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


			cout << "�������, ���������� �� ������ � �������:" << endl;
			for (auto it = backtrackableVertices.begin(); it != backtrackableVertices.end(); ++it) {
				cout << *it << endl;
			}
		}
		else cout << "������: ���� ���������������. �������� ����� ����������� ������ � ����������������� ������." << endl;
		return;
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

	void findMinimumSpanningTree() {
		if (isGraphDirected()) {
			cout << "������: ���� ���������������. �������� ����� ����������� ������ � ����������������� ������." << endl;
			return;
		}
		map<string, bool> visited; // ������� ������
		map<string, string> parent; // ������������ �������
		map<string, int> key; // ����������� ���� ������

		// ������������� �������� ������
		for (const auto& vertex : v) {
			visited[vertex.first] = false;
			key[vertex.first] = INT_MAX;
		}

		// ������ � ������������ �������
		string startVertex = v.begin()->first;
		key[startVertex] = 0;

		// ������� ������������ ������� ��� ������
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

		// ����� ������������ ��������� ������
		for (const auto& vertex : v) {
			if (parent.find(vertex.first) != parent.end()) {
				string u = parent[vertex.first];
				string v = vertex.first;
				int weight = key[v];
				cout << u << " -> " << v << "(" << weight << ")" << endl;
			}
		}
	}

private:
	map<string, set<pair<string, int>>> v;
	bool Weighted;
	bool Oriented;

};
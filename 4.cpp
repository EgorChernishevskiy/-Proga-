#include <iostream>

using namespace std;

struct tree {//стуктура дерева
	int inf;
	tree* right;
	tree* left;
};

tree* node(int x) {
	tree* p = new tree;
	p->inf = x;
	p->right = p->left = NULL;
	return p;
}

void create(tree*& tr, int n) {//создание дерева
	int x;
	if (n > 0) {
		cin >> x;
		tr = node(x);
		int nl = n / 2;
		int nr = n - nl - 1;
		create(tr->left, nl);
		create(tr->right, nr);

	}
}

void task(tree* tr, int h, int k) {//Вывести узлы k-ого уровня
	if (h == k) {
		cout << tr->inf << ' ';
	}
	else {
		if (tr->left) {
			task(tr->left, h + 1, k);
		}
		if (tr->right) {
			task(tr->right, h + 1, k);
		}
	}
}

int main() {
	int n;
	cout << "n = "; cin >> n;

	tree* tr = NULL;
	create(tr, n);//ввод

	int k;
	cout << "Enter k: "; cin >> k;

	task(tr, 0, k);//вывод



}
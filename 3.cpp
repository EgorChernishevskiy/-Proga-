#include <iostream>

using namespace std;

struct tree {//�������� ������
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

void create(tree*& tr, int n) {//�������� ������
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

int count(tree* tr) {//������� �������� ���-�� �������
	int k = 0;//���-�� �������
	if (!tr->right && !tr->left) {
		return k += 1;
	}
	else {
		if (tr->right && tr->left) {
			return count(tr->left) + count(tr->right);
		}
		else if (tr->right) {
			return count(tr->right);
		}
		else {
			return count(tr->left);
		}
	}
}

int main() {
	int n;
	cout << "n = "; cin >> n;

	tree* tr = NULL;
	create(tr, n);//����

	cout << "c = " << count(tr) << endl;//�����


}
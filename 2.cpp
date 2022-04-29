#include <iostream>

using namespace std;

struct tree {
	int inf;
	tree* left;
	tree* right;
	tree* parent;
};

tree* node(int x) {
	tree* n = new tree;
	n->inf = x;
	n->left = n->right = NULL;
	n->parent = NULL;
	return n;
}

void insert(tree*& tr, int x) {
	tree* n = node(x);
	if (!tr) {
		tr = n;
	}
	else {
		tree* y = tr;
		while (y) {
			if (n->inf > y->inf) { //������ �����
				if (y->right) {
					y = y->right;
				}
				else {
					n->parent = y;
					y->right = n;
					break;
				}
			}
			else if (n->inf < y->inf) { //����� �����
				if (y->left) {
					y = y->left;
				}
				else {
					n->parent = y;
					y->left = n;
					break;
				}
			}
		}
	}
}

tree* find(tree* tr, int x) {//�����
	if (!tr || x == tr->inf) //����� ��� ����� �� ����� �����
		return tr;
	if (x < tr->inf)
		return find(tr->left, x); //���� �� ����� �����
	else
		return find(tr->right, x); //���� �� ������ �����
}

tree* Min(tree* tr) {//����� min
	if (!tr->left) return tr;//��� ������ �������
	else return Min(tr->left);//���� �� ����� ����� �� �����
}

tree* Next(tree* tr, int x) {//����� ����������
	tree* n = find(tr, x);
	if (n->right)//���� ���� ������ �������
		return Min(n->right);//min �� ������ �����
	tree* y = n->parent; //��������
	while (y && n == y->right) {//���� �� ����� �� ����� ��� ���� - ������ �������
		n = y;//���� ����� �� ������
		y = y->parent;
	}
	return y;//���������� ��������
}

void Delete(tree*& tr, tree* v) {//�������� ����
	tree* p = v->parent;
	if (!p) tr = NULL; //������ �������� ���� ����
	else if (!v->left && !v->right) {//���� ��� �����
		if (p->left == v) //��������� � �������� ������ �� NULL
			p->left = NULL;
		if (p->right == v)
			p->right = NULL;
		delete v;
	}
	else if (!v->left || !v->right) {//���� ������ ���� �������
		if (!p) { //���� ������� ������, � �������� 1 �������
			if (!v->left) { //���� ���� ������ �������
				tr = v->right; //�� ���������� ������
				v->parent = NULL;
			}
			else { //���������� ��� ������
				tr = v->left;
				v->parent = NULL;
			}
		}
		else {
			if (!v->left) {//���� ���� ������ �������
				if (p->left == v) //���� ��������� ���� ���. ����� ��������
					p->left = v->right; //������� ���������� ���� ���������� ����� �������� ������ "����"
				else
					p->right = v->right; ////������� ���������� ���� ���������� ������ �������� ������ "����"
				v->right->parent = p; //��������� ������� ���������� ��� "���"
			}
			else {//���������� ��� ������ �������
				if (p->left == v)
					p->left = v->left;
				else
					p->right = v->left;
				v->left->parent = p;
			}
			delete v;
		}
	}
	else {//���� ��� �������
		tree* succ = Next(tr, v->inf);//��������� �� ��������� �����
		v->inf = succ->inf; //����������� ��������
		if (succ->parent->left == succ) {//���� succ ����� �������
			succ->parent->left = succ->right; //��� ������ ������� ���������� ����� �������� ������ "����"
			if (succ->right) //���� ���� ������� ����������
				succ->right->parent = succ->parent; //��� ��������� ���������� "���"
		}
		else { //���������� ���� succ - ����sq �������
			succ->parent->right = succ->right;
			if (succ->right)
				succ->right->parent = succ->parent;
		}
		delete succ;
	}
}

void inorder(tree* tr) {
	if (tr) {
		inorder(tr->left);
		cout << tr->inf << ' ';
		inorder(tr->right);
	}
}

int height(tree* tr, tree* v, int h) {
	if (!v->left && !v->right) {
		return h;
	}
	else {
		if (v->left && v->right) {
			int r = height(tr, v->right, h + 1);
			int l = height(tr, v->left, h + 1);
			if (r > l) {
				return r;
			}
			else {
				return l;
			}
		}
		else if (v->left) {
			return height(tr, v->left, h + 1);
		}
		else {
			return height(tr, v->right, h + 1);
		}
	}
}

int main() {
	int n, x;
	cout << "n="; cin >> n;
	tree* tr = NULL;
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		cin >> x;
		insert(tr, x);
	}
	inorder(tr);
	cout << endl;

	cout << "h = " << height(tr, tr, 0) << endl;

}
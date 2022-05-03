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
			if (n->inf > y->inf) { //ïðàâàÿ âåòêà
				if (y->right) {
					y = y->right;
				}
				else {
					n->parent = y;
					y->right = n;
					break;
				}
			}
			else if (n->inf < y->inf) { //ëåâàÿ âåòêà
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

tree* find(tree* tr, int x) {//ïîèñê
	if (!tr || x == tr->inf) //íàøëè èëè äîøëè äî êîíöà âåòêè
		return tr;
	if (x < tr->inf)
		return find(tr->left, x); //èùåì ïî ëåâîé âåòêå
	else
		return find(tr->right, x); //èùåì ïî ïðàâîé âåòêå
}

tree* Min(tree* tr) {//ïîèñê min
	if (!tr->left) return tr;//íåò ëåâîãî ðåáåíêà
	else return Min(tr->left);//èäåì ïî ëåâîé âåòêå äî êîíöà
}

tree* Next(tree* tr, int x) {//ïîèñê ñëåäóþùåãî
	tree* n = find(tr, x);
	if (n->right)//åñëè åñòü ïðàâûé ðåáåíîê
		return Min(n->right);//min ïî ïðàâîé âåòêå
	tree* y = n->parent; //ðîäèòåëü
	while (y && n == y->right) {//ïîêà íå äîøëè äî êîðíÿ èëè óçåë - ïðàâûé ðåáåíîê
		n = y;//èäåì ââåðõ ïî äåðåâó
		y = y->parent;
	}
	return y;//âîçâðàùàåì ðîäèòåëÿ
}

void Delete(tree*& tr, tree* v) {//óäàëåíèå óçëà
	tree* p = v->parent;
	if (!p) tr = NULL; //äåðåâî ñîäåðæèò îäèí óçåë
	else if (!v->left && !v->right) {//åñëè íåò äåòåé
		if (p->left == v) //óêàçàòåëü ó ðîäèòåëÿ ìåíÿåì íà NULL
			p->left = NULL;
		if (p->right == v)
			p->right = NULL;
		delete v;
	}
	else if (!v->left || !v->right) {//åñëè òîëüêî îäèí ðåáåíîê
		if (!p) { //åñëè óäàëÿåì êîðåíü, ó êîòîðîãî 1 ðåáåíîê
			if (!v->left) { //åñëè åñòü ïðàâûé ðåáåíîê
				tr = v->right; //îí ñòàíîâèòñÿ êîðíåì
				v->parent = NULL;
			}
			else { //àíàëîãè÷íî äëÿ ëåâîãî
				tr = v->left;
				v->parent = NULL;
			}
		}
		else {
			if (!v->left) {//åñëè åñòü ïðàâûé ðåáåíîê
				if (p->left == v) //åñëè óäàëÿåìûé óçåë ÿâë. ëåâûì ðåáåíêîì
					p->left = v->right; //ðåáåíîê óäàëÿåìîãî óçëà ñòàíîâèòñÿ ëåâûì ðåáåíêîì ñâîåãî "äåäà"
				else
					p->right = v->right; ////ðåáåíîê óäàëÿåìîãî óçëà ñòàíîâèòñÿ ïðàâûì ðåáåíêîì ñâîåãî "äåäà"
				v->right->parent = p; //ðîäèòåëåì ðåáåíêà ñòàíîâèòñÿ åãî "äåä"
			}
			else {//àíàëîãè÷íî äëÿ ëåâîãî ðåáåíêà
				if (p->left == v)
					p->left = v->left;
				else
					p->right = v->left;
				v->left->parent = p;
			}
			delete v;
		}
	}
	else {//åñòü îáà ðåáåíêà
		tree* succ = Next(tr, v->inf);//ñëåäóþùèé çà óäàëÿåìûì óçëîì
		v->inf = succ->inf; //ïðèñâàèâàåì çíà÷åíèå
		if (succ->parent->left == succ) {//åñëè succ ëåâûé ðåáåíîê
			succ->parent->left = succ->right; //åãî ïðàâûé ðåáåíîê ñòàíîâèòñÿ ëåâûì ðåáåíêîì ñâîåãî "äåäà"
			if (succ->right) //åñëè ýòîò ðåáåíîê ñóùåñòâóåò
				succ->right->parent = succ->parent; //åãî ðîäèòåëåì ñòàíîâèòñÿ "äåä"
		}
		else { //àíàëîãè÷íî åñëè succ - ïðàâsq ðåáåíîê
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

void delete_if(tree* tr, tree* d, int x) {
	if (d) {
		delete_if(tr, d->left, x);
		delete_if(tr, d->right, x);
		if (d->inf % x == 0) {
			Delete(tr, d);
		}
	}
}

int main() {
	int n, c;
	cout << "n="; cin >> n;
	tree* tr = NULL;
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		cin >> c;
		insert(tr, c);
	}
	inorder(tr);
	cout << endl;

	int x;
	cout << "x = "; cin >> x;

	delete_if(tr, tr, x);

	inorder(tr);
	cout << endl;


}

#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

struct node
{
	int element;
	node* left;
	node* right;
	int height;
};

typedef struct node* nodeptr;

class bstree
{
public:
	void insert(int, nodeptr&);
	void inorder(nodeptr);
	int bsheight(nodeptr);
	nodeptr srl(nodeptr&);
	nodeptr drl(nodeptr&);
	nodeptr srr(nodeptr&);
	nodeptr drr(nodeptr&);
	int nonodes(nodeptr);
};
// Inserting a node
void bstree::insert(int x, nodeptr& p)
{
	if (p == NULL)
	{
		p = new node;
		p->element = x;
		p->left = NULL;
		p->right = NULL;
		p->height = 0;
		if (p == NULL)
		{
			cout << "Out of Space\n" << endl;
		}
	}
	else
	{
		if (x < p->element)
		{
			insert(x, p->left);
			if ((bsheight(p->left) - bsheight(p->right)) == 2)
			{
				if (x < p->left->element)
				{
					p = srl(p);
				}
				else
				{
					p = drl(p);
				}
			}
		}
		else if (x > p->element)
		{
			insert(x, p->right);
			if ((bsheight(p->right) - bsheight(p->left)) == 2)
			{
				if (x > p->right->element)
				{
					p = srr(p);
				}
				else
				{
					p = drr(p);
				}
			}
		}
		else
		{
			cout << "Элемет существует\n" << endl;
		}
	}
	int m, n, d;
	m = bsheight(p->left);
	n = bsheight(p->right);
	d = max(m, n);
	p->height = d + 1;
}



// Inorder Printing
void bstree::inorder(nodeptr p)
{
	if (p != NULL)
	{
		inorder(p->left);
		cout << p->element << "\t";
		inorder(p->right);
	}
}

int bstree::bsheight(nodeptr p)//height
{
	int t;
	if (p == NULL)
	{
		return -1;
	}
	else
	{
		t = p->height;
		return t;
	}
}

nodeptr bstree::srl(nodeptr& p1)
{
	nodeptr p2;
	p2 = p1->left;
	p1->left = p2->right;
	p2->right = p1;
	p1->height = max(bsheight(p1->left), bsheight(p1->right)) + 1;
	p2->height = max(bsheight(p2->left), p1->height) + 1;
	return p2;
}
nodeptr bstree::srr(nodeptr& p1)
{
	nodeptr p2;
	p2 = p1->right;
	p1->right = p2->left;
	p2->left = p1;
	p1->height = max(bsheight(p1->left), bsheight(p1->right)) + 1;
	p2->height = max(p1->height, bsheight(p2->right)) + 1;
	return p2;
}
nodeptr bstree::drl(nodeptr& p1)
{
	p1->left = srr(p1->left);
	return srl(p1);
}
nodeptr bstree::drr(nodeptr& p1)
{
	p1->right = srl(p1->right);
	return srr(p1);
}

int bstree::nonodes(nodeptr p)
{
	int count = 0;
	if (p != NULL)
	{
		nonodes(p->left);
		nonodes(p->right);
		count++;
	}
	return count;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	nodeptr root, root1;//,flag;
	int a, choice;
	bstree bst;

	//system("clear");
	root = NULL;
	root1 = NULL;
	cout << "\n\tАВЛ Дерево" << endl;

	do
	{
		
		cout << "1 Вставить новый узел:" << endl;
		cout << "2 Показать высоту дерева:" << endl;
		cout << "3 Обход:" << endl;
		cout << "4 Выход:" << endl;

		cout << "\nВыберите нужное действие и нажмите Enter: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "\n\t\tДобавление нового узла" << endl;
			cout << "Введите элемент: ";
			cin >> a;
			bst.insert(a, root);
			cout << "\nНовый элемент добавлен успешно\n" << endl;
			break;
		case 2:
			cout << "\n\t\tВЫСОТА\n" << endl;
			cout << "TДерево имеет высоту: " << bst.bsheight(root) << endl;

			break;
		case 3:
			cout << "\n\t\tОбход" << endl;
			bst.inorder(root);
			cout << endl;
			break;
		case 4:
			cout << "\n\tА на сегодня все, до новых встреч\n" << endl;
			break;
		default:
			cout << "Неверный ввод\n" << endl;
			break;
		}
		system("pause");
		system("cls");
	} while (choice != 0);
	return 0;
}

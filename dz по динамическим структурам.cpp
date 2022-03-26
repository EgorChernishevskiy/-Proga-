#include <iostream>
using namespace std;

struct stack {
    int inf;
    stack* next;
};


void push(stack*& h, int x) {
    stack* r = new stack; //создаем новый элемент
    r->inf = x; //поле inf = x
    r->next = h; //следующим элементов является h
    h = r; //теперь r является головой

}

int pop(stack*& h) {
    int i = h->inf; //значение первого элемента
    stack* r = h; //указатель на голову стека
    h = h->next; //переносим указатель на следующий элемент
    delete r; //удаляем первый элемент
    return i; //возвращаем значение
}


void reverse(stack*& h) { //"обращение"стека
    stack* head1 = NULL; //инициализация буферного стека
    while (h) //пока стек не пуст
        push(head1, pop(h)); //переписываем из одного стека в другой
    h = head1; //переобозначаем указатели

}

int max(stack*& h) {//поиск последнего максимального
    stack* head1 = NULL;
    int max = h->inf;
    while (h) {
        int l = pop(h);
        push(head1, l);
        if (l >= max) {
            max = l;
        }
    }
    h = head1;
    return max;
}

int min(stack*& h) {//поиск минимума
    stack* head1 = NULL;
    int min = h->inf;
    while (h) {
        int l = pop(h);
        push(head1, l);
        if (l < min) {
            min = l;
        }
    }
    h = head1;
    return min;
}

int chet(stack*& h) {//функция поиска последнего четного
    stack* head1 = NULL;
    int chet = 1;
    while (h) {
        int l = pop(h);
        push(head1, l);
        if (l % 2 == 0) {
            chet = l;
            break;
        }
    }
    h = head1;
    return chet;
}

void task3(stack*& h, int min) {//удаление первого минимума
    stack* head1 = NULL;
    int k = 0;
    while (h) {
        if (h->inf == min && k == 0) {
            pop(h);
            k++;
        }
        else {
            push(head1, pop(h));
        }
    }
    h = head1;
}

void task4(stack*& h, int max) {//вставка 0 
    stack* head1 = NULL;
    int k = 0;
    while (h) {
        int el = pop(h);
        
        if (el == max && k ==0) {
            push(head1, 0);
            k++;
        }
        push(head1, el);
        
    }
    h = head1;
}
int main()
{
    setlocale(LC_ALL, "RUS");
    stack* h = NULL;
    int n; //кол-во элементов
    int input; //ввод данных
    cout << "task 1 " << endl;//задание 1
    cout << "Enter n: ";
    cin >> n;
    cout << endl;
    while (n > 0) {
        cin >> input;
        push(h, input);
        n--;
    }

    while (h) {
        cout << pop(h) << ' ';
    }
    cout << endl;

    cout << "task 2 " << endl;//задание 2
    stack* g = NULL;
    cout << "Enter n: ";
    cin >> n;
    cout << endl;
    while (n > 0) {
        cin >> input;
        push(g, input);
        n--;
    }
    int ch = chet(g);
    if (ch != 1)
        cout << ch << endl;
    else
        cout << "нет четных " << endl;
    cout << endl;

    cout << "task 3 " << endl;//задание 3
    stack* f = NULL;
    cout << "Enter n: ";
    cin >> n;
    cout << endl;
    while (n > 0) {
        cin >> input;
        push(f, input);
        n--;
    }
    int mi = min(f);
    task3(f, mi);
    reverse(f);

    while (f) {
        cout << pop(f) << ' ';
    }
    cout << endl;

    cout << "task 4 " << endl;//задание 4
    stack* d = NULL;
    cout << "Enter n: ";
    cin >> n;
    cout << endl;
    while (n > 0) {
        cin >> input;
        push(d, input);
        n--;
    }
    int ma = max(d);
    reverse(d);
    task4(d, ma);
    while (d) {
        cout << pop(d) << ' ';
    }

    return 0;
}

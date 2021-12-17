#include <iostream>
using namespace std;
//Односвязный список в двусвязный
struct Node {
	int val;
	Node* next;
	Node* prew;
	Node(int _val) : val(_val), next(nullptr), prew(nullptr) {}
};

struct list {
	Node* first;
	Node* last;
	list() : first(nullptr), last(nullptr) {}

	bool empty() {
		return first == nullptr;
	}
	//нахождение элемента
	Node* find(int _val) {
		Node* ptr = first;
		while (ptr != nullptr) {
			if (ptr->val == _val) break;
			else
				ptr = ptr->next;
		}
		return ptr;
	}
	//Добавить элемент
	void push_back(int _val) {
		Node* ptr = new Node(_val);
		if (empty()) {
			first = ptr;
			last = ptr;
			return;
		}
		else {
			last->next = ptr;
			ptr->prew = last;
			last = ptr;
		}
	}

	void print() {
		if (empty()) return;
		Node* ptr = first;
		while (ptr != nullptr) {
			cout << ptr->val << " ";
			ptr = ptr->next;
		}
		cout << endl;
	}
	//Удаление последнего
	void remove_last() {
		if (empty()) return;
		if (first == last) {
			remove_first();
			return;
		}
		Node* ptr = first;
		while (ptr->next != last) ptr = ptr->next;
		ptr->next = nullptr;
		delete last;
		last = ptr;
	}
	//Удаление первого
	void remove_first() {
		if (empty()) return;
		Node* ptr = first;
		first = ptr->next;
		first->prew = nullptr;
		delete ptr;
	}
	//Удаление элемента
	void remove_val(int _val) {
		if (empty()) return;
		if (first->val == _val) {
			remove_first();
			return;
		}
		else if (last->val == _val) {
			remove_last();
			return;
		}
		else {
			Node* ptr = first;
			if (ptr->next == nullptr) return;
			while (ptr->next != nullptr) {
				if (ptr->next->val == _val) break;
				else ptr = ptr->next;
			}
			if (ptr->next != nullptr) {
				Node* t = ptr->next;
				ptr->next = t->next;
				t->next->prew = ptr;
				delete t;
			}
		}
	}

	Node* operator [] (const int index) {
		if (empty()) return nullptr;
		Node* ptr = first;
		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
			if (!ptr) return nullptr;
		}
		return ptr;
	}
	//Добавление в начало
	void push_front(int _val) {
		Node* ptr = new Node(_val);
		ptr->next = first;
		first->prew = ptr;
		first = ptr;
	}
	//Счетчик
	int count() {
		int k = 0;
		Node* ptr = first;
		while (ptr != nullptr) {
			k++;
			ptr = ptr->next;
		}
		return k;
	}
};
//Симметричен ли двусвязный список (чётный)
bool IsSim1(list l) {
	bool p = true;
	Node* p1 = l.first;
	Node* p2 = l.last;
	while (p1 != p2) {
		if (p1->val != p2->val) { p = false; break; }
		p1 = p1->next;
		p2 = p2->prew;
	}
	return p;
}
//чётный
bool IsSim0(list l) {
	bool p = true;
	Node* p1 = l.first;
	Node* p2 = l.last;
	while (p1->next != p2)
	{
		if (p1->val != p2->val) { p = false; break; }
		p1 = p1->next;
		p2 = p2->prew;
	}
	return p;
}
//Основная
bool IsSim(list l) {
	if (l.empty()) return false;
	if (l.count() % 2 == 0) return IsSim0(l);
	else return IsSim1(l);
}
//Главная часть-проверки
int main() {
	list l;
	cout << l.empty() << endl;
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.print();
	cout << IsSim(l) << endl;
	cout << l.empty() << endl;
	//	l.remove("123");
	l.print();
	l.push_back(6);
	l.remove_first();
	l.print();
	l.remove_last();
	l.print();
	for (int i = 0; i < 10; i++) 	l.push_back(i);
	l.print();
	cout << l[7]->val << endl;
	l.remove_val(4);
	l.remove_val(9);
	l.remove_val(2);
	l.print();
	if (l.find(7) != nullptr) cout << "+"; else cout << "-" << endl;
	if (l.find(14) != nullptr) cout << "+"; else cout << "-" << endl;
	l.push_front(13);
	l.print();
	cout << IsSim(l) << endl;

	return 0;
}
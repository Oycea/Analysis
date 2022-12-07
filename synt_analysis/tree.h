#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
#include <string>
#include "Element.h"
#include "incident.h"
using namespace std;

class node {
public:
	int a;
	Element el;
	int _size;
	vector<node*> arr;
	node* parent;

	node(int _a) {
		a = _a;
		parent = nullptr;
	}

	node(Element _el) {
		a = -1;
		el = _el;
		parent = nullptr;
	}

	inline node* add(node* __node, int _a) {
		node* nd = new node(_a);
		__node->arr.push_back(nd);
		__node->_size++;
		nd->parent = __node;
		return nd;
	}

	inline node* add(node* __node, Element& _a) {
		node* nd = new node(_a);
		__node->arr.push_back(nd);
		__node->_size++;
		nd->parent = __node;
		return nd;
	}

	inline void _print(node* pos, int level) {
		if (pos == 0) return;
		for (int i = 0; i < level; i++)
			cout << ' ';
		if (pos->a != -1)
			cout << trans(pos->a) << '\n';
		else
			cout << pos->el << "\n";
		for (int i = 0; i < pos->_size; i++) {
			_print(pos->arr[i], level + 1);
		}
	}

	inline void _print(node* pos, int level, ofstream& fout) {
		if (pos == 0) return;
		for (int i = 0; i < level; i++)
			fout << ' ';
		if (pos->a != -1)
			fout << trans(pos->a) << '\n';
		else
			fout << pos->el << "\n";
		for (int i = 0; i < pos->_size; i++) {
			_print(pos->arr[i], level + 1, fout);
		}
	}

	void destroy(node* pos) {
		for (int i = 0; i < pos->_size; i++) {
			destroy(pos->arr[i]);
		}
		delete pos;
	}
};
#endif

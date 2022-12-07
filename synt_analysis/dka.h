#ifndef DKA_H
#define DKA_H

#include<iostream>
#include<string>
#include<vector>
#include"hash_table.h"
using namespace std;

class Node {
private:
	bool _fin_pos;
	string _condition;
	int nodes[3];

public:

	// йнмярпсйрнп
	Node(bool, string, int, int, int);

	// церрепш
	string get_condition() { return _condition; }
	bool get_fin_pos() { return _fin_pos; }

	// лернд
	int get_next(char a);
};

class Checker {
private:
	vector<Node> matrix;

public:

	// йнмярпсйрнп
	Checker();

	// лернд
	string check_word(string word);
};

#endif // DKA_H

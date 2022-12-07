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

	// �����������
	Node(bool, string, int, int, int);

	// �������
	string get_condition() { return _condition; }
	bool get_fin_pos() { return _fin_pos; }

	// �����
	int get_next(char a);
};

class Checker {
private:
	vector<Node> matrix;

public:

	// �����������
	Checker();

	// �����
	string check_word(string word);
};

#endif // DKA_H

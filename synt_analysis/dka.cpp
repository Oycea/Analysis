#include"dka.h"
using namespace std;

Node::Node(bool fin_pos, string condition, int pos_1, int pos_2, int pos_3) {
	_fin_pos = fin_pos;
	_condition = condition;
	nodes[0] = pos_1;
	nodes[1] = pos_2;
	nodes[2] = pos_3;
}

int Node::get_next(char a) {
	if ((int)a >= 48 && (int)a <= 57) // öèôğû
		return nodes[0];
	else if ((int)a >= 65 && (int)a <= 90 || (int)a >= 97 && (int)a <= 122) // áóêâû
		return nodes[1];
	else if ((int)a == 46) // .
		return nodes[2];
	else
		return -1;
}

Checker::Checker() {
	Node q0(0, "not_determinated", 1, 2, 3);
	matrix.push_back(q0);
	Node q1(1, "intNum", 1, 3, 4);
	matrix.push_back(q1);
	Node q2(1, "id", 3, 2, 3);
	matrix.push_back(q2);
	Node q3(0, "not_determinated", 3, 3, 3);
	matrix.push_back(q3);
	Node q4(0, "not_determinated", 5, 3, 3);
	matrix.push_back(q4);
	Node q5(1, "complexNum", 5, 3, 3);
	matrix.push_back(q5);
}

string Checker::check_word(string word) {
	int k = 0;
	for (char it : word) {
		k = matrix[k].get_next(it);
		if (k == -1)
			return "not_determinated";
	}
	return matrix[k].get_condition();
}
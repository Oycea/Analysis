#include"func.h"
using namespace std;

vector<char> operators = { '+', '-', '=', '(', ')', ',' };
vector<char> space = { ' ' };
vector<string> key_words = { "PROGRAM", "END", "INTEGER", "COMPLEX", "CMPLX", "CABS" };

Checker check;

void make_table(string str, Hash_table& matrix) {

	string word = "";

	for (char ind : str) {

		bool is_space = find(space.begin(), space.end(), ind) != space.end();
		bool is_oper = find(operators.begin(), operators.end(), ind) != operators.end();

		if (is_space || is_oper) {
			if (is_oper) {
				string s;
				s += ind;
				Element spr;
				spr.set_lexem(s);
				spr.set_type("separator");
				matrix.insert(spr);
			}
			if (find(key_words.begin(), key_words.end(), word) != key_words.end()) {
				Element kw;
				kw.set_lexem(word);
				kw.set_type("keyword");
				matrix.insert(kw);
				word = "";
			}
			else if (word != "") {
				string name = check.check_word(word);
				Element s;
				s.set_lexem(word);
				s.set_type(name);
				matrix.insert(s);
				word = "";
			}
		}
		else
			word += ind;
	}
	if (word != "") {
		if (find(key_words.begin(), key_words.end(), word) != key_words.end()) {
			Element kw;
			kw.set_lexem(word);
			kw.set_type("keyword");
			matrix.insert(kw);
			word = "";
		}
		else {
			string name = check.check_word(word);
			Element s(word, name);
			matrix.insert(s);
			word = "";
		}
	}
}
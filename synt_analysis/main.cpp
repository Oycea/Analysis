#include<iostream>
#include<string>
#include<fstream>
#include<vector>

#include"element.h"
#include"hash_table.h"
#include"dka.h"
#include"func.h"
#include"syntax.h"
#include"tree.h"
#include"analysis.h"

using namespace std;

int main() {

	syntax_anal prog("input.txt");
	int status = prog.program();
	if (status != OK) {
		if (status == LEX_ERR) {
			cout << trans(status) << "\n";
			cout << "Problem in that moment -> " << prog.lexem() << "\n";
			return 0;
		}
		else {
			cout << trans(status) << "\n";
			cout << "Problem in that moments -> " << prog.lexem2() << prog.lexem() << "\n";
			return 0;
		}
	}
	node* a = prog.root();
	ofstream text("output2.txt");
	a->_print(a, 0, text);
	a->destroy(a);
	prog.table().display_table("output.txt");
	return 0;
}
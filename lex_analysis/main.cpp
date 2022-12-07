#include<iostream>
#include<string>
#include<fstream>
#include"Elements.h"
#include"hash_table.h"
#include"dka.h"
#include"func.h"
using namespace std;

int main() {
	ifstream fin("input.txt");

	Hash_table tbl(1000);
	string str;

	while (getline(fin, str)) {
		make_table(str, tbl);
	}
    ofstream out("output.txt");
    for (int i = 0; i < tbl.get_size(); i++)
    {
        if (tbl._table[i].size() != 0) {
            out << "table[" << i << "]";
            for (auto x : tbl._table[i])
                out << " --> " << x;
            out << endl;
        }
    }
    out.close();

	return 0;
}
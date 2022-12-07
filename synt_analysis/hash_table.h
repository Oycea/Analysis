#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"element.h"
using namespace std;

class Hash_table {
private:
    int _size;

public:

    vector<Element> _table;

    //  ŒÕ—“–” “Œ–€

    Hash_table();

    Hash_table(int);

    // √≈““≈–

    int get_size() { return _size; }

    // Ã≈“Œƒ€

    int hash_func(Element);

    void insert(Element);

    inline void see_table()
    {
        for (int i = 0; i < _size; i++)
        {
            if (_table[i].get_lexem() != "") {
                cout << "table[" << i << "]";
                cout << " --> " << _table[i];
                cout << "\n";
            }
        }
    }

    inline void display_table(string file_name)
    {
        ofstream out(file_name);
        for (int i = 0; i < _size; i++)
        {
            if (_table[i].get_lexem() != "") {
                out << "table[" << i << "]";
                out << " --> " << _table[i];
                out << "\n";
            }
        }
        out.close();
    }

};

#endif // HASH_TABLE_H

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"elements.h"
using namespace std;

class Hash_table{
private:
    int _size;

public:

    vector<Element>* _table;

    // йнмярпсйрнп

    Hash_table(int);

    // церреп

    int get_size() { return _size; }

    // лерндш

    int hash_func(Element);

    void insert(Element);

    inline void see_table()
    {
        for (int i = 0; i < _size; i++)
        {
            if (_table[i].size() != 0) {
                cout << "table[" << i << "]";
                for (auto x : _table[i])
                    cout << " --> " << x;
                cout << "\n";
            }
        }
    }

};

#endif

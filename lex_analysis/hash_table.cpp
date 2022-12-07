#include"hash_table.h"

Hash_table::Hash_table(int size) {
    _size = size;
    _table = new vector<Element>[size];
}

int Hash_table::hash_func(Element el) {
	int hash = 0, cnst = 1013;
	for (int i = 0; i < el.get_lexem().size(); i++)
		hash = (cnst * hash + (int)el.get_lexem()[i]) % _size;
	return hash;
}

void Hash_table::insert(Element a) {
    bool flag = 0;
    int index = hash_func(a);
    for (int i = 0; i < _table[index].size(); i++)
        if (a.get_lexem() == _table[index][i].get_lexem())
            flag = 1;
    if (!flag)
        _table[index].push_back(a);
}

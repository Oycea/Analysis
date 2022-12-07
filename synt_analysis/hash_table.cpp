#include"hash_table.h"

Hash_table::Hash_table() {
    _size = 20000;
    _table.resize(20000);
}

Hash_table::Hash_table(int size) {
    _size = size;
    _table.resize(size);
}

int Hash_table::hash_func(Element el) {
    int hash = 0, cnst = 1013;
    for (int i = 0; i < el.get_lexem().size(); i++)
        hash = (cnst * hash + (int)el.get_lexem()[i]) % _size;
    return hash;
}

void Hash_table::insert(Element a) {
    int index = hash_func(a); // находим его индекс
    for (int i = index; i < _size; i++) {
        if (_table[i].get_lexem() == "") {
            _table[i] = a;
            return;
        }
        if (_table[i].get_lexem() == a.get_lexem())
            return;
    }
    _table.push_back(a);
}

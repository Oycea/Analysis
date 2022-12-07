#ifndef ELEMENT_H
#define ELEMENT_H

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Element {
private:
	string _lexem;
	string _type;

public:

	// йнмярпсйрнпШ
	Element();
	Element(string, string);
	Element(const Element&);

	// церрепш
	string get_lexem() { return _lexem; }
	string get_type() { return _type; }

	// яеррепш
	void set_lexem(string lexem) { _lexem = lexem; }
	void set_type(string type) { _type = type; }

	// оепецпсгйю ноепюрнпнб
	void operator=(Element obj) {
		_lexem = obj._lexem;
		_type = obj._type;
	}
	friend ostream& operator<<(ostream&, const Element&);
};

#endif // ELEMENT_H

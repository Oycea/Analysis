#include"elements.h"

// КОНСТРУКТОРЫ

Element::Element() : _lexem(""), _type("") {}

Element::Element(string lexem, string type) {
	_lexem = lexem;
	_type = type;
}

// Перегрузка оператора вывода
ostream& operator<<(ostream& output, const Element& object) {
	output << object._type << " --> " << object._lexem << endl;
	return output;
}
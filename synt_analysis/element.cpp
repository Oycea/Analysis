#include"element.h"

// ������������

Element::Element() : _lexem("") {}

Element::Element(string lexem, string type) {
	_lexem = lexem;
	_type = type;
}

Element::Element(const Element& obj) {
	_lexem = obj._lexem;
	_type = obj._type;
}

// ���������� ��������� ������
ostream& operator<<(ostream& output, const Element& object) {
	output << object._type << " --> " << object._lexem << endl;
	return output;
}
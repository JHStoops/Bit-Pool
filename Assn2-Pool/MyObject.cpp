#include "MyObject.h"

Pool MyObject::pool(sizeof(MyObject));

MyObject::MyObject(int i, const std::string& nm) : name(nm) {
	id = i;
}

std::ostream& operator<<(std::ostream& os, const MyObject& obj) {
	os << "{" << obj.id << "," << obj.name << "}";
	return os;
}
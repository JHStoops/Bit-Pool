#ifndef MYOBJECT
#include <string>
#include <cstddef>
#include "Pool.h"

class MyObject
{
private:
	// (De)Constructors
	MyObject(const MyObject&) = delete;
	MyObject(int, const std::string&);

	// Member Variables
	int id;
	std::string name;
	

	// Methods
	static void* operator new(size_t count) {
		return reinterpret_cast<char*>(MyObject::pool.allocate());
	}

public:
	// Methods
	void operator=(const MyObject&) = delete;
	friend std::ostream& operator<<(std::ostream& os, const MyObject& obj);
	static void operator delete(void* ptr) {
		pool.deallocate(ptr);
	}
	static MyObject* create(int id, const std::string& name) {
		return new MyObject(id, name);
	}
	static Pool pool;
};
#endif MYOBJECT
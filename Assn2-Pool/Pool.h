#ifndef POOL
#define _SECURE_SCL_DEPRECATE 0
#include <cassert>
#include <iostream>
#include <cstddef>

class Pool
{
private:
	// Member Variables
	char** poolHead;
	char* free;
	size_t blockCount;
	size_t elemSize;
	size_t blockSize;

public:
	// (De)Constructors
	Pool(const Pool&) = delete;
	Pool(size_t, size_t blockSize = 6);
	~Pool();

	// Methods
	void operator=(const Pool&) = delete;
	void* allocate(); // Get a pointer inside a pre-allocated block for a new object
	void deallocate(void*); // Free an object's slot (push the address on the "free list")
	void expandPool();
	
	template<typename T>
	T peek(void* p) {
		// Return the bytes at address p interpreted as a T object
		return *reinterpret_cast<T*>(p); // Casting from void* only requires a static_cast
	}
	template<typename T>
	void poke(void* p, T t) {
		// Place a copy of the object t at address p
		new (p) T(t);   // "Placement new"
	}
};
#endif POOL
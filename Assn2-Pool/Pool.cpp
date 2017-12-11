#include "Pool.h"

// (De)Constructors
Pool::Pool(size_t _elemSize, size_t _blockSize){ //TODO find out if this is ok, or if it needs to be user-defined.
	std::cout << "Initializing a pool with element size " << _elemSize << " and block size " << _blockSize << std::endl;
	assert(_elemSize > 0, "elemSize must be greater than zero.");
	elemSize = _elemSize;
	assert(_blockSize > 0, "blockSize must be greater than zero.");
	blockSize = _blockSize;
	blockCount = 0;
	poolHead = nullptr;
	free = nullptr;
}
Pool::~Pool(){
	//Delete X amount of blocks
	std::cout << "Deleting " << blockCount << " blocks" << std::endl;
	for (int i = 0; i < blockCount; i++)
		delete[] poolHead[i];
	delete[] poolHead;
}

// Methods
void* Pool::allocate(){
	//allocate new cell in pool
	if (this->free == nullptr) expandPool();
	assert(free != nullptr, "allocate() requires free to not be a nullptr.");
	void* ptr = free;
	if (peek<char*>(free) == nullptr) free = nullptr;
	else free = peek<char*>(free);
	std::cout << "Cell allocated at " << ptr << std::endl;
	return ptr;
}
void Pool::deallocate(void* ptr){
	//deallocate new cell in pool
	assert(reinterpret_cast<char*>(ptr), "deallocate(ptr) requires ptr to point at an object.");
	poke(ptr, free);
	free = reinterpret_cast<char*>(ptr);
	std::cout << "Cell deallocated at " << reinterpret_cast<void*>(free) << std::endl;
}
void Pool::expandPool() {
	//Resize
	std::cout << "Expanding pool..." << std::endl;
	blockCount++;

	//Expand the pool - make bigger array and copy over pointers to blocks
	if (blockCount == 1) poolHead = new char*;
	else {
		char **tempPool = poolHead;
		poolHead = new char*[blockCount];
		poolHead[0] = new char[blockSize * elemSize];
		std::copy(tempPool, tempPool + blockCount, poolHead);
		delete[] tempPool;
	}

	//Expand the pool - Add a block
	poolHead[blockCount - 1] = new char[elemSize * blockSize];
	free = &poolHead[blockCount - 1][0];

	//Put address of next element into each element -- last element is nullptr
	for (int i = 0; i < blockSize; i++) {
		if (i == blockSize - 1) poke(free + i * elemSize, nullptr);
		else poke(free + i * elemSize, static_cast<char *>(free + (i + 1) * elemSize));
	}

	std::cout << "Linking cells starting at " << reinterpret_cast<void *>(free) << std::endl;
}
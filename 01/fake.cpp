#include "fake.hpp"

#include <iostream>

class Allocator {
    bool allocated = false;
    size_t allocated_size;
    size_t offset;
    char *memory;
public:
    void makeAllocator(size_t maxSize)
    {
        if (allocated) {
            delete[] memory;
        }
        allocated = true;
        memory = new char[maxSize];
        offset = 0;
        allocated_size = maxSize;
    }
    char* alloc(size_t size) {
        size_t new_offset = offset + size;
        if (new_offset > allocated_size)
        {
            return nullptr;
        }
        char *block = &memory[offset];
        offset = new_offset;
        return block;
    }
    void reset() {
        offset = 0;
    }
    ~Allocator() {
        delete[] memory;
    }
};



namespace fake
{

bool memoryOverflowTest() {
	Allocator al;
	al.makeAllocator(100);
	char *m1 = al.alloc(10);
	char *m2 = al.alloc(20);
	char *m3 = al.alloc(100);
	return (m3 == nullptr && m2 != nullptr && m1 != nullptr);
}
bool defaultWorkTest()
{
    Allocator allocator;
    allocator.makeAllocator(100);
    char *mem1 = allocator.alloc(10);
    char *mem2 = allocator.alloc(20);
    char *mem3 = allocator.alloc(50);
    ptrdiff_t f1 = mem3 - mem2;
    ptrdiff_t f2 = mem2 - mem1;
    return (f1 == 20 && f2 == 10);
}

bool resetMethodTest() 
{
    Allocator allocator;
    allocator.makeAllocator(100);
    char* mem1 = allocator.alloc(10);
    allocator.reset();
    char* mem3 = allocator.alloc(50);
    return (mem1 == mem3);
}

bool newSpaceTest()
{
    Allocator allocator;
    allocator.makeAllocator(100);
    char* mem1 = allocator.alloc(50);
    allocator.makeAllocator(150);
    char* mem2 = allocator.alloc(50);
    return (mem1 != mem2);
}

}

#include <iostream>
#include "allocator.hpp"

void Allocator::makeAllocator(size_t maxSize) {
    if (!maxSize) {
    	return;
    }
    if (allocated) {
        delete[] memory;
        allocated = false;
    }
    allocated = true;
    memory = new char[maxSize];
    offset = 0;
    allocated_size = maxSize;
}

char* Allocator::alloc(size_t size) {
    if (!size) {
    	return nullptr;
    }	
    size_t new_offset = offset + size;
    if (new_offset > allocated_size)
    {
        return nullptr;
    }
    char *block = &memory[offset];
    offset = new_offset;
    return block;
}
size_t Allocator::Get_of() {
    return offset;
}
bool Allocator::IsAllocated() {
    return allocated;
}
void Allocator::reset() {
    offset = 0;
}

Allocator::~Allocator() {
    delete[] memory;
}

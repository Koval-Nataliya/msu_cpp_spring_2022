#pragma once

#include <gtest/gtest.h>

class Allocator 
{
    bool allocated = false;
    size_t allocated_size;
    size_t offset;
    char *memory;
public:
    bool IsAllocated();
    size_t Get_of();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};

#include <iostream>

#include <gtest/gtest.h>

#include "allocator.hpp"

bool memoryOverflowTest() {
	Allocator al;
	al.makeAllocator(100);
	char *m1 = al.alloc(10);
	char *m2 = al.alloc(20);
	char *m3 = al.alloc(100);
	return (m3 == nullptr && m2 != nullptr && m1 != nullptr);
}

long int Test_Al() {
	Allocator al;
	al.makeAllocator(100);
	char *m1 = al.alloc(10);
	char *m2 = al.alloc(10);
	return (m1 - m2);
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

bool Some_makeAl() {
    Allocator allocator;
    allocator.makeAllocator(100);
    allocator.makeAllocator(50);
    return allocator.IsAllocated();
}
bool ResizeTest(){
    Allocator allocator;
    allocator.makeAllocator(1);
    char* ptr = allocator.alloc(1);
    ptr = allocator.alloc(1);
    return (ptr == nullptr);
}

bool If_Null(){
    Allocator allocator;
    char* ptr = allocator.alloc(0);
    return (ptr == nullptr);
}


class TestFoo : public ::testing::Test
{
protected:
	void SetUp()
	{
        std::cout << "SetUp" << std::endl;
	}
	void TearDown()
	{
        std::cout << "TearDown" << std::endl;
	}
};

TEST_F(TestFoo, test_mem)
{
	ASSERT_TRUE(memoryOverflowTest());
}
TEST_F(TestFoo, test_reset)
{
	ASSERT_TRUE(resetMethodTest());
}

TEST_F(TestFoo, test_newSpace)
{
	ASSERT_TRUE(newSpaceTest());
}

TEST_F(TestFoo, test_default)
{
	ASSERT_TRUE(defaultWorkTest());
}

TEST_F(TestFoo, reset_test)
{
	ASSERT_FALSE(Some_makeAl());
}
TEST_F(TestFoo, test_null)
{
	ASSERT_TRUE(If_Null());
}
TEST_F(TestFoo, test_resize)
{
	ASSERT_TRUE(ResizeTest());
}

TEST_F(TestFoo, r_test)
{
	ASSERT_EQ(Test_Al(), 0);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

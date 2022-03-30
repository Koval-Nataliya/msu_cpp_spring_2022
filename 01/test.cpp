#include <iostream>

#include <gtest/gtest.h>

#include "fake.hpp"

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
	ASSERT_TRUE(fake::memoryOverflowTest());
}
TEST_F(TestFoo, test_reset)
{
	ASSERT_TRUE(fake::resetMethodTest());
}

TEST_F(TestFoo, test_newSpace)
{
	ASSERT_TRUE(fake::newSpaceTest());
}

TEST_F(TestFoo, test_default)
{
	ASSERT_TRUE(fake::defaultWorkTest());
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

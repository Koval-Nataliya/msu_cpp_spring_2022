#include <iostream>
#include "matrix.hpp"
#include <gtest/gtest.h>


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

TEST_F(TestFoo, test_matr1) {
	Matrix m(3, 3);
	for(size_t i = 0; i < 3; ++i)
		for(size_t j = 0; j < 3; ++j)
			m[i][j] = 3*i + j;

	ASSERT_EQ(m.getRowSize(), 3);
    ASSERT_EQ(m.getColumnSize(), 3);
	for(size_t i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			ASSERT_EQ(m[i][j], 3*i + j);
	
	m *= 3;
	
	for(size_t i = 0; i < 3; ++i)
		for(size_t j = 0; j < 3; ++j)
			ASSERT_EQ(m[i][j], 9*i + 3*j);
	Matrix I(3, 3);
	for(size_t i = 0; i < 3; ++i)
		I[i][i] = 1;

	Matrix ans = I + m;
	for(size_t i = 0; i < 3; ++i)
		for(size_t j = 0; j < 3; ++j)
			ASSERT_EQ(ans[i][j], (9*i + 3*j + (i == j)));
}

TEST_F(TestFoo, test_matr3) {
	Matrix m(3, 3);
	bool f = false;
	
	try {
		m[100][5] = 1000;
	}
	catch(std::out_of_range const&){
		f = true;
	}
	
	ASSERT_TRUE(f);
}

TEST_F(TestFoo, test_matr4) {
	Matrix m(1, 1);
	m[0][0] = 100;
	ASSERT_EQ(m.getValue(0, 0), 100);
	m *= 100;
	ASSERT_EQ(m.getValue(0, 0), 10000);
}

TEST_F(TestFoo, test_matr5) {
	Matrix m(3, 3);
	for(size_t i = 0; i < 3; ++i)
		for(size_t j = 0; j < 3; ++j)
			m[i][j] = i + j;
	m *= 10;
	std::cout << "this is my <<" << std::endl;
	std::cout << m;
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

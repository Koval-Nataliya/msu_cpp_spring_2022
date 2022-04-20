#include <iostream>
#include <cassert>
#include "bigint.hpp"
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

TEST_F(TestFoo, test_1) {
    BigInt a("1111111111111111"), b("11");
    BigInt c = a + b;
    ASSERT_EQ(c, BigInt("1111111111111122"));
    c = a - b;
    ASSERT_EQ(c, BigInt("1111111111111100"));
    c = a*2;
    ASSERT_EQ(c, BigInt("2222222222222222"));
    c = b + 11;
    ASSERT_EQ(c, BigInt("22"));
    c = a*b;
    ASSERT_EQ(c, BigInt("12222222222222221"));
}

TEST_F(TestFoo, test_2){
    BigInt a("100"), b("105");
    BigInt c = 103;
    ASSERT_EQ(c > a, c < b);
    ASSERT_EQ(c >= a, c <= b);
    ASSERT_EQ(c, 103);
    ASSERT_NE(c, 100);
    c = -c;
    b = -b;
    assert(c < a && c > b);
    assert(c <= a && c >= b);
    ASSERT_NE(c, 103);
}

TEST_F(TestFoo, test_3){
    BigInt a = -123, b = 23;
    BigInt c = a + b;
    ASSERT_EQ(c, -100);
    c = a - b;
    ASSERT_EQ(c, -146);
    b = 121;
    c = a + b;
    ASSERT_EQ(c, -2);
    c = a*b;
    ASSERT_EQ(c, BigInt(-14883));
    ASSERT_EQ(c, BigInt("-14883"));
}

TEST_F(TestFoo, test_4){
    BigInt a("1111111111111111"), b("9999999999");
    BigInt c = a*b*b*2;
    ASSERT_EQ(c, BigInt("222222222177777755557777782222222222"));
}

TEST_F(TestFoo, test_5){
    BigInt a = 1;
    BigInt b("123456789012345678901234567890");
    BigInt c = a * b + 2;
    BigInt d;
    d = std::move(c);
    a = d + b;
    ASSERT_EQ(a, BigInt("246913578024691357802469135782"));
}

TEST_F(TestFoo, test_6){
    BigInt A(42);
    BigInt B = std::move(A);
    ASSERT_EQ(B, 42);
    ASSERT_TRUE(A.empty());
}

TEST_F(TestFoo, test_7){
    BigInt a = 99999;
    BigInt b("99900");
    BigInt c = a  - b;
    ASSERT_EQ(c, BigInt("99"));
}

TEST_F(TestFoo, test_8){
    BigInt a = 4;
    BigInt b("-25");
    BigInt c = a*b;
    ASSERT_EQ(c, BigInt("-100"));
}


TEST_F(TestFoo, test_9){
    BigInt a("4000000000000000000000001");
    BigInt b("-1");
    BigInt c = a*b;
    ASSERT_EQ(c, BigInt("-4000000000000000000000001"));
}

TEST_F(TestFoo, test_10){
    BigInt a("4000000000000000000000001");
    BigInt b("0");
    BigInt c = a*b;
    ASSERT_EQ(c, BigInt("0"));
}

TEST_F(TestFoo, test_11){
    BigInt a("9999");
    BigInt b("1");
    BigInt c = a + b;
    ASSERT_EQ(c, BigInt("10000"));
}


int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

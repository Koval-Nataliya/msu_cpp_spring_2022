#include <iostream>
#include <sstream>
#include <cassert>
#include "serializer.hpp"
#include "deserializer.hpp"
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

struct Data{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c);
    }
};

struct DataBig{
    uint64_t a;
    bool b;
    uint64_t c;
    uint64_t d;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c, d);
    }
};

struct DataInvalid{
    uint64_t a;
    bool b;
    int c;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(a, b, c);
    }
};


TEST_F(TestFoo, test_2) {
    Data x { 3, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.a, 3);
    ASSERT_EQ(x.b, y.b); 
    ASSERT_EQ(x.b == true);
    ASSERT_EQ(x.c, y.c);
    ASSERT_EQ(x.c == 2);
}

TEST_F(TestFoo, test_1) {
    Data x { 10, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataBig y { 0, false, 0, 10};

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::VariableBig);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.a, 10);
    ASSERT_EQ(x.b, y.b); 
    ASSERT_EQ(x.b == true);
    ASSERT_EQ(x.c, y.c); 
    ASSERT_EQ(x.c == 2);
}

TEST_F(TestFoo, test_3) {
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataInvalid y { 0, false, 0};

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::CorruptedArchive);
}

TEST_F(TestFoo, test_4) {
    DataInvalid x { 1, true, 2};

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err = serializer.save(x);

    ASSERT_EQ(err, Error::CorruptedArchive);
}

struct DataOnlyBool{
    bool t;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(t);
    }
};

struct DataOnlyInt{
    uint64_t t;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(t);
    }
};

TEST_F(TestFoo, test_5) {
    DataOnlyBool x {true}, y {false};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.t, y.t); 
    ASSERT_EQ(x.t == true);
}

TEST_F(TestFoo, test_6) {
    DataOnlyInt x {123123}, y {1111};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.t, y.t); 
    ASSERT_EQ(x.t, 123123);
}


int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#include <iostream>
#include <gtest/gtest.h>
#include "tokenParser.hpp"

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

TEST_F(TestFoo, test_pars1) {
    std::string str;
    std::vector<uint64_t> Digits;
    std::vector<std::string> Strings;

    TokenParser TokenParser;
    TokenParser.SetStartCallback([&str](){str += "B";});
    TokenParser.SetEndCallback([&str](){str += "E";});
    TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
        Digits.push_back(digitToken);
    });
    TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
        Strings.push_back(stringToken);
    });

    TokenParser.StartParsing("I love 899 apples and 9213 bananas   \
			2+2=5     \
			oh -1231");

    std::vector<uint64_t> DigitAns = {899, 9213};
    std::vector<std::string> StrAns = { "I", "love", "apples", "and", "bananas", "2+2=5", "oh", "-1231" };
    ASSERT_EQ(str, "BE");

    for(size_t i = 0; i < Digits.size(); ++i) {
        ASSERT_EQ(Digits[i], DigitAns[i]);
    }

    for(size_t i = 0; i < Strings.size(); ++i) {
        ASSERT_EQ(Strings[i], StrAns[i]);
    }
    ASSERT_EQ(Digits.size(), DigitAns.size());
    ASSERT_EQ(Strings.size(), StrAns.size());
}

TEST_F(TestFoo, test_pars2) {
    std::string str;
    std::vector<uint64_t> Digits;
    std::vector<std::string> Strings;

    TokenParser TokenParser;
    TokenParser.SetEndCallback([&str](){str += "E";});
    TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
        Digits.push_back(digitToken);
    });
    TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
        Strings.push_back(stringToken);
    });

    TokenParser.StartParsing("I love 43 \t \t \t \n         apples -1231");

    ASSERT_EQ(str, "E");
    std::vector<uint64_t> DigitAns = {43};
    std::vector<std::string> StrAns = { "I", "love", "apples", "-1231" };

    for(size_t i = 0; i < Digits.size(); ++i) {
        ASSERT_EQ(Digits[i], DigitAns[i]);
    }

    for(size_t i = 0; i < Strings.size(); ++i) {
        ASSERT_EQ(Strings[i], StrAns[i]);
    }
    ASSERT_EQ(Digits.size(), DigitAns.size());
    ASSERT_EQ(Strings.size(), StrAns.size());
}

TEST_F(TestFoo, test_pars3){
    std::vector<uint64_t> Digits;
    std::vector<std::string> Strings;

    TokenParser TokenParser;
    TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
        Digits.push_back(digitToken);
    });
    TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
        Strings.push_back(stringToken);
    });

    TokenParser.StartParsing("99123");
    std::vector<uint64_t> DigitAns = {99123};
    std::vector<std::string> StrAns = { };

    for(size_t i = 0; i < Digits.size(); ++i)
        ASSERT_EQ(Digits[i], DigitAns[i]);

    for(size_t i = 0; i < Strings.size(); ++i)
        ASSERT_EQ(Strings[i], StrAns[i]);

    ASSERT_EQ(Digits.size(), DigitAns.size());
    ASSERT_EQ(Strings.size(), StrAns.size());
}

TEST_F(TestFoo, test_pars4){
    std::vector<uint64_t> Digits;
    std::vector<std::string> Strings;

    TokenParser TokenParser;
    TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
        Digits.push_back(digitToken);
    });
    TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
        Strings.push_back(stringToken);
    });

    TokenParser.StartParsing("9999999999999999999123");
    std::vector<uint64_t> DigitAns = {};
    std::vector<std::string> StrAns = {"9999999999999999999123"};

    for(size_t i = 0; i < Digits.size(); ++i)
        ASSERT_EQ(Digits[i], DigitAns[i]);
    for(size_t i = 0; i < Strings.size(); ++i)
        ASSERT_EQ(Strings[i], StrAns[i]);

    ASSERT_EQ(Digits.size(), DigitAns.size());
    ASSERT_EQ(Strings.size(), StrAns.size());
}
TEST_F(TestFoo, test_pars5) {
    std::vector <uint64_t> Digits;
    std::vector <std::string> Strings;

    TokenParser TokenParser;
    //TokenParser.SetStartCallback([&str](){str = nullptr;});

    TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
            Digits.push_back(digitToken);});
    TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
            Strings.push_back(stringToken);});
    TokenParser.StartParsing("I l 4 3 \t \t \t \n         a l es  1 2 3 1");

    std::vector <uint64_t> DigitAns1 = {4, 3, 1, 2, 3, 1};
    std::vector <std::string> StrAns1 = {"I", "l", "a", "l", "es"};

    for(size_t i = 0; i<Digits.size(); ++i) {
        ASSERT_EQ(Digits[i], DigitAns1[i]);
    }

    for(size_t i = 0; i<Strings.size(); ++i) {
        ASSERT_EQ(Strings[i], StrAns1[i]);
    }
}
TEST_F(TestFoo, test_pars6) {
    std::vector <uint64_t> Digits;
    std::vector <std::string> Strings;

    TokenParser TokenParser;

    TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
            Digits.push_back(digitToken);});
    TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
            Strings.push_back(stringToken);});
    TokenParser.StartParsing("42str");
    std::vector <std::string> StrAns2 = {"42str"};
    for(size_t i = 0; i<Strings.size(); ++i) {
        ASSERT_EQ(Strings[i], StrAns2[i]);
    }
}
TEST_F(TestFoo, test_pars7) {
    std::vector <uint64_t> Digits;
    std::vector <std::string> Strings;

    TokenParser TokenParser;

    TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
        Digits.push_back(digitToken);});
    TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
        Strings.push_back(stringToken);});
    TokenParser.StartParsing("     ");
    std::vector <std::string> StrAns2 = {"     "};
    for(size_t i = 0; i<Strings.size(); ++i) {
        ASSERT_EQ(Strings[i], StrAns2[i]);
    }
}
TEST_F(TestFoo, test_pars8) {
    std::vector <uint64_t> Digits;
    std::vector <std::string> Strings;

    TokenParser TokenParser;

    TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
            Digits.push_back(digitToken);});
    TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
            Strings.push_back(stringToken);});
    TokenParser.StartParsing("");
    std::vector <std::string> StrAns2 = {""};
    for(size_t i = 0; i<Strings.size(); ++i) {
        ASSERT_EQ(Strings[i], StrAns2[i]);
    }
}
TEST_F(TestFoo, test_pars9) {
    std::vector <uint64_t> Digits;
    std::vector <std::string> Strings;

    TokenParser TokenParser;

    TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
        Digits.push_back(digitToken);});
    TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
        Strings.push_back(stringToken);});
    TokenParser.StartParsing("18446744073709551615");
    std::vector <std::string> StrAns2 = {"18446744073709551615"};

    for(size_t i = 0; i<Strings.size(); ++i) {
        ASSERT_EQ(Strings[i], StrAns2[i]);
    }
}
TEST_F(TestFoo, test_pars10) {
    std::vector <uint64_t> Digits;
    std::vector <std::string> Strings;

    TokenParser TokenParser;

    TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
            Digits.push_back(digitToken);});
    TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
            Strings.push_back(stringToken);});
    TokenParser.StartParsing("18446744073709551614");
    std::vector <uint64_t> DigitAns1 = {UINT64_MAX - 1};

    for(size_t i = 0; i<Digits.size(); ++i) {
        ASSERT_EQ(Digits[i], DigitAns1[i]);
    }
}
int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#pragma once
#include <string>
#include <functional>

using void_f = std::function<void()>;
using uint_func = std::function<void (uint64_t)>;
using str_f = std::function<void(std::string)>;


class TokenParser
{
private:
    bool spaceChar(char c){
        return c == ' ' || c == '\t' || c == '\n';
    }

    void tokenF(bool isDigit, std::string s, uint64_t x) {
        if(isDigit && digitF)
            digitF(x);
        else if(stringF)
            stringF(s);
    }

    std::function<void()> startF;

    std::function<void()> endF;

    std::function<void(uint64_t)> digitF;

    std::function<void(std::string)> stringF;

public:
    TokenParser() = default;

	void SetStartCallback(void_f t = nullptr){
        startF =  t;
    }

    void SetEndCallback(void_f t = nullptr){
        endF =  t;
    }

    void SetDigitTokenCallback(uint_func t = nullptr){
        digitF =  t;
    }

    void SetStringTokenCallback(str_f t = nullptr){
        stringF =  t;
    }	
	
	void StartParsing(const std::string s);
	
};

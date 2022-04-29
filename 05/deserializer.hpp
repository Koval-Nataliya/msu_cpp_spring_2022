#pragma once
#include <iostream>
#include "errors.hpp"

class Deserializer {
public:
    explicit Deserializer(std::istream& in): in_(in){ }

    template <class T>
    Error load(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT&&... args);
private:
    static constexpr char Separator = ' ';
    std::istream& in_;

    template <class T, class... ArgsT>
    Error process(T& value, ArgsT&&... args);

    template <class T>
    Error process(T& value);
};

#include "deserializer.tpp"

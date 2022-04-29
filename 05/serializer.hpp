#pragma once
#include <iostream>
#include "errors.hpp"

class Serializer {
public:
    explicit Serializer(std::ostream& out): out_(out){ }

    template <class T>
    Error save(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT... args);
private:
    static constexpr char Separator = ' ';
    std::ostream& out_;

    template <class T, class... ArgsT>
    Error process(T val, ArgsT&&... args);

    template <class T>
    Error process(T val);
};

#include "serializer.tpp"

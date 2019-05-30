#pragma once

#include <string>
#include <variant>

namespace m2tsext {


    class Error {
        std::string description;
    public:
        Error(const char* description) : description(description) {}
        Error(const std::string& description) : description(description) {}
        const std::string& what() const { return description; }
    };

    template <typename T>
    class Result {
        std::variant<T, Error> result;
    public:
        Result(const T& value) : result(value) {}
        Result(const Error& error) : result(error) {}
        bool isOK() const { return result.index() == 0; }
        const T& value() const { return std::get<0>(result); }
        const Error& error() const { return std::get<1>(result); }
    };
}
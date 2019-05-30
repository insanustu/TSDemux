#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

namespace m2tsext {
    template <typename T, size_t NBytes>
    struct ReadFromBigEndian;

    template <typename T>
    struct ReadFromBigEndian<T, 1> {
        static T read(const uint8_t* data) {
            return T(data[0]);
        }
    };

    template <typename T>
    struct ReadFromBigEndian<T, 2> {
        static T read(const uint8_t* data) {
            return data[1] | (T(data[0]) << 8);
        }
    };

    template <typename T>
    struct ReadFromBigEndian<T, 4> {
        static T read(const uint8_t* data) {
            return (T(data[0]) << 24) | (T(data[1]) << 16) | (T(data[2]) << 8) | data[3];
        }
    };

    template <typename T>
    struct ReadFromBigEndian<T, 8> {
        static T read(const uint8_t* data) {
            return (T(data[0]) << 56) | (T(data[1]) << 48) | (T(data[2]) << 40) | (T(data[3]) << 32) |
                   (T(data[4]) << 24) | (T(data[5]) << 16) | (T(data[6]) << 8)  | data[7];
        }
    };

    // function to read primitive types from big-endian
    // endian-independently
    template <typename T>
    T readFromBigEndian(const uint8_t* data) {
        return ReadFromBigEndian<T, sizeof(T)>::read(data);
    }

    inline uint16_t readPIDFromBigEndian(const uint8_t* data) {
        return m2tsext::readFromBigEndian<uint16_t>(data) & 0x1fff;
    }

    std::unordered_map<std::string, std::string> parseParameters (
            int numberOfParameters, char* parameters[]);

    inline void printErrorMessage(const std::string& msg) {
        std::cerr << "\033[1;31m" << msg << "\033[0m\n";
    }
}

#pragma once

#include "util.h"

namespace m2tsext {
    // Class wrapping PAT in MPEG-2 TS
    // +==============================
    // | 16     | program num
    // +------------------------------
    // | 3      | reserved bits
    // +------------------------------
    // | 13     | program map PID
    // +==============================
    class PAT {
    public:
        explicit PAT(const uint8_t* _data) : data(_data) {}

        uint16_t pid() const { return readPIDFromBigEndian(&data[2]); }
    private:
        const uint8_t* data;
    };
}

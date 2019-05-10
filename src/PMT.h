#pragma once

#include "util.h"

namespace m2tsext {

    // Class wrapping PMT of MPEG-2 TS
    // +==============================
    // | 3      | reserved bits
    // +------------------------------
    // | 13     | PCR PID
    // +------------------------------
    // | 4      | reserved bits
    // +------------------------------
    // | 2      | unused bits
    // +------------------------------
    // | 10     | program info length
    // +------------------------------
    // | N*8    | program descriptors
    // +------------------------------
    // | N*8    | elementary info data
    // +==============================
    class PMT {
    public:
        explicit PMT(const uint8_t* _data) : data(_data) {}

        uint16_t getPCR_PID() const { return readPIDFromBigEndian(data); }

        uint16_t getProgramInfoLength() const { return readFromBigEndian<uint16_t>(&data[2]) & 0x03ff; }

        const uint8_t* getElementaryStreamInfoData() const { return data + 4 + getProgramInfoLength(); }
        
    private:
        const uint8_t* data;
    };
}
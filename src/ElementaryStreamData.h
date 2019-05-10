#pragma once

#include "util.h"

namespace m2tsext {
    // Class wrapping elementary stream data
    // +=======================================
    // | 8      | stream type
    // +---------------------------------------
    // | 3      | reserved bits
    // +---------------------------------------
    // | 13     | elementary PID
    // +---------------------------------------
    // | 4      | reserved bits
    // +---------------------------------------
    // | 2      | ES info length unused bits
    // +---------------------------------------
    // | 10     | ES info length
    // +---------------------------------------
    // | N*8    | elementary stream descriptors
    // +=======================================
    class ElementaryStreamData {
    public:
        explicit ElementaryStreamData(const uint8_t* _data) : data(_data) {}

        uint8_t streamType() const { return data[0]; }

        uint16_t elementaryPID() const { return readFromBigEndian<uint16_t>(&data[1]) & 0x1fff; }

        uint16_t esInfoLength() const { return readFromBigEndian<uint16_t>(&data[3]) & 0x03ff; }

        uint16_t elementaryStreamDataSize() const { return esInfoLength() + 5; }

        bool isAudio() const;

        bool isVideo() const;
    private:
        const uint8_t* data;
    };
}

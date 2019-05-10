#pragma once

#include "util.h"

namespace m2tsext {
    // Class wrapping PES packet header
    // +===============================
    // | 24     | 0x000001
    // +-------------------------------
    // | 8      | stream id
    // +-------------------------------
    // | 16     | PES packet length
    // +-------------------------------
    // | > 24   | optional PES header
    // +-------------------------------
    // | ~~~    | stuffing bytes
    // +-------------------------------
    // | ~~~    | data
    // +===============================
    class PESPacketHeader {
    public:
        explicit PESPacketHeader(const uint8_t* _data) : data(_data) {}

        uint32_t startCode() const { return readFromBigEndian<uint32_t>(data); }

        uint16_t packetLength() const { return readFromBigEndian<uint16_t>(&data[4]); }

        uint8_t headerLength() const { return data[8] + 9; }

        uint16_t packetDataSize() const {
            if (packetLength() == 0) {
                return 0;
            }
            return packetLength() - headerLength() + 6;
        }
    private:
        const uint8_t* data;
    };
}

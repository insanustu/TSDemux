#pragma once

#include "util.h"

namespace m2tsext {
    // Class wrapping table header of MPEG-2 TS
    // +=======================================
    // | 8      | table ID
    // +---------------------------------------
    // | 1      | section syntax indicator
    // +---------------------------------------
    // | 1      | private bit
    // +---------------------------------------
    // | 2      | reserved bits
    // +---------------------------------------
    // | 2      | unused bits
    // +---------------------------------------
    // | 10     | section length
    // +---------------------------------------
    // | N*8    | syntax section/table data
    // +=======================================
    class TableHeader {
    public:
        explicit TableHeader(const uint8_t* _data) : data(_data) {}

        uint8_t tableID() const { return data[0]; }

        bool sectionSyntaxIndicator() const { return data[1] & 0x80; }

        bool privateBit() const { return data[1] & 0x40; }

        uint16_t sectionLength() const { return readFromBigEndian<uint16_t>(&data[1]) & 0x03ff; }

        const uint8_t* getTableData() const { return data + 8; }

        // table data length is a section length - CRC(4) - table_syntax_length(5)
        const uint16_t getTableDataLength() const { return sectionLength() - 9; }
    private:
        const uint8_t* data;
    };
}
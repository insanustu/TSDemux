#pragma once

#include <cstdint>

namespace m2tsext {
    // Class wrapping adaptation field in MPEG-2 TS packet header
    // +=========================================================
    // | 8      | adaptation field length
    // +---------------------------------------------------------
    // | 1      | discontinuity indicator
    // +---------------------------------------------------------
    // | 1      | random access indicator
    // +---------------------------------------------------------
    // | 1      | elementary stream priority indicator
    // +---------------------------------------------------------
    // | 1      | PCR flag
    // +---------------------------------------------------------
    // | 1      | OPCR flag
    // +---------------------------------------------------------
    // | 1      | splicing point flag
    // +---------------------------------------------------------
    // | 1      | transport private data flag
    // +---------------------------------------------------------
    // | 1      | adaptation field extension flag
    // +======== Optional =======================================
    // | 48     | PCR
    // +---------------------------------------------------------
    // | 48     | OPCR
    // +---------------------------------------------------------
    // | 8      | splice countdown
    // +---------------------------------------------------------
    // | 8      | transport private data length
    // +---------------------------------------------------------
    // | ~~~    | transport private data
    // +---------------------------------------------------------
    // | ~~~    | adaptation extension
    // +---------------------------------------------------------
    // | ~~~    | stuffing bytes
    // +=========================================================
    class AdaptationField {
    public:
        explicit AdaptationField(const uint8_t* _data) : data(_data) {}

        uint8_t adaptationFieldLength() const {
            return data[0];
        }

        bool discontinuity() const {
            return data[1] & 0x80;
        }

        bool randomAccess() const {
            return data[1] & 0x40;
        }

        bool elementaryStreamHighPriority() const {
            return data[1] & 0x20;
        }

        bool hasPCR() const {
            return data[1] & 0x10;
        }

        bool hasOPCR() const {
            return data[1] & 0x08;
        }

        bool hasSpliceCoundownField() const {
            return data[1] & 0x04;
        }

        bool hasTransportPrivateData() const {
            return data[1] & 0x02;
        }

        bool hasAdaptationExtention() const {
            return data[1] & 0x01;
        }

    private:
        const uint8_t* data;
    };
}
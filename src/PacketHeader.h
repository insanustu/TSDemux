#pragma once

#include "AdaptationField.h"
#include "util.h"

namespace m2tsext {
    constexpr uint16_t PACKET_SIZE = 188;

    // Class wrapping packet header of MPEG-2 TS
    // +========================================
    // | 8      | sync byte
    // +----------------------------------------
    // | 1      | transport error indicator
    // +----------------------------------------
    // | 1      | payload unit start indicator
    // +----------------------------------------
    // | 1      | transport priority
    // +----------------------------------------
    // | 13     | PID
    // +----------------------------------------
    // | 2      | transport scrambling
    // +----------------------------------------
    // | 2      | adaptation field control
    // +----------------------------------------
    // | 4      | continuity counter
    // +======= OPTIONAL =======================
    // | ~~~    | adaptation field
    // +----------------------------------------
    // | ~~~    | payload data
    // +========================================
    class PacketHeader {
    public:
        explicit PacketHeader(const uint8_t* _data) : data(_data) {}

        uint8_t syncByte() const {
            return data[0];
        }

        bool transportErrorIndicator() const {
            return data[1] & 0x80;
        }

        bool payloadUnitStartIndicator() const {
            return data[1] & 0x40;
        }

        bool transportPriority() const {
            return data[1] & 0x20;
        }

        uint16_t pid() const {
            return readPIDFromBigEndian(&data[1]);
        }

        uint8_t transportScramblingControl() const {
            return (data[3] & 0xc0) >> 6;
        }

        bool hasPayload() const {
            return data[3] & 0x10;
        }

        bool hasAdaptationField() const {
            return data[3] & 0x20;
        }

        uint8_t continuityCounter() const {
            return data[3] & 0xf;
        }

        const uint8_t* payloadData() const {
            auto payloadData = data + 4;
            if (hasAdaptationField()) {
                AdaptationField af(payloadData);
                payloadData += af.adaptationFieldLength();
                ++payloadData; // skip the adaptation field length length (1 byte)
            }
            return payloadData;
        }
        
        const uint16_t payloadSize() const {
            return uint16_t(data + PACKET_SIZE - payloadData());
        }
    private:
        const uint8_t* data;
    };
}

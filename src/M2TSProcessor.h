#pragma once

#include "PacketHeader.h"

#include <array>
#include <functional>
#include <vector>

namespace m2tsext {
    using TDataProcessor = std::function<bool(const uint8_t* data, size_t dataSize)>;
    using TPacketData = std::array<uint8_t, PACKET_SIZE>;

    // Class used for MPEG-2 TS splitting
    class M2TSProcessor {
    public:
        // function that process any input packet from MPEG-2 TS
        bool processPacket(TPacketData& packetData);

        // sets the function that is called for audio data from splitted TS
        void setAudioDataProcessor(TDataProcessor&& aProcessor);

        // sets the function that is called for video data from splitted TS
        void setVideoDataProcessor(TDataProcessor&& vProcessor);
    private:
        uint16_t programPID{};
        uint16_t videoPID{};
        uint16_t audioPID{};
        uint16_t videoPESLength{};
        uint16_t audioPESLength{};

        TDataProcessor audioDataProcessor;
        TDataProcessor videoDataProcessor;

        void processPATPacket(const PacketHeader& packetHeader);
        void processPMTPacket(const PacketHeader& packetHeader);
        void processAudioPacket(const PacketHeader& packetHeader);
        void processVideoPacket(const PacketHeader& packetHeader);
    };
}

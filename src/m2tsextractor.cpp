#include "m2tsextractor.h"
#include "M2TSProcessor.h"
#include "PacketHeader.h"

#include <iostream>

namespace m2tsext {
    bool extractVideoAudioFromM2TSSstream(
        std::istream& m2tsStream,
        std::ostream& outVideoStream,
        std::ostream& outAudioStream) {
        M2TSProcessor mpr;
        if (outAudioStream) {
            mpr.setAudioDataProcessor([&outAudioStream](const uint8_t* data, size_t dataSize) mutable {
                outAudioStream.write((char*)data, dataSize);
                return true;
                });
        }
        if (outVideoStream) {
            mpr.setVideoDataProcessor([&outVideoStream](const uint8_t* data, size_t dataSize) mutable {
                outVideoStream.write((char*)data, dataSize);
                return true;
                });
        }
        while (m2tsStream) {
            TPacketData data;
            m2tsStream.read((char*)data.data(), data.size());
            mpr.processPacket(data);
        }
        return true;
    }
}

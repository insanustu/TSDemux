#include "m2tsextractor.h"
#include "M2TSProcessor.h"
#include "PacketHeader.h"

#include <iostream>

namespace m2tsext {
    Result<std::monostate> extractVideoAudioFromM2TSSstream(
        std::istream& m2tsStream,
        std::ostream& outVideoStream,
        std::ostream& outAudioStream) {
        M2TSProcessor mpr;
        if (outAudioStream) {
            mpr.setAudioDataProcessor([&outAudioStream](const uint8_t* data, size_t dataSize) -> Result<std::monostate> {
                outAudioStream.write((char*)data, dataSize);
                if (!outAudioStream.good()) {
                    return Error("Error writing audio stream occured");
                }
                return std::monostate();
            });
        }
        if (outVideoStream) {
            mpr.setVideoDataProcessor([&outVideoStream](const uint8_t* data, size_t dataSize) -> Result<std::monostate> {
                outVideoStream.write((char*)data, dataSize);
                if (!outVideoStream.good()) {
                    return Error("Error writing video stream occured");
                }
                return std::monostate();
            });
        }
        while (m2tsStream) {
            TPacketData data;
            m2tsStream.read((char*)data.data(), data.size());
            const auto bytesRead = m2tsStream.gcount();
            if (bytesRead != 0 && bytesRead != data.size()) {
                return Error("Error occured while reading from the input stream");
            }
            const auto& result = mpr.processPacket(data);
            if (result.isOK()) {
                continue;
            }
            return result;
        }
        return std::monostate();
    }
}

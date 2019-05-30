#include "ElementaryStreamData.h"
#include "M2TSProcessor.h"
#include "PacketHeader.h"
#include "TableHeader.h"
#include "PAT.h"
#include "PMT.h"
#include "PESPacketHeader.h"

namespace {
    enum class PredefinedPid : uint16_t {
        PAT         = 0x0000,
        CAT         = 0x0001,
        TSDT        = 0x0002,
        IPMP        = 0x0003,
        NIT_ST      = 0x0010,
        STD_BAT_ST  = 0x0011,
        EIT_ST_CIT  = 0x0012,
        RST_ST      = 0x0013,
        TDT_TOT_ST  = 0x0014,
        NET_SYNC    = 0x0015,
        RNT         = 0x0016,
        INBAND_SIG  = 0x001C,
        MEASURE     = 0x001D,
        DIT         = 0x001E,
        SIT         = 0x001F
    };
}

namespace m2tsext {

    Result<std::monostate> M2TSProcessor::processPacket(TPacketData& packetData) {
        PacketHeader ph(packetData.data());
        if (ph.syncByte() != 'G') {
            // format of ts is corrupted
            return Error("Wrong sync byte error: " + ph.syncByte());;
        }
        if (ph.transportErrorIndicator()) {
            // skip broken packet
            return std::monostate();
        }
        if (!ph.hasPayload()) {
            // skip packet without a payload
            return std::monostate();
        }
        if (PredefinedPid(ph.pid()) == PredefinedPid::PAT) {
            processPATPacket(ph);
        }
        else if (ph.pid() == programPID) {
            processPMTPacket(ph);
        }
        else if (ph.pid() == audioPID) {
            const auto& result = processAudioPacket(ph);
            if (result.isOK()) {
                return result;
            }
            return Error("Error while processing an audio packet: " + result.error().what());
        }
        else if (ph.pid() == videoPID) {
            const auto& result = processVideoPacket(ph);
            if (result.isOK()) {
                return result;
            }
            return Error("Error while processing a video packet: " + result.error().what());
        }
        return std::monostate();
    }

    void M2TSProcessor::setAudioDataProcessor(TDataProcessor&& aProcessor) {
        audioDataProcessor = std::move(aProcessor);
    }

    void M2TSProcessor::setVideoDataProcessor(TDataProcessor&& vProcessor) {
        videoDataProcessor = std::move(vProcessor);
    }

    void M2TSProcessor::processPATPacket(const PacketHeader& packetHeader)
    {
        auto tableHeader = packetHeader.payloadData();
        if (packetHeader.payloadUnitStartIndicator()) {
            auto fillers = tableHeader[0];
            ++tableHeader;
            tableHeader += fillers;
        }
        TableHeader th(tableHeader);
        if (th.getTableDataLength() == 0) {
            return;
        }
        programPID = PAT(th.getTableData()).pid();
    }

    void M2TSProcessor::processPMTPacket(const PacketHeader& packetHeader)
    {
        auto tableHeader = packetHeader.payloadData();
        if (packetHeader.payloadUnitStartIndicator()) {
            auto fillers = tableHeader[0];
            ++tableHeader;
            tableHeader += fillers;
        }
        TableHeader th(tableHeader);
        if (th.getTableDataLength() == 0) {
            return;
        }
        PMT pmt(th.getTableData());
        auto totalElementaryStreamInfoLength = th.getTableDataLength() - 4 - pmt.getProgramInfoLength();
        auto totalElementaryStreamStartData = pmt.getElementaryStreamInfoData();
        while (totalElementaryStreamInfoLength > 0) {
            ElementaryStreamData esd(totalElementaryStreamStartData);
            if (esd.isAudio()) {
                audioPID = esd.elementaryPID();
            }
            if (esd.isVideo()) {
                videoPID = esd.elementaryPID();
            }
            totalElementaryStreamInfoLength -= esd.elementaryStreamDataSize();
            totalElementaryStreamStartData += esd.elementaryStreamDataSize();
        }
    }

    Result<std::monostate> processPES(const PacketHeader& packetHeader,
        TDataProcessor& dataProcessor,
        uint16_t& remainingPESLength) {
        const uint8_t* data = packetHeader.payloadData();
        uint16_t dataSize = packetHeader.payloadSize();
        if (packetHeader.payloadUnitStartIndicator()) {
            PESPacketHeader pes(packetHeader.payloadData());
            data += pes.headerLength();
            remainingPESLength = pes.packetDataSize();
            dataSize -= pes.headerLength();
        }
        if (remainingPESLength != 0) {
            dataSize = std::min(dataSize, remainingPESLength);
            remainingPESLength -= dataSize;
        }
        return dataProcessor(data, dataSize);
    }

    Result<std::monostate> M2TSProcessor::processAudioPacket(const PacketHeader& packetHeader)
    {
        if (!audioDataProcessor) {
            return std::monostate();
        }
        return processPES(packetHeader, audioDataProcessor, audioPESLength);
    }

    Result<std::monostate> M2TSProcessor::processVideoPacket(const PacketHeader& packetHeader)
    {
        if (!videoDataProcessor) {
            return std::monostate();
        }
        return processPES(packetHeader, videoDataProcessor, videoPESLength);
    }
}

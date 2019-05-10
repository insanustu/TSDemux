#include "ElementaryStreamData.h"

#include <unordered_set>

namespace {
    enum ElementaryStreamType : uint8_t {
        MPEG_1_VIDEO                                = 0x01,
        MPEG_2_HIGHER_RATE_INTERLACED_VIDEO         = 0x02,
        MPEG_1_AUDIO                                = 0x03,
        MPEG_2_HALVED_SAMPLE_RATE_AUDIO             = 0x04,
        MPEG_2_LOWER_BIT_RATE_AUDIO                 = 0x0f,
        MPEG_4_H_263_BASED_VIDEO                    = 0x10,
        MPEG_4_LOAS_MULTI_FORMAT_FRAMED_AUDIO       = 0x11,
        H_264_LOWER_BIT_RATE_VIDEO                  = 0x1b,
        MPEG_4_RAW_AUDIO                            = 0x1c,
        MPEG_4_AUXILIARY_VIDEO                      = 0x1e,
        JPEG_2000_VIDEO                             = 0x21,
        H_265_ULTRA_HD_VIDEO                        = 0x24,
        PCM_FOR_BLUE_RAY_AUDIO                      = 0x80,
        DOLBY_DIGITAL_FOR_BLUE_RAY_AUDIO            = 0x81,
        DOLBY_TRUE_HD_LOSSLESS_FOR_BLUE_RAY_AUDIO   = 0x83,
        DOLBY_DIGITAL_PLUS_FOR_BLUE_RAY_AUDIO       = 0x84,
        DTS_8_CHANNEL_FOR_BLUE_RAY_AUDIO            = 0x85,
        DTS_8_LOSSLESS_FOR_BLUE_RAY_AUDIO           = 0x86,
        DOLBY_DIGITAL_PLUS_AUDIO                    = 0x87,
        DOLBY_DIGITAL_WITH_AES_AUDIO                = 0xc1,
        ADTS_AAC_WITH_AES_AUDIO                     = 0xcf,
        MICROSOFT_WINDOWS_MEDIA_9_VIDEO             = 0xea
    };

    const std::unordered_set<ElementaryStreamType, std::hash<uint8_t>> AUDIO_STREAMS = {
        ElementaryStreamType::MPEG_1_AUDIO,
        ElementaryStreamType::MPEG_2_HALVED_SAMPLE_RATE_AUDIO,
        ElementaryStreamType::MPEG_2_LOWER_BIT_RATE_AUDIO,
        ElementaryStreamType::MPEG_4_LOAS_MULTI_FORMAT_FRAMED_AUDIO,
        ElementaryStreamType::MPEG_4_RAW_AUDIO,
        ElementaryStreamType::PCM_FOR_BLUE_RAY_AUDIO,
        ElementaryStreamType::DOLBY_DIGITAL_FOR_BLUE_RAY_AUDIO,
        ElementaryStreamType::DOLBY_TRUE_HD_LOSSLESS_FOR_BLUE_RAY_AUDIO,
        ElementaryStreamType::DOLBY_DIGITAL_PLUS_FOR_BLUE_RAY_AUDIO,
        ElementaryStreamType::DTS_8_CHANNEL_FOR_BLUE_RAY_AUDIO,
        ElementaryStreamType::DTS_8_LOSSLESS_FOR_BLUE_RAY_AUDIO,
        ElementaryStreamType::DOLBY_DIGITAL_PLUS_AUDIO,
        ElementaryStreamType::DOLBY_DIGITAL_WITH_AES_AUDIO,
        ElementaryStreamType::ADTS_AAC_WITH_AES_AUDIO
    };

    const std::unordered_set<ElementaryStreamType, std::hash<uint8_t>> VIDEO_STREAMS = {
        ElementaryStreamType::MPEG_1_VIDEO,
        ElementaryStreamType::MPEG_2_HIGHER_RATE_INTERLACED_VIDEO,
        ElementaryStreamType::MPEG_4_H_263_BASED_VIDEO,
        ElementaryStreamType::H_264_LOWER_BIT_RATE_VIDEO,
        ElementaryStreamType::MPEG_4_AUXILIARY_VIDEO,
        ElementaryStreamType::JPEG_2000_VIDEO,
        ElementaryStreamType::H_265_ULTRA_HD_VIDEO,
        ElementaryStreamType::MICROSOFT_WINDOWS_MEDIA_9_VIDEO
    };
}

namespace m2tsext {
    bool ElementaryStreamData::isAudio() const {
        return AUDIO_STREAMS.find(ElementaryStreamType(streamType())) != AUDIO_STREAMS.end();
    }

    bool ElementaryStreamData::isVideo() const {
        return VIDEO_STREAMS.find(ElementaryStreamType(streamType())) != VIDEO_STREAMS.end();
    }
}

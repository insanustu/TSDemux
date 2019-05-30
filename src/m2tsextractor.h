#pragma once

#include "Error.h"

#include <istream>

namespace m2tsext {
    // gets a stream containing MPEG-2 TS
    // splits it on video and audio
    // and writes the splitted into output streams
    // @m2tsStream      - input MPEG-2 TS stream to split
    // @outVideoStream  - output video stream
    // @outAudioStream  - output audio stream
    Result<std::monostate> extractVideoAudioFromM2TSSstream(
        std::istream& m2tsStream,
        std::ostream& outVideoStream,
        std::ostream& outAudioStream);
}

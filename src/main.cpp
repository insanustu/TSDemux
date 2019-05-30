#include "Error.h"
#include "m2tsextractor.h"
#include "util.h"

#include <fstream>
#include <iostream>

void printErrorParameters() {
    m2tsext::printErrorMessage( "Wrong parameters. Usage:\n"
         "\tts-demux -i <input_file> -a <audio_file> -v <video_file>\n");
}

void printErrorNoInputFile(const std::string& file) {
    m2tsext::printErrorMessage("No such file: " + file);
}

void printErrorNoOutputFile(const std::string& file) {
    m2tsext::printErrorMessage("Could not create: " + file);
}

int main(int argc, char* argv[]) {
    auto parameters = m2tsext::parseParameters(argc, argv);
    if (parameters.empty()) {
        printErrorParameters();
        return 1;
    }
    auto inputFileName = parameters["-i"];
    auto audioOutputFileName = parameters["-a"];
    auto videoOutputFileName = parameters["-v"];
    if (inputFileName.empty() ||
        (audioOutputFileName.empty() && videoOutputFileName.empty())) {
        printErrorParameters();
        return 1;
    }
    std::ifstream i(inputFileName, std::ios::binary);
    if (!i.is_open()) {
        printErrorNoInputFile(inputFileName);
        return 1;
    }
    std::ofstream a(audioOutputFileName, std::ios::binary);
    if (!audioOutputFileName.empty() && !a.is_open()) {
        printErrorNoOutputFile(audioOutputFileName);
        return 1;
    }
    std::ofstream v(videoOutputFileName, std::ios::binary);
    if (!videoOutputFileName.empty() && !v.is_open()) {
        printErrorNoOutputFile(videoOutputFileName);
        return 1;
    }
    const auto& result = m2tsext::extractVideoAudioFromM2TSSstream(i, v, a);
    if (!result.isOK()) {
        m2tsext::printErrorMessage(result.error().what());
        return 1;
    }
    return 0;
}

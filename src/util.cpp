#include "util.h"

namespace m2tsext {
    std::unordered_map<std::string, std::string> parseParameters(
            int numberOfParameters, char* parameters[]) {
        if ((numberOfParameters & 1) == 0) { // if number of parameters (but 0) is odd, return empty
            return {};
        }
        std::unordered_map<std::string, std::string> toReturn;
        for(auto i = 1; i < numberOfParameters; i += 2) {
            toReturn[parameters[i]] = parameters[i+1];
        }
        return toReturn;
    }
}

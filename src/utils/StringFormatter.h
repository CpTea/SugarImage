#ifndef SUGAR_STRING_FORMATTER
#define SUGAR_STRING_FORMATTER

#include <string>

namespace sugar::image::similarity::utils {

    std::string bytesToHexadecimalString(const uint8_t* source, size_t length);

    std::string bytesToHexadecimalString(const std::string& source);

    std::string binaryStringToHexadecimalString(const uint8_t* source,
        size_t length);

    std::string binaryStringToHexadecimalString(const std::string& source);

}

#endif
#include "StringFormatter.h"
#include <cmath>

constexpr int8_t hexadecimal_characters[16] = {'0', '1', '2', '3', '4', '5',
                                               '6', '7', '8', '9', 'a', 'b',
                                               'c', 'd', 'e', 'f'};

std::string sugar::image::similarity::utils::bytesToHexadecimalString(
    const uint8_t* source,
    size_t length) {
    std::string str;
    str.reserve(length << 1);
    for (size_t i = 0; i < length; ++i) {
        int t = source[i];
        int a = t / 16;
        int b = t % 16;
        str.append(1, hexadecimal_characters[a]);
        str.append(1, hexadecimal_characters[b]);
    }
    return str;
}

std::string sugar::image::similarity::utils::bytesToHexadecimalString(
    const std::string& source) {
    return bytesToHexadecimalString((const uint8_t*)source.c_str(),
                                    source.length());
}

std::string sugar::image::similarity::utils::binaryStringToHexadecimalString(
    const uint8_t* source,
    size_t length) {
    std::string str;
    str.reserve((size_t)ceil(length / 4.0));
    int t = 0, j = 0;
    for (size_t i = 0; i < length; ++i) {
        if (j != 3) {
            t |= (source[i] - '0') << j;
            ++j;
        } else {
            str.append(1, hexadecimal_characters[t]);
            t = 0;
            j = 0;
        }
    }
    if (j != 0) {
        str.append(1, hexadecimal_characters[t]);
    }
    return str;
}

std::string sugar::image::similarity::utils::binaryStringToHexadecimalString(
    const std::string& source) {
    return binaryStringToHexadecimalString((const uint8_t*)source.c_str(),
                                           source.length());
}
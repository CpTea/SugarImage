#include "MD5.h"
#include "utils/StringFormatter.h"
#include <fstream>
#include <cstring>

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define FF(a, b, c, d, x, s, ac)        \
  {                                     \
    (a) += F((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT((a), (s));        \
    (a) += (b);                         \
  }
#define GG(a, b, c, d, x, s, ac)        \
  {                                     \
    (a) += G((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT((a), (s));        \
    (a) += (b);                         \
  }
#define HH(a, b, c, d, x, s, ac)        \
  {                                     \
    (a) += H((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT((a), (s));        \
    (a) += (b);                         \
  }
#define II(a, b, c, d, x, s, ac)        \
  {                                     \
    (a) += I((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT((a), (s));        \
    (a) += (b);                         \
  }

constexpr uint8_t PADDING[64] = { 0x80 };

sugar::image::similarity::hash::MD5::MD5(const void* input, size_t length) {
    reset();
    update((const uint8_t*)input, length);
}

sugar::image::similarity::hash::MD5::MD5(const std::string& str) {
    reset();
    update((const uint8_t*)str.c_str(), str.length());
}

sugar::image::similarity::hash::MD5::MD5(std::ifstream& in) {
    reset();

    if (!in) {
        return;
    }

    std::streamsize length;
    char buffer[BUFFER_SIZE];
    while (!in.eof()) {
        in.read(buffer, BUFFER_SIZE);
        length = in.gcount();
        if (length > 0) {
            update((const uint8_t*)buffer, length);
        }
    }
    in.close();
}

std::string sugar::image::similarity::hash::MD5::value() {
    return toString();
}

void sugar::image::similarity::hash::MD5::final() {
    uint8_t bits[8];
    uint32_t oldState[4];
    uint32_t oldCount[2];
    uint32_t index, padLen;

    // Save current state and count.
    memcpy(oldState, _state, 16);
    memcpy(oldCount, _count, 8);

    // Save number of bits
    encode(_count, bits, 8);

    // Pad out to 56 mod 64.
    index = (uint32_t)((_count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    update(PADDING, padLen);

    // Append length (before padding)
    update(bits, 8);

    // Store state in digest
    encode(_state, _digest, 16);

    // Restore current state and count.
    memcpy(_state, oldState, 16);
    memcpy(_count, oldCount, 8);
}

void sugar::image::similarity::hash::MD5::transform(const uint8_t block[64]) {
    uint32_t a = _state[0], b = _state[1], c = _state[2], d = _state[3], x[16];

    decode(block, x, 64);

    // Round 1
    FF(a, b, c, d, x[0], S11, 0xd76aa478);
    FF(d, a, b, c, x[1], S12, 0xe8c7b756);
    FF(c, d, a, b, x[2], S13, 0x242070db);
    FF(b, c, d, a, x[3], S14, 0xc1bdceee);
    FF(a, b, c, d, x[4], S11, 0xf57c0faf);
    FF(d, a, b, c, x[5], S12, 0x4787c62a);
    FF(c, d, a, b, x[6], S13, 0xa8304613);
    FF(b, c, d, a, x[7], S14, 0xfd469501);
    FF(a, b, c, d, x[8], S11, 0x698098d8);
    FF(d, a, b, c, x[9], S12, 0x8b44f7af);
    FF(c, d, a, b, x[10], S13, 0xffff5bb1);
    FF(b, c, d, a, x[11], S14, 0x895cd7be);
    FF(a, b, c, d, x[12], S11, 0x6b901122);
    FF(d, a, b, c, x[13], S12, 0xfd987193);
    FF(c, d, a, b, x[14], S13, 0xa679438e);
    FF(b, c, d, a, x[15], S14, 0x49b40821);

    // Round 2
    GG(a, b, c, d, x[1], S21, 0xf61e2562);
    GG(d, a, b, c, x[6], S22, 0xc040b340);
    GG(c, d, a, b, x[11], S23, 0x265e5a51);
    GG(b, c, d, a, x[0], S24, 0xe9b6c7aa);
    GG(a, b, c, d, x[5], S21, 0xd62f105d);
    GG(d, a, b, c, x[10], S22, 0x2441453);
    GG(c, d, a, b, x[15], S23, 0xd8a1e681);
    GG(b, c, d, a, x[4], S24, 0xe7d3fbc8);
    GG(a, b, c, d, x[9], S21, 0x21e1cde6);
    GG(d, a, b, c, x[14], S22, 0xc33707d6);
    GG(c, d, a, b, x[3], S23, 0xf4d50d87);
    GG(b, c, d, a, x[8], S24, 0x455a14ed);
    GG(a, b, c, d, x[13], S21, 0xa9e3e905);
    GG(d, a, b, c, x[2], S22, 0xfcefa3f8);
    GG(c, d, a, b, x[7], S23, 0x676f02d9);
    GG(b, c, d, a, x[12], S24, 0x8d2a4c8a);

    // Round 3
    HH(a, b, c, d, x[5], S31, 0xfffa3942);
    HH(d, a, b, c, x[8], S32, 0x8771f681);
    HH(c, d, a, b, x[11], S33, 0x6d9d6122);
    HH(b, c, d, a, x[14], S34, 0xfde5380c);
    HH(a, b, c, d, x[1], S31, 0xa4beea44);
    HH(d, a, b, c, x[4], S32, 0x4bdecfa9);
    HH(c, d, a, b, x[7], S33, 0xf6bb4b60);
    HH(b, c, d, a, x[10], S34, 0xbebfbc70);
    HH(a, b, c, d, x[13], S31, 0x289b7ec6);
    HH(d, a, b, c, x[0], S32, 0xeaa127fa);
    HH(c, d, a, b, x[3], S33, 0xd4ef3085);
    HH(b, c, d, a, x[6], S34, 0x4881d05);
    HH(a, b, c, d, x[9], S31, 0xd9d4d039);
    HH(d, a, b, c, x[12], S32, 0xe6db99e5);
    HH(c, d, a, b, x[15], S33, 0x1fa27cf8);
    HH(b, c, d, a, x[2], S34, 0xc4ac5665);

    // Round 4
    II(a, b, c, d, x[0], S41, 0xf4292244);
    II(d, a, b, c, x[7], S42, 0x432aff97);
    II(c, d, a, b, x[14], S43, 0xab9423a7);
    II(b, c, d, a, x[5], S44, 0xfc93a039);
    II(a, b, c, d, x[12], S41, 0x655b59c3);
    II(d, a, b, c, x[3], S42, 0x8f0ccc92);
    II(c, d, a, b, x[10], S43, 0xffeff47d);
    II(b, c, d, a, x[1], S44, 0x85845dd1);
    II(a, b, c, d, x[8], S41, 0x6fa87e4f);
    II(d, a, b, c, x[15], S42, 0xfe2ce6e0);
    II(c, d, a, b, x[6], S43, 0xa3014314);
    II(b, c, d, a, x[13], S44, 0x4e0811a1);
    II(a, b, c, d, x[4], S41, 0xf7537e82);
    II(d, a, b, c, x[11], S42, 0xbd3af235);
    II(c, d, a, b, x[2], S43, 0x2ad7d2bb);
    II(b, c, d, a, x[9], S44, 0xeb86d391);

    _state[0] += a;
    _state[1] += b;
    _state[2] += c;
    _state[3] += d;
}

void sugar::image::similarity::hash::MD5::encode(const uint32_t* input,
    uint8_t* output,
    size_t length) {
    for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
        output[j] = (uint8_t)(input[i] & 0xff);
        output[j + 1] = (uint8_t)((input[i] >> 8) & 0xff);
        output[j + 2] = (uint8_t)((input[i] >> 16) & 0xff);
        output[j + 3] = (uint8_t)((input[i] >> 24) & 0xff);
    }
}

void sugar::image::similarity::hash::MD5::decode(const uint8_t* input,
    uint32_t* output,
    size_t length) {
    for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
        output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) |
            (((uint32_t)input[j + 2]) << 16) |
            (((uint32_t)input[j + 3]) << 24);
    }
}

void sugar::image::similarity::hash::MD5::update(const uint8_t* input,
    size_t length) {
    uint32_t i, index, partLen;
    _finished = false;

    // Compute number of bytes mod 64
    index = (uint32_t)((_count[0] >> 3) & 0x3f);

    // update number of bits
    if ((_count[0] += ((uint32_t)length << 3)) < ((uint32_t)length << 3)) {
        ++_count[1];
    }
    _count[1] += ((uint32_t)length >> 29);
    partLen = 64 - index;

    // transform as many times as possible.
    if (length >= partLen) {
        memcpy(&_buffer[index], input, partLen);
        transform(_buffer);

        for (i = partLen; i + 63 < length; i += 64) {
            transform(&input[i]);
        }
        index = 0;

    } else {
        i = 0;
    }

    // Buffer remaining input
    memcpy(&_buffer[index], &input[i], length - i);
}

const uint8_t* sugar::image::similarity::hash::MD5::digest() {
    if (!_finished) {
        _finished = true;
        this->final();
    }
    return _digest;
}

std::string sugar::image::similarity::hash::MD5::toString() {
    return utils::bytesToHexadecimalString(digest(), 16);
}

void sugar::image::similarity::hash::MD5::reset() {
    _finished = false;
    // reset number of bits.
    _count[0] = _count[1] = 0;
    // Load magic initialization constants.
    _state[0] = 0x67452301;
    _state[1] = 0xefcdab89;
    _state[2] = 0x98badcfe;
    _state[3] = 0x10325476;
}

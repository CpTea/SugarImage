#ifndef SUGAR_MD5
#define SUGAR_MD5

#include <string>

namespace sugar::image::similarity::hash {
    class MD5 {
    public:
        MD5(const void* input, size_t length);
        MD5(const std::string& str);
        MD5(std::ifstream& in);
        std::string value();

    private:
        void final();
        void transform(const uint8_t block[64]);
        void encode(const uint32_t* input, uint8_t* output, size_t length);
        void decode(const uint8_t* input, uint32_t* output, size_t length);
        void update(const uint8_t* input, size_t length);
        const uint8_t* digest();
        std::string toString();
        void reset();

        MD5(const MD5&) = delete;
        MD5& operator=(const MD5&) = delete;

    private:
        uint32_t _state[4];
        uint32_t _count[2];
        uint8_t _buffer[64];
        uint8_t _digest[16];
        bool _finished;
        enum { BUFFER_SIZE = 1024 };
    };
}

#endif
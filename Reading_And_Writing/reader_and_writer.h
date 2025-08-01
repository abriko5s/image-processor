#pragma once

#include "../Libraries.h"
#include "../Image/image.h"

namespace reading_and_writing {
const int GetPaddingSize(const size_t& width);
}  // namespace reading_and_writing

namespace reading {
class Reader {
public:
    Reader() = default;

    ~Reader() = default;

    Image ReadFile(const ::std::string& filepath);

private:
    std::string filepath_;
    static size_t BytesToNumber(unsigned char* bytes);
};
}  // namespace reading

namespace writing {
class Writer {
public:
    Writer() = default;

    ~Writer() = default;

    static void WriteFile(const Image& image, const ::std::string& filepath);

private:
    std::string filepath_;
};
}  // namespace writing

namespace headers {
const uint32_t BMP_HEADER_SIZE = 14;
const uint32_t DIB_HEADER_SIZE = 40;

const std::array<char, 2> FORMAT_BYTES = {'B', 'M'};
const std::array<int32_t, 3> SHIFT_BYTES = {8, 16, 24};

const int FIRST_SHIFT_INDEX = 0;
const int SECOND_SHIFT_INDEX = 1;
const int THIRD_SHIFT_INDEX = 2;
const int SIZE_INDEX = 10;
const uint32_t BYTES_PER_PIXEL = 3;

const uint32_t WIDTH_POSITION = 4;
const uint32_t HEIGHT_POSITION = 8;

const uint16_t BITS_PER_PIXEL = 24;
const int DIB_HEADER_SIZE_POS = 12;
const int BITS_PER_PIXEL_POS = 14;
const int F_B_FIRST_POS = 0;
const int F_B_SECOND_POS = 1;

const uint32_t CNT_OF_PLANES = 1;
const size_t CNT_OF_PLANES_POSITION = 12;
}  // namespace headers

#include "reader_and_writer.h"

void writing::Writer::WriteFile(const Image& image, const std::string& filename) {

    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file " + filename + " for writing");
    }
    if (errno == EACCES) {
        throw std::invalid_argument("Permission to " + filename + " denied");
    }

    unsigned char bmp_pad[3] = {0, 0, 0};
    const int padding = reading_and_writing::GetPaddingSize(image.GetWidth());

    const uint32_t image_size =
        headers::BMP_HEADER_SIZE + headers::DIB_HEADER_SIZE +
        static_cast<uint32_t>(image.GetWidth()) * static_cast<uint32_t>(image.GetHeight()) * headers::BYTES_PER_PIXEL +
        padding * static_cast<uint32_t>(image.GetHeight());

    unsigned char bmp_header[headers::BMP_HEADER_SIZE] = {};
    bmp_header[headers::F_B_FIRST_POS] = static_cast<unsigned char>(headers::FORMAT_BYTES[headers::F_B_FIRST_POS]);
    bmp_header[headers::F_B_SECOND_POS] = static_cast<unsigned char>(headers::FORMAT_BYTES[headers::F_B_SECOND_POS]);
    bmp_header[headers::SIZE_INDEX] = static_cast<unsigned char>(headers::BMP_HEADER_SIZE + headers::DIB_HEADER_SIZE);

    uint32_t file_size = image_size;
    std::memcpy(bmp_header + 2, &file_size, sizeof(file_size));

    unsigned char dib_header[headers::DIB_HEADER_SIZE] = {};
    dib_header[0] = static_cast<unsigned char>(headers::DIB_HEADER_SIZE);
    dib_header[headers::DIB_HEADER_SIZE_POS] = static_cast<unsigned char>(headers::DIB_HEADER_SIZE);
    dib_header[headers::BITS_PER_PIXEL_POS] = static_cast<unsigned char>(headers::BITS_PER_PIXEL);

    uint32_t width = image.GetWidth();
    uint32_t height = image.GetHeight();
    std::memcpy(dib_header + headers::WIDTH_POSITION, &width, sizeof(width));
    std::memcpy(dib_header + headers::HEIGHT_POSITION, &height, sizeof(height));

    file.write(reinterpret_cast<char*>(bmp_header), headers::BMP_HEADER_SIZE);
    file.write(reinterpret_cast<char*>(dib_header), headers::DIB_HEADER_SIZE);

    for (int y = static_cast<int>(image.GetHeight()) - 1; y >= 0; --y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            unsigned char char_blue = (image.GetStraightPixel(x, y).blue);
            unsigned char char_green = (image.GetStraightPixel(x, y).green);
            unsigned char char_red = (image.GetStraightPixel(x, y).red);
            unsigned char color[] = {char_blue, char_green, char_red};
            file.write(reinterpret_cast<char*>(color), sizeof(color));
        }
        file.write(reinterpret_cast<char*>(bmp_pad), padding);
    }
    file.close();
}
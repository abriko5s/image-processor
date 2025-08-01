#include "reader_and_writer.h"

Image reading::Reader::ReadFile(const std::string& filepath) {

    filepath_ = filepath;

    unsigned char bmp_header[headers::BMP_HEADER_SIZE];

    std::ifstream img_file;
    img_file.open(filepath_, std::ios::binary | std::ios::in);

    if (!img_file.is_open()) {
        throw std::invalid_argument("File " + filepath_ + " not found");
    }
    if (errno == EACCES) {
        throw std::invalid_argument("File " + filepath_ + " no accessible");
    }
    img_file.read(reinterpret_cast<char*>(bmp_header), headers::BMP_HEADER_SIZE);

    if ((bmp_header[headers::F_B_FIRST_POS] != headers::FORMAT_BYTES[headers::F_B_FIRST_POS]) ||
        (bmp_header[headers::F_B_SECOND_POS] != headers::FORMAT_BYTES[headers::F_B_SECOND_POS])) {
        throw std::invalid_argument("File " + filepath_ + " is not a BMP file");
    }

    try {
        unsigned char dib_header[headers::DIB_HEADER_SIZE];

        img_file.read(reinterpret_cast<char*>(dib_header), headers::DIB_HEADER_SIZE);
        size_t width = BytesToNumber(dib_header + headers::WIDTH_POSITION);
        size_t height = BytesToNumber(dib_header + headers::HEIGHT_POSITION);

        Image image(width, height);

        PixelMatrix image_data(height, std::vector<Color>(width));
        std::vector<Color> tmp_row(width);

        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                unsigned char pix[headers::BYTES_PER_PIXEL];

                img_file.read(reinterpret_cast<char*>(pix), headers::BYTES_PER_PIXEL);

                image_data[height - i - 1][j] = Color(pix[2], pix[1], pix[0]);
            }
            const int padding = reading_and_writing::GetPaddingSize(width);
            img_file.ignore(padding);
        }

        image = Image(image_data);

        img_file.close();

        return image;

    } catch (std::exception& e) {
        throw std::invalid_argument("Error reading file " + filepath_ + ": " + static_cast<std::string>(e.what()));
    }
}

const int reading_and_writing::GetPaddingSize(const size_t& width) {
    return static_cast<const int>(
        (4 -
         (static_cast<uint32_t>(width) * static_cast<uint32_t>(headers::BYTES_PER_PIXEL)) % headers::WIDTH_POSITION) %
        headers::WIDTH_POSITION);
}

size_t reading::Reader::BytesToNumber(unsigned char* bytes) {
    size_t number = *bytes;
    for (size_t i = 0; i < headers::SHIFT_BYTES.size(); ++i) {
        number += *(bytes + i + 1) << headers::SHIFT_BYTES[i];
    }
    return number;
}

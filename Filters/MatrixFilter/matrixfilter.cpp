#include "matrixfilter.h"

void matrixfilter::MatrixFilter::ApplyFilter(Image& image, std::vector<std::string>& arguments) {

    PixelMatrix new_pixel_matrix(image.GetHeight(), std::vector<Color>(image.GetWidth(), {0, 0, 0}));

    int matrix[MATRIX_COUNT_ELEMENTS];

    for (int i = 0; i < MATRIX_COUNT_ELEMENTS; ++i) {
        matrix[i] = std::stoi(arguments[i]);
    }

    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {

            int new_red = 0;
            int new_green = 0;
            int new_blue = 0;

            for (int delta_y = -1; delta_y <= 1; ++delta_y) {
                for (int delta_x = -1; delta_x <= 1; ++delta_x) {
                    size_t matrix_indice = static_cast<size_t>((delta_x + 1) + (delta_y + 1) * 3);
                    new_red += image.GetStraightPixel(x + delta_x, y + delta_y).red * matrix[matrix_indice];
                    new_green += image.GetStraightPixel(x + delta_x, y + delta_y).green * matrix[matrix_indice];
                    new_blue += image.GetStraightPixel(x + delta_x, y + delta_y).blue * matrix[matrix_indice];
                }
            }

            new_red = std::min(static_cast<int>(COUNTED_COLOURS_AMOUNT), std::max(0, new_red));
            new_green = std::min(static_cast<int>(COUNTED_COLOURS_AMOUNT), std::max(0, new_green));
            new_blue = std::min(static_cast<int>(COUNTED_COLOURS_AMOUNT), std::max(0, new_blue));

            Color new_pixel = {static_cast<uint8_t>(new_red), static_cast<uint8_t>(new_green),
                               static_cast<uint8_t>(new_blue)};
            new_pixel_matrix[y][x] = new_pixel;
        }
    }

    Image new_image(new_pixel_matrix);

    image.SetPixelMatrix(new_pixel_matrix);
    image.SetStraightData(new_image.GetStraightData());
}
#include "grayscale.h"

GrayScale::GrayScale() : BaseFilter() {
}

Color GrayScale::FilterSpecifier(size_t x, size_t y, Image& image) {
    Color color = image.GetStraightPixel(static_cast<int32_t>(x), static_cast<int32_t>(y));
    uint8_t new_color = static_cast<uint8_t>(static_cast<float>(color.red) * filters::GS_RED +
                                             static_cast<float>(color.green) * filters::GS_GREEN +
                                             static_cast<float>(color.blue) * filters::GS_BLUE);
    return {new_color, new_color, new_color};
}

void GrayScale::ApplyFilter(Image& image, std::vector<std::string>& arguments) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Color new_color = FilterSpecifier(j, i, image);
            image.SetStraightPixel(static_cast<int32_t>(j), static_cast<int32_t>(i), new_color);
            image.SetPixel(static_cast<int32_t>(j), static_cast<int32_t>(i), new_color);
        }
    }
}
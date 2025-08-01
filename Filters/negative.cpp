#include "negative.h"

NegativeFilter::NegativeFilter() : BaseFilter() {
}

Color NegativeFilter::FilterSpecifier(size_t x, size_t y, Image &image) {
    Color color = image.GetStraightPixel(static_cast<int32_t>(x), static_cast<int32_t>(y));
    return {static_cast<uint8_t>(filters::FILTER_WHITE - color.red),
            static_cast<uint8_t>(filters::FILTER_WHITE - color.green),
            static_cast<uint8_t>(filters::FILTER_WHITE - color.blue)};
}

void NegativeFilter::ApplyFilter(Image &image, std::vector<std::string> &arguments) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Color new_color = FilterSpecifier(j, i, image);
            image.SetStraightPixel(static_cast<int32_t>(j), static_cast<int32_t>(i), new_color);
            image.SetPixel(static_cast<int32_t>(j), static_cast<int32_t>(i), new_color);
        }
    }
}

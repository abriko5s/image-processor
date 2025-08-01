#include "sepia.h"

SepiaFilter::SepiaFilter() : BaseFilter() {
}

Color SepiaFilter::FilterSpecifier(size_t x, size_t y, Image& image) {

    Color color = image.GetStraightPixel(static_cast<int32_t>(x), static_cast<int32_t>(y));

    uint8_t new_red = static_cast<uint8_t>(std::clamp(static_cast<float>(color.red) * filters::SEP_RED_RED +
                                                          static_cast<float>(color.green) * filters::SEP_RED_GREEN +
                                                          static_cast<float>(color.blue) * filters::SEP_RED_BLUE,
                                                      0.0f, filters::FLOAT_WHITE));
    uint8_t new_green = static_cast<uint8_t>(std::clamp(static_cast<float>(color.red) * filters::SEP_GREEN_RED +
                                                            static_cast<float>(color.green) * filters::SEP_GREEN_GREEN +
                                                            static_cast<float>(color.blue) * filters::SEP_GREEN_BLUE,
                                                        0.0f, filters::FLOAT_WHITE));
    uint8_t new_blue = static_cast<uint8_t>(std::clamp(static_cast<float>(color.red) * filters::SEP_BLUE_RED +
                                                           static_cast<float>(color.green) * filters::SEP_BLUE_GREEN +
                                                           static_cast<float>(color.blue) * filters::SEP_BLUE_BLUE,
                                                       0.0f, filters::FLOAT_WHITE));

    return {new_red, new_green, new_blue};
}

void SepiaFilter::ApplyFilter(Image& image, std::vector<std::string>& arguments) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Color new_color = FilterSpecifier(j, i, image);
            image.SetStraightPixel(static_cast<int32_t>(j), static_cast<int32_t>(i), new_color);
            image.SetPixel(static_cast<int32_t>(j), static_cast<int32_t>(i), new_color);
        }
    }
}

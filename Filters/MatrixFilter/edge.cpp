#include "edge.h"

#include "../grayscale.h"

EdgeFilter::EdgeFilter(const float threshold) {
    threshold_ = threshold;
}

float EdgeFilter::GetThreshold() const {
    return threshold_;
}

Color EdgeFilter::FilterSpecifier(size_t x, size_t y, Image& image, const float threshold) {
    Color color = image.GetStraightPixel(static_cast<int32_t>(x), static_cast<int32_t>(y));

    uint8_t comparable_threshold = static_cast<uint8_t>(std::round(threshold * filters::FILTER_WHITE));

    if (color.red < comparable_threshold || color.green < comparable_threshold || color.blue < comparable_threshold) {
        return {colors::BLACK, colors::BLACK, colors::BLACK};
    }
    return {colors::WHITE, colors::WHITE, colors::WHITE};
};

void EdgeFilter::ApplyFilter(Image& image, std::vector<std::string>& arguments) {

    GrayScale grayscale;
    grayscale.ApplyFilter(image, arguments);

    MatrixFilter::ApplyFilter(image, edge_data_matrix_);

    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Color new_color = FilterSpecifier(j, i, image, threshold_);
            image.SetStraightPixel(static_cast<int32_t>(j), static_cast<int32_t>(i), new_color);
            image.SetPixel(static_cast<int32_t>(j), static_cast<int32_t>(i), new_color);
        }
    }
}
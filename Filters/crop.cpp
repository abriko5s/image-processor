#include "crop.h"

CropFilter::CropFilter() : new_width_(0), new_height_(0) {
}

CropFilter::CropFilter(const size_t width, const size_t height) {
    new_width_ = width;
    new_height_ = height;
}

size_t CropFilter::GetHeight() const {
    return new_height_;
}

size_t CropFilter::GetWidth() const {
    return new_width_;
}

void CropFilter::ApplyFilter(Image& image, std::vector<std::string>& arguments) {

    size_t width_to_apply = std::min(image.GetWidth(), GetWidth());
    size_t height_to_apply = std::min(image.GetHeight(), GetHeight());

    PixelMatrix new_pixel_matrix(height_to_apply, std::vector<Color>(width_to_apply, {0, 0, 0}));

    for (size_t y = 0; y < height_to_apply; ++y) {
        for (size_t x = 0; x < width_to_apply; ++x) {
            new_pixel_matrix[y][x] = image.GetPixel(x, y);
        }
    }

    Image new_image(new_pixel_matrix);

    image.SetHeight(height_to_apply);
    image.SetWidth(width_to_apply);
    image.SetPixelMatrix(new_pixel_matrix);
    image.SetStraightData(new_image.GetStraightData());
}

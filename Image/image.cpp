#include "image.h"

Image::Image(size_t width, size_t height) {
    width_ = width;
    height_ = height;
    straight_data_ = std::vector<Color>(width_ * height_, Color(0, 0, 0));
    pixel_matrix_ = PixelMatrix(height_, std::vector<Color>(width_, Color(0, 0, 0)));
}

Image::Image(const Image& image) {
    width_ = image.width_;
    height_ = image.height_;
    straight_data_ = image.straight_data_;
    pixel_matrix_ = image.pixel_matrix_;
}

Image::Image(const PixelMatrix& pixel_matrix) {
    width_ = pixel_matrix[0].size();
    height_ = pixel_matrix.size();
    pixel_matrix_ = pixel_matrix;
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            straight_data_.push_back(pixel_matrix[i][j]);
        }
    }
}

size_t Image::GetWidth() const {
    return width_;
}

size_t Image::GetHeight() const {
    return height_;
}

const std::vector<Color>& Image::GetStraightData() const {
    return straight_data_;
}

const PixelMatrix& Image::GetPixelMatrix() const {
    return pixel_matrix_;
}

Color& Image::GetPixel(size_t x, size_t y) {
    return pixel_matrix_[y][x];
}

Color Image::GetStraightPixel(int32_t x, int32_t y) {
    return straight_data_[static_cast<size_t>(std::clamp(y, 0, static_cast<int32_t>(height_) - 1)) * width_ +
                          static_cast<size_t>(std::clamp(x, 0, static_cast<int32_t>(width_) - 1))];
}

const Color& Image::GetStraightPixel(int32_t x, int32_t y) const {
    return straight_data_[static_cast<size_t>(std::clamp(y, 0, static_cast<int32_t>(height_) - 1)) * width_ +
                          static_cast<size_t>(std::clamp(x, 0, static_cast<int32_t>(width_) - 1))];
}

void Image::SetWidth(size_t width) {
    width_ = width;
}

void Image::SetHeight(size_t height) {
    height_ = height;
}

void Image::SetPixel(size_t x, size_t y, const Color& color) {
    CheckHeightAndWidth(x, y);
    pixel_matrix_[y][x] = color;
}

void Image::SetStraightPixel(int32_t x, int32_t y, const Color& color) {
    straight_data_[static_cast<size_t>(std::clamp(static_cast<int>(y), 0, static_cast<int>(height_) - 1)) * width_ +
                   static_cast<size_t>(std::clamp(static_cast<int>(x), 0, static_cast<int>(width_) - 1))] = color;
}

void Image::SetStraightData(const std::vector<Color>& straight_data) {
    straight_data_ = straight_data;
}

void Image::SetPixelMatrix(const PixelMatrix& pixel_matrix) {
    pixel_matrix_ = pixel_matrix;
}

void Image::CheckHeightAndWidth(const size_t width, const size_t height) const {
    if (width >= width_ || height >= height_) {
        throw std::out_of_range("Coordinates out of range");
    }
}
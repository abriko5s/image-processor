#pragma once

#include "../Libraries.h"
#include "color.h"

using PixelMatrix = std::vector<std::vector<Color>>;

class Image {
public:
    Image() = default;
    Image(size_t width, size_t height);
    Image(const Image& image);

    explicit Image(const PixelMatrix& data);

    ~Image() = default;

    size_t GetWidth() const;
    size_t GetHeight() const;
    const std::vector<Color>& GetStraightData() const;
    const PixelMatrix& GetPixelMatrix() const;

    Color& GetPixel(size_t x, size_t y);
    Color GetStraightPixel(int32_t x, int32_t y);               // int32_t for correct clamping!
    const Color& GetStraightPixel(int32_t x, int32_t y) const;  // int32_t for correct clamping!

    void SetPixel(size_t x, size_t y, const Color& color);
    void SetStraightPixel(int32_t x, int32_t y, const Color& color);  // int32_t for correct clamping!

    void SetPixelMatrix(const PixelMatrix& pixel_matrix);
    void SetStraightData(const std::vector<Color>& straight_data);
    void SetWidth(size_t width);
    void SetHeight(size_t height);

private:
    size_t width_ = 0;
    size_t height_ = 0;
    std::vector<Color> straight_data_;
    PixelMatrix pixel_matrix_;

    void CheckHeightAndWidth(const size_t width, const size_t height) const;
};

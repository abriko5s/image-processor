#pragma once

#include "basicfilter.h"

class CropFilter final : public BaseFilter {
public:
    CropFilter();
    CropFilter(size_t width, size_t height);

    size_t GetHeight() const;
    size_t GetWidth() const;

    void ApplyFilter(Image& image, std::vector<std::string>& arguments) override;

private:
    size_t new_width_;
    size_t new_height_;
};

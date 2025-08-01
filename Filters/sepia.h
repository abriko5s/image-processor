#pragma once

#include "basicfilter.h"

class SepiaFilter final : public BaseFilter {
public:
    SepiaFilter();
    void ApplyFilter(Image& image, std::vector<std::string>& arguments) override;

private:
    static Color FilterSpecifier(size_t x, size_t y, Image& image);
};
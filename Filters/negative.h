#pragma once

#include "basicfilter.h"

class NegativeFilter final : public BaseFilter {
public:
    NegativeFilter();
    void ApplyFilter(Image& image, std::vector<std::string>& arguments) override;

private:
    static Color FilterSpecifier(size_t x, size_t y, Image& image);
};
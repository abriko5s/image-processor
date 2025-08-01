#pragma once

#include "../basicfilter.h"

namespace matrixfilter {
class MatrixFilter : virtual public BaseFilter {
public:
    void ApplyFilter(Image& image, std::vector<std::string>& arguments) override;
};

const int MATRIX_COUNT_ELEMENTS = 9;
const size_t COUNTED_COLOURS_AMOUNT = 255;

}  // namespace matrixfilter
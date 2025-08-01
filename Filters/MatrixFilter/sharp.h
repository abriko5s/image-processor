#pragma once

#include "matrixfilter.h"

class SharpFilter final : public matrixfilter::MatrixFilter {
public:
    void ApplyFilter(Image& image, std::vector<std::string>& arguments) override;

private:
    std::vector<std::string> sharp_data_matrix_ = {"0", "-1", "0", "-1", "5", "-1", "0", "-1", "0"};
};

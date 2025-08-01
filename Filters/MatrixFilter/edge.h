#pragma once

#include "matrixfilter.h"

class EdgeFilter final : public matrixfilter::MatrixFilter {
public:
    explicit EdgeFilter(float threshold);
    void ApplyFilter(Image& image, std::vector<std::string>& arguments) override;
    float GetThreshold() const;

private:
    std::vector<std::string> edge_data_matrix_ = {"0", "-1", "0", "-1", "4", "-1", "0", "-1", "0"};

    float threshold_ = 0.f;

    static Color FilterSpecifier(size_t x, size_t y, Image& image, const float threshold);
};

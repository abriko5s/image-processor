#pragma once
#include "basicfilter.h"

class GaussianBlurFilter final : public BaseFilter {
public:
    explicit GaussianBlurFilter(float sigma);
    void ApplyFilter(Image &image, std::vector<std::string> &arguments) override;

private:
    float sigma_;
    static std::vector<int> BoxesForGauss(float sigma, double number);
    static void BoxBlur(std::vector<Color> &source, std::vector<Color> &target, size_t width, size_t height,
                        float sigma);
    static void BoxBlurH(std::vector<Color> &source, std::vector<Color> &target, size_t width, size_t height,
                         float sigma);
    static void BoxBlurT(std::vector<Color> &source, std::vector<Color> &target, size_t width, size_t height,
                         float sigma);
};
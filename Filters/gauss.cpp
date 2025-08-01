#include "gauss.h"

GaussianBlurFilter::GaussianBlurFilter(float sigma) : sigma_(sigma) {
}

std::vector<int> GaussianBlurFilter::BoxesForGauss(float sigma, double number) {

    sigma = sigma * filters::NORMING_MULTIPLYER;

    double width_ideal = std::sqrt(filters::NORMING * sigma * sigma / number + 1);
    int width_lower = std::floor(width_ideal);
    if (width_lower % 2 == 0) {
        --width_lower;
    }
    int width_upper = width_lower + 2;
    double m_ideal = (filters::NORMING * sigma * sigma - number * width_lower * width_lower - 4 * number * width_lower -
                      3 * number) /
                     (-4 * width_lower - 4);
    int m = static_cast<int>(std::round(m_ideal));
    std::vector<int> sizes(static_cast<std::vector<int>::size_type>(number));
    std::fill(sizes.begin(), sizes.begin() + m, width_lower);
    std::fill(sizes.begin() + m, sizes.end(), width_upper);
    return sizes;
}

void GaussianBlurFilter::BoxBlur(std::vector<Color>& source, std::vector<Color>& target, size_t width, size_t height,
                                 float sigma) {
    BoxBlurH(source, target, width, height, sigma);
    BoxBlurT(source, target, width, height, sigma);
}

void GaussianBlurFilter::BoxBlurH(std::vector<Color>& source, std::vector<Color>& target, size_t width, size_t height,
                                  float sigma) {
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            float new_red = 0;
            float new_green = 0;
            float new_blue = 0;
            for (int x = static_cast<int>(static_cast<float>(j) - sigma);
                 x <= static_cast<int>(static_cast<float>(j) + sigma); ++x) {
                const int min_x = std::clamp(x, 0, static_cast<int>(width) - 1);
                new_red += static_cast<float>(source[width * i + min_x].red);
                new_green += static_cast<float>(source[width * i + min_x].green);
                new_blue += static_cast<float>(source[width * i + min_x].blue);
            }
            target[i * width + j] = Color(static_cast<uint8_t>(new_red / (2 * sigma + 1)),
                                          static_cast<uint8_t>(new_green / (2 * sigma + 1)),
                                          static_cast<uint8_t>(new_blue / (2 * sigma + 1)));
        }
    }
}

void GaussianBlurFilter::BoxBlurT(std::vector<Color>& source, std::vector<Color>& target, size_t width, size_t height,
                                  float sigma) {
    for (size_t j = 0; j < width; ++j) {
        for (size_t i = 0; i < width; ++i) {
            float new_red = 0;
            float new_green = 0;
            float new_blue = 0;
            for (int y = static_cast<int>(static_cast<float>(j) - sigma);
                 y <= static_cast<int>(static_cast<float>(j) + sigma); ++y) {
                const int min_y = std::clamp(y, 0, static_cast<int>(height) - 1);
                new_red += static_cast<float>(source[min_y * width + i].red);
                new_green += static_cast<float>(source[min_y * width + i].green);
                new_blue += static_cast<float>(source[min_y * width + i].blue);
            }
            target[i * width + j] = Color(static_cast<uint8_t>(new_red / (2 * sigma + 1)),
                                          static_cast<uint8_t>(new_green / (2 * sigma + 1)),
                                          static_cast<uint8_t>(new_blue / (2 * sigma + 1)));
        }
    }
}

void GaussianBlurFilter::ApplyFilter(Image& image, std::vector<std::string>& arguments) {
    const size_t width = image.GetWidth();
    const size_t height = image.GetHeight();

    std::vector<Color> lined_data = image.GetStraightData();

    std::vector<Color> buffer1 = lined_data;
    std::vector<Color> buffer2(width * height);

    std::vector<int> boxes = BoxesForGauss(sigma_, 3);

    BoxBlur(buffer1, buffer2, image.GetWidth(), image.GetHeight(), static_cast<float>((boxes[0] - 1) / 2));
    BoxBlur(buffer2, buffer1, image.GetWidth(), image.GetHeight(), static_cast<float>((boxes[1] - 1) / 2));
    BoxBlur(buffer1, buffer2, image.GetWidth(), image.GetHeight(), static_cast<float>((boxes[2] - 1) / 2));

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            image.SetPixel(static_cast<int32_t>(y), static_cast<int32_t>(x), buffer2[y * width + x]);
        }
    }

    Image new_image(image.GetPixelMatrix());

    std::vector<Color> new_straight_data = new_image.GetStraightData();
    image.SetStraightData(new_straight_data);
}
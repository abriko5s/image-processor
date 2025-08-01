#pragma once

#include "../Image/image.h"

class BaseFilter {
public:
    BaseFilter() = default;
    virtual void ApplyFilter(Image& image, std::vector<std::string>& arguments) = 0;
    virtual ~BaseFilter() = default;
};

namespace filters {
const uint8_t FILTER_BLACK = 0;
const uint8_t FILTER_WHITE = 255;

const float GS_RED = 0.299;
const float GS_GREEN = 0.587;
const float GS_BLUE = 0.114;

const float SEP_RED_RED = 0.393;
const float SEP_RED_GREEN = 0.769;
const float SEP_RED_BLUE = 0.189;

const float SEP_GREEN_RED = 0.349;
const float SEP_GREEN_GREEN = 0.686;
const float SEP_GREEN_BLUE = 0.168;

const float SEP_BLUE_RED = 0.272;
const float SEP_BLUE_GREEN = 0.534;
const float SEP_BLUE_BLUE = 0.131;

const int NORMING = 12;
const float NORMING_DENUMERATOR = 2.0f;
const float NORMING_MULTIPLYER = static_cast<float>(4) / static_cast<float>(3);
const float FLOAT_WHITE = 255.0f;
}  // namespace filters
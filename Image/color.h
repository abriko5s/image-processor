#pragma once

#include "../Libraries.h"

struct Color {
    Color() = default;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    Color(uint8_t red, uint8_t green, uint8_t blue);

    void SetValue(uint8_t red, uint8_t green, uint8_t blue);

    bool operator==(const Color& other) const;
};

namespace colors {
const uint8_t WHITE = 255;
const uint8_t BLACK = 0;
}  // namespace colors

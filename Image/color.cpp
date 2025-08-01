#include "color.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {
}

void Color::SetValue(uint8_t input_red, uint8_t input_green, uint8_t input_blue) {
    red = input_red;
    green = input_green;
    blue = input_blue;
}

bool Color::operator==(const Color &other) const {
    return std::tie(red, green, blue) == std::tie(other.red, other.green, other.blue);
}

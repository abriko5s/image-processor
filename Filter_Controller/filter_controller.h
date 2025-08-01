#pragma once

#include "../Filters/basicfilter.h"
#include "../Parsing/parser.h"

class FilterController {
public:
    FilterController();

    static void FilterConveyor(Image& image, const std::vector<parsing::Argument>& arguments);
};
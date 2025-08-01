#pragma once

#include "../Libraries.h"

namespace parsing {

struct Argument {
    std::string name;
    std::vector<std::string> parameters;

    void ClearArgument();
    bool IsEmpty() const;
};

class Parser {
public:
    Parser() = default;
    ~Parser() = default;

    static std::vector<Argument> ParseArguments(int argc, char *argv[]);
};
}  // namespace parsing

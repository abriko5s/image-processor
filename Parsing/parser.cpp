#include "parser.h"

std::vector<parsing::Argument> parsing::Parser::ParseArguments(int argc, char* argv[]) {

    std::vector<Argument> arguments;
    Argument tmp;

    for (size_t i = 1; i < static_cast<size_t>(argc); ++i) {
        std::string arg = argv[i];

        if (argc <= 2) {
            tmp.name = arg;
            arguments.push_back(tmp);
            tmp.ClearArgument();
        } else {
            if (arg.front() == '-') {
                if (!tmp.IsEmpty()) {
                    arguments.push_back(tmp);
                    tmp.ClearArgument();
                }
                tmp.name = arg;
            } else {
                tmp.parameters.push_back(arg);
            }
        }
    }
    if (!tmp.IsEmpty()) {
        arguments.push_back(tmp);
    }
    return arguments;
}

void parsing::Argument::ClearArgument() {
    name.clear();
    parameters.clear();
}

bool parsing::Argument::IsEmpty() const {
    return name.empty() && parameters.empty();
}

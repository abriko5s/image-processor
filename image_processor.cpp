#include "Libraries.h"

#include "Filter_Controller/filter_controller.h"
#include "Reading_And_Writing/reader_and_writer.h"
#include "Parsing/parser.h"

int main(int argc, char** argv) {

    parsing::Parser parser;
    std::vector<parsing::Argument> arguments = parser.ParseArguments(argc, argv);

    std::string input_file = arguments[0].parameters[0];
    std::string output_file = arguments[0].parameters[1];

    reading::Reader reader;
    Image image = reader.ReadFile(input_file);

    FilterController controller;
    controller.FilterConveyor(image, arguments);

    writing::Writer writer;
    writer.WriteFile(image, output_file);

    return 0;
}
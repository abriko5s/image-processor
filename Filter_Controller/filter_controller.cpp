#include "filter_controller.h"

#include "../Filters/crop.h"
#include "../Filters/gauss.h"
#include "../Filters/grayscale.h"
#include "../Filters/negative.h"
#include "../Filters/MatrixFilter/edge.h"
#include "../Filters/MatrixFilter/sharp.h"
#include "../Filters/sepia.h"

FilterController::FilterController() {
}

void FilterController::FilterConveyor(Image& image, const std::vector<parsing::Argument>& arguments) {
    for (size_t i = 1; i < arguments.size(); ++i) {
        parsing::Argument current_argument = arguments[i];
        std::string current_filter = current_argument.name;
        std::vector<std::string> current_parameters = current_argument.parameters;

        // trying grayscale
        if (current_argument.name == "-gs") {
            if (!current_argument.parameters.empty()) {
                throw std::invalid_argument("Grayscale filter does not support any parameters");
            }
            try {
                GrayScale grayscale;
                grayscale.ApplyFilter(image, current_parameters);

            } catch (std::exception& e) {
                throw std::invalid_argument("Reading Arguments Error: " + static_cast<std::string>(e.what()));
            }
        }

        // trying negative
        if (current_argument.name == "-neg") {
            if (!current_argument.parameters.empty()) {
                throw std::invalid_argument("Negative filter does not support any parameters");
            }
            try {
                NegativeFilter negative;
                negative.ApplyFilter(image, current_parameters);

            } catch (std::exception& e) {
                throw std::invalid_argument("Reading Arguments Error: " + static_cast<std::string>(e.what()));
            }
        }

        // trying crop
        if (current_argument.name == "-crop") {
            if (current_argument.parameters.size() != 2) {
                throw std::invalid_argument("Crop filter needs only 2 parameters: width and height");
            }
            try {
                size_t width = static_cast<size_t>(std::stoi(current_argument.parameters[0]));
                size_t height = static_cast<size_t>(std::stoi(current_argument.parameters[1]));

                CropFilter crop(width, height);
                crop.ApplyFilter(image, current_parameters);

            } catch (std::exception& e) {
                throw std::invalid_argument(
                    "Reading Arguments Error: parameters width and height must both be non-negative int " +
                    static_cast<std::string>(e.what()));
            }
        }
        // trying sharp
        if (current_argument.name == "-sharp") {
            if (!current_argument.parameters.empty()) {
                throw std::invalid_argument("Sharp filter does not support any parameters");
            }
            try {
                SharpFilter sharp;
                sharp.ApplyFilter(image, current_parameters);

            } catch (std::exception& e) {
                throw std::invalid_argument("Filter Applying Error" + static_cast<std::string>(e.what()));
            }
        }

        // trying edge
        if (current_argument.name == "-edge") {
            if (current_argument.parameters.size() != 1) {
                throw std::invalid_argument("Edge filter needs only one parameter: threshold (float from 0 to 1)");
            }
            try {
                EdgeFilter edge(std::stof(current_argument.parameters.front()));
                edge.ApplyFilter(image, current_parameters);

            } catch (std::exception& e) {
                throw std::invalid_argument("Reading Arguments Error: threshold parameter's type must be float " +
                                            static_cast<std::string>(e.what()));
            }
        }

        // trying gaussian blur
        if (current_argument.name == "-blur") {
            if (current_argument.parameters.size() != 1) {
                throw std::invalid_argument("Blur filter needs only one parameter: non-negative float");
            }

            try {
                GaussianBlurFilter gaussian_blur(std::stof(current_parameters.front()));
                gaussian_blur.ApplyFilter(image, current_parameters);

            } catch (std::exception& e) {
                throw std::invalid_argument("Reading Arguments Error: non-negative float" +
                                            static_cast<std::string>(e.what()));
            }
        }

        // trying sepia
        if (current_argument.name == "-sepia") {
            if (!current_argument.parameters.empty()) {
                throw std::invalid_argument("Sepia filter does not support any parameters");
            }
            try {
                SepiaFilter sepia;
                sepia.ApplyFilter(image, current_parameters);

            } catch (std::exception& e) {
                throw std::invalid_argument("Reading Arguments Error: non-negative float" +
                                            static_cast<std::string>(e.what()));
            }
        }
    }
}
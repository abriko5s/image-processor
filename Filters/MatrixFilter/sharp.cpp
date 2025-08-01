#include "sharp.h"

void SharpFilter::ApplyFilter(Image& image, std::vector<std::string>& arguments) {

    MatrixFilter::ApplyFilter(image, sharp_data_matrix_);
}

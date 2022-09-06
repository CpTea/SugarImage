#include "DHashMeasuableObject.h"
#include "hash/Hash.h"

std::string
sugar::image::similarity::hash::DHashMeasuableObject::getFeatureFrom_(
    const std::string& filePath) {
    constexpr size_t width = 9, height = 8;
    auto image =
        detail::asType<double>(detail::getImageFrom<width, height>(filePath));

    char feature[(width - 1) * height + 1] = {0};
    for (size_t i = 0; i < height; ++i) {
        size_t ridx = i * height;
        for (size_t j = 0; j < width - 1; ++j) {
            feature[ridx + j] =
                image.at<double>(i, j) > image.at<double>(i, j + 1) ? '1' : '0';
        }
    }
    return feature;
}

double
sugar::image::similarity::hash::DHashMeasuableObject::differencesBetween_(
    const std::string& feature1,
    const std::string& feature2) {
    return detail::getHammingDistance(feature1, feature2);
}

bool sugar::image::similarity::hash::DHashMeasuableObject::IsHomogenous_(
    double distance) {
    return distance <= 5;
}

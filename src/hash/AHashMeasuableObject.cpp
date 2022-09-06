#include "AHashMeasuableObject.h"
#include "Hash.h"

std::string
sugar::image::similarity::hash::AHashMeasuableObject::getFeatureFrom_(
    const std::string& filePath) {
    auto image = detail::getImageFrom<8, 8>(filePath);
    double mean = detail::getMeanFrom<double>(image);
    return detail::elementCompare<64>(detail::flatten<double>(image), mean);
}

double
sugar::image::similarity::hash::AHashMeasuableObject::differencesBetween_(
    const std::string& feature1,
    const std::string& feature2) {
    return detail::getHammingDistance<64>(feature1, feature2);
}

bool sugar::image::similarity::hash::AHashMeasuableObject::IsHomogenous_(
    double distance) {
    return distance <= 5;
}

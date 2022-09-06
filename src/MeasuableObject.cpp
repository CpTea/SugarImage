#include "MeasuableObject.h"

#include <filesystem>

std::string sugar::image::similarity::MeasuableObject::getFeatureFrom(
    const std::string& filePath) {
    return std::filesystem::exists(filePath) ? getFeatureFrom_(filePath)
                                             : std::string();
}

double sugar::image::similarity::MeasuableObject::differencesBetween(
    const std::string& feature1,
    const std::string& feature2) {
    return !feature1.empty() && !feature2.empty()
               ? differencesBetween_(feature1, feature2)
               : -1;
}

bool sugar::image::similarity::MeasuableObject::IsHomogenous(double distance) {
    return distance >= 0 && IsHomogenous_(distance);
}

sugar::image::similarity::MeasuableObject::~MeasuableObject() {}

#include "MD5MeasuableObject.h"
#include <fstream>
#include "MD5.h"

std::string sugar::image::similarity::hash::MD5MeasuableObject::getFeatureFrom_(
    const std::string& filePath) {
    std::ifstream in(filePath, std::ios::binary);
    return MD5(in).value();
}

double sugar::image::similarity::hash::MD5MeasuableObject::differencesBetween_(
    const std::string& feature1,
    const std::string& feature2) {
    return feature1 == feature2 ? 0 : -1;
}

bool sugar::image::similarity::hash::MD5MeasuableObject::IsHomogenous_(
    double distance) {
    return !distance;
}
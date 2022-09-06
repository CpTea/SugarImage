#include "PHashMeasuableObject.h"
#include "Hash.h"

std::string
sugar::image::similarity::hash::PHashMeasuableObject::getFeatureFrom_(
    const std::string& filePath) {
    auto image = detail::asType<double>(detail::getImageFrom<32, 32>(filePath));
    cv::Mat dst;
    cv::dct(image, dst);
    auto pixels = detail::flatten<double>(dst);
    std::vector<double> tmp = pixels;
    std::sort(tmp.begin(), tmp.end());
    double median = detail::getMedianFrom(pixels);
    return detail::elementCompare<64>(pixels, median);
}

double
sugar::image::similarity::hash::PHashMeasuableObject::differencesBetween_(
    const std::string& feature1,
    const std::string& feature2) {
    return detail::getHammingDistance<64>(feature1, feature2);
}

bool sugar::image::similarity::hash::PHashMeasuableObject::IsHomogenous_(
    double distance) {
    return distance <= 5;
}

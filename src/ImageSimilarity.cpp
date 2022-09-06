#include "SugarImage.h"
#include "creator/MeasuableObjectCreator.h"

sugar::image::similarity::MeasurementResult
sugar::image::similarity::SimilarityOperations::measure(
    const std::string& path1,
    const std::string& path2,
    MeasurementMode mode) {
    return measure(path1, path2, (unsigned)mode);
}

sugar::image::similarity::MeasurementResult
sugar::image::similarity::SimilarityOperations::measure(
    const std::string& path1,
    const std::string& path2,
    unsigned mode) {
    MeasurementResult result;
    auto measuableObj = detail::creators::getMeasuableObject(mode);
    result.feature1 = measuableObj->getFeatureFrom(path1);
    result.feature2 = measuableObj->getFeatureFrom(path2);
    result.dissimilarity =
        measuableObj->differencesBetween(result.feature1, result.feature2);
    result.homogeneity = measuableObj->IsHomogenous(result.dissimilarity);
    return result;
}

sugar::image::similarity::capi::MeasurementResult
sugar::image::similarity::capi::similarityMeasure(const char* path1,
                                                  const char* path2,
                                                  unsigned mode) {
    auto result = SimilarityOperations::measure(path1, path2, mode);
    capi::MeasurementResult cresult;
    cresult.dissimilarity = result.dissimilarity;
    cresult.homogeneity = result.homogeneity;
    strcpy(cresult.feature1, result.feature1.c_str());
    strcpy(cresult.feature2, result.feature2.c_str());
    return cresult;
}

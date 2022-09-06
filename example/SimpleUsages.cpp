#include <filesystem>
#include <iostream>
#include "SugarImage.h"

using namespace std;
using namespace sugar::image::similarity;

void printResult(const MeasurementResult& r) {
    cout << "Homogeneity: " << boolalpha << r.homogeneity << endl;
    cout << "Dissimilarity: " << r.dissimilarity << endl;
    cout << "Feature1: " << r.feature1 << endl;
    cout << "Feature2: " << r.feature2 << endl;
}

void printCResult(const capi::MeasurementResult& r) {
    cout << "Homogeneity: " << boolalpha << r.homogeneity << endl;
    cout << "Dissimilarity: " << r.dissimilarity << endl;
    cout << "Feature1: " << r.feature1 << endl;
    cout << "Feature2: " << r.feature2 << endl;
}

int main(int argc, char* argv[]) {
    auto p1 = "../../../assets/img1.png";
    auto p2 = "../../../assets/img2.png";
    cout << "Path 1: " << filesystem::absolute(p1) << endl;
    cout << "Path 2: " << filesystem::absolute(p2) << endl;

    cout << ">>======= Print result with Cxx API =======<<" << endl;

    printResult(SimilarityOperations::measure(p1, p2, MeasurementMode::MD5));
    printResult(SimilarityOperations::measure(p1, p2, MeasurementMode::PHash));
    printResult(SimilarityOperations::measure(p1, p2, MeasurementMode::AHash));
    printResult(SimilarityOperations::measure(p1, p2, MeasurementMode::DHash));
    cout << ">>=========================================<<" << endl;
    cout << ">>======== Print result with C API ========<<" << endl;
    printCResult(capi::similarityMeasure(p1, p2, 0));
    printCResult(capi::similarityMeasure(p1, p2, 1));
    printCResult(capi::similarityMeasure(p1, p2, 2));
    printCResult(capi::similarityMeasure(p1, p2, 3));
     cout << ">>=========================================<<" << endl;
    return 0;
}

#ifndef SUGAR_MEASUABLE_OBJECT
#define SUGAR_MEASUABLE_OBJECT

#include <string>

namespace sugar::image::similarity {

    class MeasuableObject {
    public:
        virtual std::string getFeatureFrom(const std::string& filePath);
        virtual double differencesBetween(const std::string& feature1,
                                          const std::string& feature2);
        virtual bool IsHomogenous(double distance);
        virtual ~MeasuableObject();

    protected:
        virtual std::string getFeatureFrom_(const std::string& filePath) = 0;
        virtual double differencesBetween_(const std::string& feature1,
                                           const std::string& feature2) = 0;
        virtual bool IsHomogenous_(double distance) = 0;
    };

}

#endif

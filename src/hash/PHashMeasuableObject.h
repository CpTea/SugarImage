#ifndef SUGAR_PHASH_MEASUABLE_OBJECT
#define SUGAR_PHASH_MEASUABLE_OBJECT

#include "../MeasuableObject.h"

namespace sugar::image::similarity::hash {

    class PHashMeasuableObject : public MeasuableObject {
    protected:
        virtual std::string getFeatureFrom_(
            const std::string& filePath) override;
        virtual double differencesBetween_(
            const std::string& feature1,
            const std::string& feature2) override;
        virtual bool IsHomogenous_(double distance) override;
    };

}
#endif
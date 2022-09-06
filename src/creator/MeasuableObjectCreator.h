#ifndef SUGAR_MEASUABLE_OBJECT_CREATOR
#define SUGAR_MEASUABLE_OBJECT_CREATOR

#include <memory>
#include "SugarImage.h"
#include "hash/AHashMeasuableObject.h"
#include "hash/DHashMeasuableObject.h"
#include "hash/MD5MeasuableObject.h"
#include "hash/PHashMeasuableObject.h"

namespace sugar::image::similarity::detail::creators {

    std::shared_ptr<MeasuableObject> getMeasuableObject(unsigned mode) {
        switch (mode) {
            case constants::MEASUREMENT_MODE_MD5:
                return std::make_shared<hash::MD5MeasuableObject>(
                    hash::MD5MeasuableObject());
            case constants::MEASUREMENT_MODE_PHASH:
                return std::make_shared<hash::PHashMeasuableObject>(
                    hash::PHashMeasuableObject());
            case constants::MEASUREMENT_MODE_AHASH:
                return std::make_shared<hash::AHashMeasuableObject>(
                    hash::AHashMeasuableObject());
            case constants::MEASUREMENT_MODE_DHASH:
                return std::make_shared<hash::DHashMeasuableObject>(
                    hash::DHashMeasuableObject());
            default:
                return nullptr;
        }
    }

}

#endif

#ifndef SUGAR_IMAGE_SIMILARITY
#define SUGAR_IMAGE_SIMILARITY

#include <string>
#include "LibExport.h"

namespace sugar::image::similarity {

    namespace detail::constants {
        constexpr unsigned MAX_FEATURE_SIZE = 512;
        constexpr unsigned MEASUREMENT_MODE_MD5 = 0;
        constexpr unsigned MEASUREMENT_MODE_PHASH = 1;
        constexpr unsigned MEASUREMENT_MODE_AHASH = 2;
        constexpr unsigned MEASUREMENT_MODE_DHASH = 3;
    }

    /**
     * @brief Modes of similarity measurement.
     */
    enum class LIB_API MeasurementMode : unsigned {
        /**
         * @brief Message-Digest 5.
         */
        MD5 = detail::constants::MEASUREMENT_MODE_MD5,
        /**
         * @brief Perceptual Hash.
         */
        PHash = detail::constants::MEASUREMENT_MODE_PHASH,
        /**
         * @brief Average Hash.
         */
        AHash = detail::constants::MEASUREMENT_MODE_AHASH,
        /**
         * @brief Difference Hash.
         */
        DHash = detail::constants::MEASUREMENT_MODE_DHASH,
    };

    /**
     * @brief Save the result of the similarity measure.
     */
    struct LIB_API MeasurementResult {
        /**
         * @brief Whether the content of the given image is the same.
         */
        bool homogeneity;
        /**
         * @brief Differences in the features of the given images.
         */
        double dissimilarity;
        /**
         * @brief The feature of the first image.
         */
        std::string feature1;
        /**
         * @brief The feature of the second image.
         */
        std::string feature2;
    };

    /**
     * @brief The class of similarity measurement operations.
     */
    struct LIB_API SimilarityOperations {
        /**
         * @brief Measure the similarity of two given images.
         * @param path1 The file path of first image.
         * @param path2 The file path of second image.
         * @param mode The mode for similarity measurement.
         * @return The result of measurement.
         */
        static MeasurementResult measure(
            const std::string& path1,
            const std::string& path2,
            MeasurementMode mode = MeasurementMode::MD5);

        /**
         * @brief Measure the similarity of two given images.
         * @param path1 The file path of first image.
         * @param path2 The file path of second image.
         * @param mode The mode for similarity measurement.
         * @return The result of measurement.
         */
        static MeasurementResult measure(const std::string& path1,
                                         const std::string& path2,
                                         unsigned mode);
    };

    namespace capi {
        extern "C" {

        /**
         * @brief Save the result of the similarity measure.
         */
        struct LIB_API MeasurementResult {
            /**
             * @brief Whether the content of the given image is the same.
             */
            bool homogeneity;
            /**
             * @brief Differences in the features of the given images.
             */
            double dissimilarity;
            /**
             * @brief The feature of the first image.
             */
            char feature1[detail::constants::MAX_FEATURE_SIZE];
            /**
             * @brief The feature of the second image.
             */
            char feature2[detail::constants::MAX_FEATURE_SIZE];
        };

        /**
         * @brief Measure the similarity of two given images.
         * @param path1 The file path of first image.
         * @param path2 The file path of second image.
         * @param mode The mode for similarity measurement.
         * @return The result of measurement.
         */
        LIB_API capi::MeasurementResult similarityMeasure(const char* path1,
                                                          const char* path2,
                                                          unsigned mode);
        }
    }

}

#endif

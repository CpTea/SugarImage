#ifndef SUGAR_HASH
#define SUGAR_HASH

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace sugar::image::similarity::detail {
    template <size_t width = 8, size_t height = 8>
    cv::Mat getImageFrom(const std::string& filePath) {
        auto image = cv::imread(filePath, cv::ImreadModes::IMREAD_GRAYSCALE);
        cv::resize(image, image, {width, height});
        return image;
    }

    template <typename Value_t>
    std::vector<Value_t> flatten(const cv::Mat& input) {
        return input.reshape(1, 1);
    }

    template <size_t length = 64, typename T>
    std::string elementCompare(const std::vector<T> input, const T& value) {
        char feat[length + 1] = {0};
        for (int i = 0; i < length; ++i) {
            feat[i] = input[i] >= value ? '1' : '0';
        }
        return feat;
    }

    template <typename Value_t>
    Value_t getMedianFrom(const std::vector<Value_t>& input) {
        auto tmp = input;
        std::sort(tmp.begin(), tmp.end());
        return tmp[tmp.size() / 2];
    }

    template <typename Value_t>
    Value_t getMeanFrom(const cv::Mat& input) {
        cv::Scalar mean;
        mean = cv::mean(input);
        return mean[0];
    }

    template <typename Value_t>
    cv::Mat asType(const cv::Mat& input) {
        return cv::Mat_<Value_t>(input);
    }

    template <size_t length = 64>
    double getHammingDistance(const std::string& string1,
                              const std::string& string2) {
        if (string1.size() != string2.size() || string1.size() != length) {
            return -1;
        }

        int dist = 0;
        for (int i = 0; i < length; ++i) {
            if (string1[i] != string2[i]) {
                ++dist;
            }
        }
        return dist;
    }
}

#endif
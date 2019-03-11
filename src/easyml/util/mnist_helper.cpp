//
// File name: mnist_helper.cpp
// Created by ronny on 16-7-15.
//

#include <easyml/util/util.h>
#include <fstream>
#include <glog/logging.h>

namespace easyml {

namespace util {

//对应int32大小的成员
static int Transfer(int value)
{
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0xFF000000) >> 24) ;
}

static bool LoadImagesFormFile(const std::string &file, cv::Mat &data) {
    std::ifstream is(file);
    if (!is) {
        return false;
    }
    is.seekg(0, is.end);
    long length = is.tellg();
    is.seekg(0, is.beg);

    char *buffer = new char[length];
    is.read(buffer, length);

    int magic_number = Transfer(*reinterpret_cast<int*>(buffer));
    CHECK(2051 == magic_number) << "Error in reading the data." << std::endl;
    int number_of_images = Transfer(*reinterpret_cast<int*>(buffer + 4));
    int rows = Transfer(*reinterpret_cast<int*>(buffer + 8));
    int cols = Transfer(*reinterpret_cast<int*>(buffer + 12));

    data.create(number_of_images, rows * cols, CV_8U);
    for (int i = 0; i < number_of_images; i++) {
        cv::Mat image(rows, cols, CV_8UC1, buffer + 16 + i * rows * cols);
        image.reshape(0, 1).copyTo(data.row(i));
    }
    delete[] buffer;
    return true;
}

static bool LoadLabelsFormFile(const std::string &file, cv::Mat &label) {
    std::ifstream is(file);
    if (!is) {
        return false;
    }
    is.seekg(0, is.end);
    long length = is.tellg();
    is.seekg(0, is.beg);

    char *buffer = new char[length];
    is.read(buffer, length);

    int magic_number = Transfer(*reinterpret_cast<int*>(buffer));
    CHECK(2049 == magic_number) << "Error in reading the data." << std::endl;
    int number_of_label = Transfer(*reinterpret_cast<int*>(buffer + 4));
    label = cv::Mat(number_of_label, 1, CV_8U, buffer + 8);
    return true;
}

bool LoadMNIST(const std::string &prefix,
               cv::Mat &training_images,
               cv::Mat &train_labels,
               cv::Mat &testing_images,
               cv::Mat &test_labels) {
 cv::Mat training_labels;
    if (!LoadImagesFormFile(prefix + "/train-images-idx3-ubyte", training_images)) {
        LOG(ERROR) << "Failed to load training data." << std::endl;
        return false;
    }
    if (!LoadLabelsFormFile(prefix + "/train-labels-idx1-ubyte", training_labels)) {
        LOG(ERROR) << "Failed to load training labels." << std::endl;
        return false;
    }
    if (training_images.rows != training_labels.rows) {
        LOG(ERROR) << "the number of training data doesn't match with the label." << std::endl;
        return false;
    }
    train_labels = cv::Mat::zeros(training_labels.rows, 10, CV_8U);
    for (int i = 0; i < train_labels.rows; i++) {
        train_labels.at<uchar>(i, training_labels.at<uchar>(i,0)) = 1;
    }

    cv::Mat testing_labels;
    if (!LoadImagesFormFile(prefix + "/t10k-images-idx3-ubyte", testing_images)) {
        LOG(ERROR) << "Failed to load testing data." << std::endl;
        return false;
    }

    if (!LoadLabelsFormFile(prefix + "/t10k-labels-idx1-ubyte", testing_labels)) {
        LOG(ERROR) << "Failed to load testing labels." << std::endl;
        return false;
    }
    if (testing_images.rows != testing_labels.rows) {
        LOG(ERROR) << "the number of testing data doesn't match with the label." << std::endl;
        return false;
    }
    test_labels = cv::Mat::zeros(testing_labels.rows, 10, CV_8U);
    for (int i = 0; i < test_labels.rows; i++) {
        test_labels.at<uchar>(i, testing_labels.at<uchar>(i,0)) = 1;
    }
    return true;
}

} // namespace util

} // namespace easyml

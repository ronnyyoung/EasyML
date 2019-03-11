//
// File name: Util.cpp
// Created by ronny on 16-7-15.
//

#include <easyml/util/util.h>

namespace easyml {

namespace util {

void RandomShuffle(cv::Mat &train_data, cv::Mat &labels){
    cv::Mat training_temp = train_data.clone();
    cv::Mat labels_temp = labels.clone();
    cv::Mat index(1, train_data.rows, CV_32SC1);
    for (int i = 0; i < index.cols; i++) {
        index.at<int>(i) = i;
    }
    cv::randShuffle(index);
    for (int i = 0; i < index.cols; i++) {
        train_data.row(i) = training_temp.row(index.at<int>(i));
        labels.row(i) = labels_temp.row(index.at<int>(i));
    }
}

} // namepsace util
} // namespace easyml



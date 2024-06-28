#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./a_img.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define BIN_TH (100)

int main(int argc, const char * argv[]) {
    cv::Mat src_img, tmp_img, dst_img;
    src_img = cv::imread(FILE_NAME, 0);

    if (src_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    dst_img = src_img.clone();
    cv::threshold(dst_img, dst_img, BIN_TH, 255, cv::THRESH_BINARY);
    // tmp_img = dst_img.clone();
    cv::dilate(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 7);
    cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 7);
    cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 10);
    cv::dilate(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 10);

    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}

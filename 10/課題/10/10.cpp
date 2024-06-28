#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./issue1.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define BIN_TH (100)

int main(int argc, const char *argv[]){
    double L, S, R;
    cv::Mat src_img, tmp_img, tmp2_img, dst_img;
    std::vector<std::vector<cv::Point>> contours;
    cv::Scalar color[] = {CV_RGB(0, 255, 255), CV_RGB(255, 0, 255)};

    src_img = cv::imread(FILE_NAME);
    if (src_img.empty()){
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    dst_img = src_img.clone();
    tmp_img = src_img.clone();
    cv::cvtColor(tmp_img, tmp_img, cv::COLOR_BGR2GRAY);
    cv::threshold(tmp_img, tmp_img, BIN_TH, 255, cv::THRESH_BINARY);
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    for (int i = 0; i < contours.size(); i++){
        L = cv::arcLength(contours[i], true);
        S = cv::contourArea(contours[i]);
        R = (4*M_PI*S)/(L*L);
        if (R > 0.89){
            cv::drawContours(dst_img, contours, i, CV_RGB(0, 0, 0), 3);
            cv::drawContours(dst_img, contours, i, CV_RGB(0, 0, 0), cv::FILLED);
        }
    }

    tmp2_img = dst_img.clone();
    cv::cvtColor(tmp2_img, tmp2_img, cv::COLOR_BGR2GRAY);
    cv::threshold(tmp2_img, tmp2_img, BIN_TH, 255, cv::THRESH_BINARY);
    cv::dilate(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 18);
    cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 18);
    tmp_img = dst_img.clone();
    cv::cvtColor(tmp_img, tmp_img, cv::COLOR_BGR2GRAY);
    cv::threshold(tmp_img, tmp_img, BIN_TH, 255, cv::THRESH_BINARY);
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); i++) cv::drawContours(dst_img, contours, i, color[i], cv::FILLED);

    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            cv::Vec3b s = {0, 0, 0};
            if (tmp2_img.at<uchar>(y, x) < 10) dst_img.at<cv::Vec3b>(y, x) = s;
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}

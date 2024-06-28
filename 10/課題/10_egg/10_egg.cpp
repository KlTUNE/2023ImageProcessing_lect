#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./challenge.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define BIN_TH (200)

int main(int argc, const char *argv[]){
    double S;
    int count=0;
    cv::Mat src_img, dst_img;
    std::vector<std::vector<cv::Point>> contours;
    cv::Scalar color[] = {CV_RGB(0, 255, 255), CV_RGB(255, 0, 255)};

    src_img = cv::imread(FILE_NAME);
    if (src_img.empty()){
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    dst_img = src_img.clone();
    cv::cvtColor(dst_img, dst_img, cv::COLOR_BGR2GRAY);
    cv::threshold(dst_img, dst_img, BIN_TH, 255, cv::THRESH_BINARY);
    cv::findContours(dst_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    for (int i = 0; i < contours.size(); i++){
        S = cv::contourArea(contours[i]);
        if (S >= 50) count ++;
    }

    printf("%d個\n",count);
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}

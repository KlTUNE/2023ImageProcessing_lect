#include <iostream>
#include <opencv2/opencv.hpp>

// #define FILE_NAME "./sample.jpg"
#define FILE_NAME "./sample_rotate.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define BIN_TH 100

int main(int argc, const char * argv[]) {
    cv::Mat src_img = cv::imread(FILE_NAME);

    src_img = cv::imread(FILE_NAME);
    if (src_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    double L,S,R;
    cv::Mat dst_img = src_img.clone();
    std::vector< std::vector< cv::Point > > contours;

    cv::cvtColor(src_img, src_img,cv::COLOR_BGR2GRAY);
    cv::threshold(src_img,src_img,BIN_TH,255,cv::THRESH_BINARY);
    cv::findContours(src_img,contours,cv::RETR_LIST,cv::CHAIN_APPROX_NONE);

    for(int i=0;i<contours.size();i++){
        S = cv::contourArea(contours[i]);
        L = cv::arcLength(contours[i], true);
        R = (4*M_PI*S)/(L*L);

        if(S>=1740 && S<=10700 && (R>=0.65 || R<=0.6)) cv::drawContours(dst_img,contours,i,CV_RGB(255,0,0),-1);
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
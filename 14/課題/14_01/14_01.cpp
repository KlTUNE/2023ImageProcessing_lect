#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./gem2.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

cv::Mat remove_noize(cv::Mat img){
    cv::dilate(img, img, cv::Mat(), cv::Point(-1,-1), 15);
    cv::erode(img, img, cv::Mat(), cv::Point(-1,-1), 30);
    cv::dilate(img, img, cv::Mat(), cv::Point(-1,-1), 15);

    return img;
}

int main(int argc, const char * argv[]) {
    cv::Mat src_img, black_img, gold_img, green_img, tmp_img, dst_img;
    std::vector< std::vector< cv::Point > > contours;
    cv::Vec3b p,s;

    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) {
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    dst_img = src_img.clone();

    cv::cvtColor(src_img, black_img, cv::COLOR_BGR2GRAY);
    cv::threshold(black_img, black_img, 20, 255, cv::THRESH_BINARY_INV);
    black_img = remove_noize(black_img);
    cv::findContours(black_img, contours,cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    for (int i=0; i<contours.size(); i++) {
        cv::Rect bb;
        bb = cv::boundingRect(contours[i]);
        cv::rectangle(dst_img, bb, CV_RGB(255, 0, 0), 3);
    }
    printf("Black gem = %d\n", (int)contours.size());

    cv::cvtColor(src_img, tmp_img, cv::COLOR_BGR2HSV);
    gold_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            p = tmp_img.at<cv::Vec3b>(y, x);
            if(20<=p[0] && p[0]<=60 && 100<=p[1] && p[1]<=200) gold_img.at<uchar>(y, x) = 255;
        }
    }
    gold_img = remove_noize(gold_img);
    cv::findContours(gold_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    for (int i=0; i<contours.size(); i++) {
        float radius;
        cv::Point2f center;
        cv::minEnclosingCircle(contours[i], center, radius);
        cv::circle(dst_img, center, (int)radius, CV_RGB(255, 255, 255), 3);
    }
    printf ("Golden gem = %d\n", (int)contours.size());

    green_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            s = src_img.at<cv::Vec3b>(y, x);
            if(s[1]>=50 && s[1]<=100 && s[2]>=0 && s[2]<=50) green_img.at<uchar>(y,x) =  255;
        }
    }
    green_img = remove_noize(green_img);
    cv::findContours(green_img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    for (int i=0; i<contours.size(); i++) cv::drawContours(dst_img, contours, i, CV_RGB(0, 255, 0), -1);
    printf ("Green gem = %d\n", (int)contours.size());

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
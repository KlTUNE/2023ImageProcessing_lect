#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./fruit_image.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define HUE_MIN (34)
#define HUE_MAX (40)
#define SAT_MIN (90)
#define VAL_MIN (80)
#define VAL_MAX (230)

int main(int argc, const char *argv[])
{
    double S;
    cv::Vec3b p;
    std::vector<std::vector<cv::Point>> contours;
    cv::Mat src_img, dst_img, hsv_img, tmp_img;
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

    if (src_img.empty())
    {
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    // dst_img = src_img.clone();
    dst_img = cv::Mat(src_img.size(), CV_8UC3);
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

    for (int y = 0; y < src_img.rows; y++){
        for (int x = 0; x < src_img.cols; x++){
            p = hsv_img.at<cv::Vec3b>(y, x);
            if (p[0]>HUE_MIN && p[0]<HUE_MAX && p[1]>SAT_MIN && p[2]>VAL_MIN) dst_img.at<cv::Vec3b>(y, x) = {0, 255, 0};
        }
    }

    tmp_img = dst_img.clone();
    cv::cvtColor(tmp_img, tmp_img, cv::COLOR_BGR2GRAY);
    cv::threshold(tmp_img, tmp_img, 10, 255, cv::THRESH_BINARY);
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); i++){
        S = cv::contourArea(contours[i]);
        if (S < 1000){
            // cv::drawContours(dst_img, contours, i, CV_RGB(0, 0, 0), 3);
            cv::drawContours(dst_img, contours, i, CV_RGB(0, 0, 0), cv::FILLED);
        }
    }

    for (int y = 0; y < src_img.rows; y++){
        for (int x = 0; x < src_img.cols; x++){
            p = dst_img.at<cv::Vec3b>(y, x);
            if (p[1] < 100) dst_img.at<cv::Vec3b>(y, x) = src_img.at<cv::Vec3b>(y, x);
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}

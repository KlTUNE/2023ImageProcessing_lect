#include <iostream>
#include <opencv2/opencv.hpp>
#define TARGET_IMG_FILE "./gazoDora.jpg"
#define TEMPLATE_IMG_FILE "./red.jpg"
int main(int argc, const char *argv[]){
    cv::Mat src_img, template_img, compare_img, result_img;
    src_img = cv::imread(TARGET_IMG_FILE, 0);
    if (src_img.empty()) return (-1);
    template_img = cv::imread(TEMPLATE_IMG_FILE, 0);
    compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1, src_img.cols - template_img.cols + 1), CV_32F, 1);
    cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
    result_img = cv::Mat(compare_img.size(), CV_8UC1);
    for (int y = 0; y < compare_img.rows; y++) for (int x = 0; x < compare_img.cols; x++) result_img.at<uchar>(y, x) = compare_img.at<float>(y, x) * 255;
    cv::imshow("input", src_img);
    cv::imshow("template", template_img);
    cv::imshow("compare", result_img);
    cv::waitKey(0);
    return 0;}

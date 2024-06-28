#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./input1.jpg"
#define FILE_NAME2 "./input2.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define ALPHA (0.3)

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    cv::Mat src_img2 = cv::imread(FILE_NAME2, 0);

    if (src_img.empty() || src_img2.empty())
    {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    cv::Mat result_img = cv::Mat(src_img.size(), CV_8UC1);

    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            double s1 = (double)src_img.at<unsigned char>(y, x);
            double s2 = (double)src_img2.at<unsigned char>(y, x);
            int s_result = ALPHA * s1 + (1.0 - ALPHA) * s2;
            result_img.at<unsigned char>(y, x) = (unsigned char)s_result;
        }
    }

    // cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey();
    return 0;
}
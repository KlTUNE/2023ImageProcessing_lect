#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./apple_tree.jpg"
#define WINDOW_IN "input"
#define WINDOW_OUT "output"
#define WINDOW_GOUT "gray_output"

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME);
    cv::Mat gray_img = cv::Mat(src_img.size(), CV_8UC1);
    cv::Mat dst_img;

    if (src_img.empty())
    {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
            uchar val = 0.114 * s[0]    // B
                        + 0.587 * s[1]  // G
                        + 0.299 * s[2]; // R
            gray_img.at<uchar>(y, x) = val;
        }
    }

    cv::cvtColor(src_img, dst_img, cv::COLOR_BGR2GRAY);

    cv::imshow(WINDOW_IN, src_img);
    cv::imshow(WINDOW_OUT, gray_img);
    cv::imshow(WINDOW_GOUT, dst_img);
    cv::waitKey();

    return (0);
}

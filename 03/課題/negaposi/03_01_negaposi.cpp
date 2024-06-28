#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./sakura.jpg"
#define WINDOW_IN "input"
#define WINDOW_GRAY "gray"
#define WINDOW_NEGA "negaposi"
#define COLOR_NUM (256)

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME);
    cv::Mat gray_img = cv::Mat(src_img.size(), CV_8UC1);
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

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

    for (int y = 0; y < gray_img.rows; y++)
    {
        for (int x = 0; x < gray_img.cols; x++)
        {
            uchar s = gray_img.at<uchar>(y, x);
            dst_img.at<uchar>(y, x) = COLOR_NUM - s;
        }
    }

    cv::imshow(WINDOW_IN, src_img);
    // cv::imshow(WINDOW_GRAY, gray_img);
    cv::imshow(WINDOW_NEGA, dst_img);
    cv::waitKey();

    return (0);
}
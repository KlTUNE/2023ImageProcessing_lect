#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./fruit_image.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_NUM (256)

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
    if (src_img.empty())
    {
        fprintf(stderr,
                "読み込み失敗\n");
        return (-1);
    }

    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

    for (int y = 0; y < dst_img.rows; y++)
    {
        for (int x = 0; x < dst_img.cols; x++)
        {
            uchar s = src_img.at<uchar>(y, x);
            dst_img.at<uchar>(y, x) = COLOR_NUM-s;
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
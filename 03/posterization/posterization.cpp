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
    uchar lut[COLOR_NUM];

    for (int i = 0; i < COLOR_NUM; i++)
    {
        if (i <= 63)
        {
            lut[i] = 0;
        }
        else if (64 <= i && i <= 127)
        {
            lut[i] = 85;
        }
        else if (128 <= i && i <= 191)
        {
            lut[i] = 170;
        }
        else
        {
            lut[i] = 255;
        }
    }

    for (int y = 0; y < dst_img.rows; y++)
    {
        for (int x = 0; x < dst_img.cols; x++)
        {
            uchar s = src_img.at<uchar>(y, x);
            dst_img.at<uchar>(y, x) = lut[s];
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
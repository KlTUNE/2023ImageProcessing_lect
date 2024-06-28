#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./kagoshima.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_MAX (256)

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

    if (src_img.empty())
    {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    uchar Imin = 255, Imax = 0, Dmin = 0, Dmax = 255;

    for (int y = 0; y < dst_img.rows; y++)
    {
        for (int x = 0; x < dst_img.cols; x++)
        {
            uchar s = src_img.at<uchar>(y, x);
            if (Imin > s)
            {
                Imin = s;
            }
            if (Imax < s)
            {
                Imax = s;
            }
        }
    }

    printf("Imin=%d\nImax=%d\n", Imin, Imax);

    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            uchar s = src_img.at<uchar>(y, x);
            s = (Dmax - Dmin) / (Imax - Imin) * (s - Imin) + Dmin;
            dst_img.at<uchar>(y, x) = s;
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return (0);
}
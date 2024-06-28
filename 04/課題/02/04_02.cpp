#include <iostream>
#include <opencv2/opencv.hpp>
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define FILE_NAME "./image2.jpg"

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

    if (src_img.empty())
    {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    int bin = 121, area = 0, asdf;

    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            uchar s = src_img.at<uchar>(y, x);
            if (s >= bin)
            {
                s = 0;
            }
            else
            {
                s = 255;
                area++;
            }
            dst_img.at<uchar>(y, x) = s;
        }
    }

    printf("image2=%d\n", area);

    // cv::imshow(WINDOW_NAME_INPUT, src_img);
    // cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    // cv::waitKey();

    return (0);
}
#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./image1.jpg"
#define COLOR_MAX (256)

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, 0);

    if (src_img.empty())
    {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    int hist[COLOR_MAX];

    for (int i=0;i < COLOR_MAX;i++){
        hist[i] = 0;
    }

    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            uchar s = src_img.at<uchar>(y, x);
            hist[(int)s]++;
        }
    }

    for (int i=0;i < COLOR_MAX;i++){
        printf ("%d, %d\n", i, hist[i]);
    }

    return (0);
}
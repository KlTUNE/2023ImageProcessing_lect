#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./dot_gray_kanji.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);;
    cv::Mat dst_img2 = cv::Mat(src_img.size(), CV_8UC1);;

    if (src_img.empty())
    {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    cv::blur(src_img, dst_img,cv::Size(7, 7));

    int bin = 200;

    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            uchar s = dst_img.at<uchar>(y, x);
            if (s > bin){
                s = 255;
            }
            else {
                s = 0;
            }
            dst_img2.at<uchar>(y, x) = s;
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img2);
    cv::waitKey();

    return 0;
}

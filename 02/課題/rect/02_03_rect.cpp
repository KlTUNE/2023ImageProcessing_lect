#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./aquarium.jpg"
// #define FILE_NAME "./fruit_image.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME);
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);

    if (src_img.empty())
    {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    int n, box_zero[2];

    fprintf(stderr, "n:");
    scanf("%d", &n);

    box_zero[0] = (src_img.cols/2) - (n/2);
    box_zero[1] = (src_img.rows/2) - (n/2);

    for (int y=0; y<src_img.rows; y++){
        for (int x=0; x<src_img.cols; x++){
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
            if (box_zero[0] <= x && box_zero[1] <= y && box_zero[0]+n >= x && box_zero[1]+n >= y){
                s[0] = 255;
                s[1] = 255;
                s[2] = 255;
            }
            dst_img.at<cv::Vec3b>(y, x) = s;
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}
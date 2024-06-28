#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./ait.png"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME);
    cv::Mat gray_img;
    cv::Mat x_img;
    cv::Mat y_img;
    cv::Mat tmp_img = cv::Mat(src_img.size(), CV_64FC1);
    cv::Mat dst_img;

    if (src_img.empty())
    {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    cv::Sobel(gray_img, x_img, CV_64FC1, 0, 1);
    cv::Sobel(gray_img, y_img, CV_64FC1, 1, 0);

    for (int y = 0; y < gray_img.rows; y++){
        for (int x = 0; x < gray_img.cols; x++){
            double xs = x_img.at<double>(y, x);
            double ys = y_img.at<double>(y, x);

            double s = sqrt(xs*xs+ys*ys);

            tmp_img.at<double>(y, x) = s;
        }
    }

    cv::convertScaleAbs(tmp_img, dst_img);

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    return 0;
}
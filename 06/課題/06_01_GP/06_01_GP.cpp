#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./apple_tree.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME);
    cv::Mat gray_img;
    cv::Mat blur_img;
    cv::Mat tmp_img;
    cv::Mat dst_img;

    if (src_img.empty())
    {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray_img, blur_img,cv::Size(3, 3), 0);

    double filter_h[] = {-1., -1., -1.,
                        0., 0., 0.,
                        1., 1., 1.};

    cv::Mat kernel = cv::Mat(3, 3, CV_64F, filter_h);
    cv::filter2D(gray_img, tmp_img, CV_64F, kernel);
    cv::convertScaleAbs(tmp_img, dst_img);
    cv::convertScaleAbs(tmp_img, dst_img);

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow("Gaussian", blur_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    return 0;
}

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./handinwhite.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define HUE_MIN (20)
#define HUE_MAX (170)
#define SAT_MIN (39)

int main(int argc, const char *argv[])
{
    cv::Vec3b p;
    cv::Mat src_img, dst_img, hsv_img;
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

    if (src_img.empty())
    {
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    dst_img = src_img.clone();
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

    for (int y = 0; y < src_img.rows; y++)
    {
        for (int x = 0; x < src_img.cols; x++)
        {
            p = hsv_img.at<cv::Vec3b>(y, x);
            if (p[0]>HUE_MIN && p[0]<HUE_MAX) dst_img.at<cv::Vec3b>(y, x) = {0, 0, 0};
            if (p[1]<SAT_MIN) dst_img.at<cv::Vec3b>(y, x) = {0, 0, 0};
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();

    return 0;
}

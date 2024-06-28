#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./red_rectangle.jpg"
// #define FILE_NAME "./canvas.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define TH (127)
#define HIGHVAL (255)

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, CV_8UC1);

    if (src_img.empty())
    {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

    // cv::threshold(src_img, dst_img, TH, HIGHVAL, cv::THRESH_BINARY);
    cv::threshold(src_img, dst_img, 0, 255,cv::THRESH_BINARY | cv::THRESH_OTSU);

    // for (int y=0; y<src_img.rows; y++) {
    //     for (int x=0; x<src_img.cols; x++) {
    //         uchar s = src_img.at<uchar>(y, x);

    //         if (s > TH) {
    //             s = 0;
    //         }else{
    //             s = 255;
    //         }
    //         dst_img.at<uchar>(y, x) = s;
    //     }
    // }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    return 0;
}
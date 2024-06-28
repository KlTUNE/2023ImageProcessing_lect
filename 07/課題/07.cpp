#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./issue_input1.jpg"
#define FILE_NAME2 "./issue_input2.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_SUB "sub"
#define ALPHA (0.3)
#define FILTERSIZE (5)
#define THRESHOLD (10)

int main(int argc, const char *argv[])
{
    cv::Mat src_img = cv::imread(FILE_NAME, 0);
    cv::Mat src_img2 = cv::imread(FILE_NAME2, 0);
    cv::Mat src_img2_gray = cv::Mat(src_img.size(), CV_8UC1);
    cv::Mat sub_img = cv::Mat(src_img.size(), CV_8UC1);
    cv::Mat result_img = cv::Mat(src_img.size(), CV_8UC3);

    if (src_img.empty() || src_img2.empty())
    {
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    cv::GaussianBlur(src_img2, src_img2_gray, cv::Size(FILTERSIZE, FILTERSIZE), 0);

    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            int s1 = (int)src_img.at<unsigned char>(y, x);
            int s2 = (int)src_img2_gray.at<unsigned char>(y, x);
            int s_result = abs(s1 - s2);
            cv::Vec3b s;
            sub_img.at<unsigned char>(y, x) = s_result;

            if (s_result > THRESHOLD){
                s[0] = 0;
                s[1] = 0;
                s[2] = 255;
            }

            result_img.at<cv::Vec3b>(y, x) = s;
        }
    }

    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow("input2", src_img2);
    cv::imshow(WINDOW_NAME_SUB, sub_img);
    cv::imshow(WINDOW_NAME_OUTPUT, result_img);
    cv::waitKey();
    return 0;
}
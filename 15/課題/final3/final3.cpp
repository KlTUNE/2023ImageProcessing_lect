#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./input_img1.png"
#define FILE_NAME_HAND "./input_img2.png"
#define WINDOW_INPUT "input"
#define WINDOW_OUTPUT "output"

int main(int argc, const char * argv[]) {
    cv::Mat src_img = cv::imread(FILE_NAME);
    cv::Mat dst_img = cv::imread(FILE_NAME_HAND);

    if (src_img.empty() || dst_img.empty()) {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    for (int y=0; y<src_img.rows; y++){
        for (int x=0; x<src_img.cols; x++){
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
            cv::Vec3b sh = dst_img.at<cv::Vec3b>(y, x);
            //二つの画像の画素値の平均を取る
            sh[0] = (sh[0] + s[0]) / 2;
            sh[1] = (sh[1] + s[1]) / 2;
            sh[2] = (sh[2] + s[2]) /2;
            dst_img.at<cv::Vec3b>(y, x) = sh;
        }
    }

    cv::imshow(WINDOW_INPUT, src_img);
    cv::imshow(WINDOW_OUTPUT, dst_img);
    cv::waitKey();

    return (0);

}

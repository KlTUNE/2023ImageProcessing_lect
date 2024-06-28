#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./aquarium.jpg"

int main(int argc, const char * argv[]) {
    int n, square_w, square_h;
    cv::Mat src_img = cv::imread(FILE_NAME);
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);

    if (src_img.empty()) {
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    scanf("%d", &n);
    square_w = src_img.cols/n;
    square_h = src_img.rows/n;

    if (square_w <= 0) {
        fprintf(stderr, "入力した値が大きすぎます\n");
        return (-1);
    }

    for (int y=0;y<src_img.rows;y++){
        for (int x=0;x<src_img.cols;x++){
            cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
            if ((x/square_w)%2 != (y/square_h)%2){
                s[0] = 255;
                s[1] = 255;
                s[2] = 255;
            }
            dst_img.at<cv::Vec3b>(y, x) = s;
        }
    }
    cv::imshow("lattice", dst_img);
    cv::waitKey();
    return (0);
}
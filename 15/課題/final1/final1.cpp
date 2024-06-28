//k22076

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./input_img1.png"

int main(int argc, const char *argv[]){
    cv::Mat src_img = cv::imread(FILE_NAME);
    cv::Mat gray_img;
    int flag = 0;

    if (src_img.empty()){
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }

    cv::Mat dst_img = src_img.clone();
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    cv::threshold(gray_img, gray_img, 100, 255, cv::THRESH_BINARY);

    //横線描画
    //xを50pxから始めて50pxずつ走査する
    for (int y=0; y<gray_img.rows; y++) {
        for (int x=50; x<gray_img.cols; x+=50) {
            uchar s = gray_img.at<uchar>(y, x);

            //黒以外のピクセルが検出されたらフラグを立てる
            if (s > 10) {
                flag = 1;
            }
        }
        //フラグが立ってなかったら横線を描画する
        if (flag == 0){
            for (int x=0; x<gray_img.cols; x++){
                dst_img.at<cv::Vec3b>(y, x) = {0, 0, 255};
            }
        }
        flag = 0;
    }

    //縦線描画
    //yを50pxから始めて50pxずつ走査する
    for (int x=0; x<gray_img.cols; x++) {
        for (int y=50; y<gray_img.rows; y+=50) {
            uchar s = gray_img.at<uchar>(y, x);

            //黒以外のピクセルが検出されたらフラグを立てる
            if (s > 10) {
                flag = 1;
            }
        }
        //フラグが立ってなかったら縦線を描画する
        if (flag == 0){
            for (int y=0; y<gray_img.rows; y++){
                dst_img.at<cv::Vec3b>(y, x) = {0, 0, 255};
            }
        }
        flag = 0;
    }

    cv::imshow("input", src_img);
    cv::imshow("output", dst_img);
    cv::waitKey();
    return 0;
}
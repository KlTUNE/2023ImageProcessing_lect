#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./gem1.jpg"

#define R_MIN (0) //Rの最小値
#define R_MAX (50) //Rの最大値
#define G_MIN (50) //Gの最小値
#define G_MAX (100) //Gの最大値
#define MAX_VAL (255)
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //変数の宣言
    int x, y; //走査用
    cv::Vec3b p; //色値
    cv::Mat src_img, dst_img; //入力画像，出力画像
    
    //1. 画像を入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    // 2. 出力二値画像の領域を確保（初期値ゼロ：黒）
    cv::Mat gray_img = cv::Mat(src_img.size(), CV_8UC1);

    // 3. しきい値処理
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            p = src_img.at<cv::Vec3b>(y, x);
            if(p[1]>=50 && p[1]<=100 && p[2]>=0 && p[2]<=50){
            gray_img.at<uchar>(y,x) =  255;
            }
        }
    }
    
    //4. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, gray_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}

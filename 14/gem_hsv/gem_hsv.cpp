#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./gem1.jpg"

#define HUE_MIN () // Hの最小値
#define HUE_MAX () // Hの最大値
#define SAT_MIN () // Sの最小値
#define SAT_MAX () // Sの最小値
#define MAX_VAL (255)
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //変数の宣言
    int x, y;    //走査用
    cv::Vec3b p; //色値(HSV)
    cv::Mat src_img, hsv_img, dst_img; //入力画像，HSV画像，出力画像
    
    // 1. 画像を入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    // 2. 出力二値画像の領域を確保（初期値ゼロ：黒）
    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);

    // 3. 色変換 (BGR → HSV)  
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

    // 4. しきい値処理
    for (y=0; y<hsv_img.rows; y++) {
        for (x=0; x<hsv_img.cols; x++) {
            p = hsv_img.at<cv::Vec3b>(y, x);
            if(20<=p[0] && p[0]<=60){
                if(100<=p[1] && p[1]<=200){
                    dst_img.at<uchar>(y, x) = MAX_VAL;
                }
            }
        }
    }
    
    // 5. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}

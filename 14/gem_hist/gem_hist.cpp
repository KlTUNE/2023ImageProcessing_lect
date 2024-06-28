#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./gem1.jpg"
#define COLOR_MAX (256)

int main(int argc, const char * argv[]) {
    cv::Mat gray_img; //画像変数の宣言
    int i,x,y;
    //ヒストグラム用変数の宣言
    int hist[COLOR_MAX];
    
    //1. 入力画像をカラーで入力
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    //2. グレースケール画像
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    //3. ヒストグラム用配列の初期化

    for(i = 0; i < COLOR_MAX; i++){
        hist[i] = 0;
    } 
    
    //4. ヒストグラムの生成
    for (y=0; y<gray_img.rows; y++) {
        for (x=0; x<gray_img.cols; x++) {
            uchar s = gray_img.at<uchar>(y,x);
            hist[(int)s]++;
        }
    }
    
    //5. コンソールに出力
    for(i=0;i<COLOR_MAX;i++){
        printf("%d\n",hist[i]);
    }
    

    return 0;
}

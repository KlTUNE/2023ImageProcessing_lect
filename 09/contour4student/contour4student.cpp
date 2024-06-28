#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル
#define FILE_NAME "./sample.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

//二値化しきい値
#define BIN_TH 100

int main(int argc, const char * argv[]) {
    //1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;
    
    //2. 輪郭の座標リストの宣言
    std::vector< std::vector< cv::Point > > contours;
    //std::vector --- 動的配列 配列の大きさが固定されない
    //cv::Point --- 座標 二次元の座標
        // 「(x,y)の可変配列」の可変配列
    
    //3. カラー画像の入力
    src_img = cv::imread(FILE_NAME);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    //4. 入力画像を出力画像にコピー
    dst_img = src_img.clone();

    //5. グレースケール化
    cv::cvtColor(src_img, gray_img,cv::COLOR_BGR2GRAY);

    //6. 二値化 (固定しきい値で実装．しきい値: 100)
    cv::threshold(gray_img,bin_img,BIN_TH,255,cv::THRESH_BINARY);

    //二値画像コピー
    tmp_img = bin_img.clone();

    //7. 輪郭追跡
    cv::findContours(tmp_img,contours,cv::RETR_LIST,cv::CHAIN_APPROX_NONE);
    //cv::RETR_LIST すべての輪郭
    //cv::CHAIN_APPROX_NONE 8近傍、近似なし
    //出力結果 contoursに格納

    //8. 輪郭の描画
    for(int i=0;i<contours.size();i++){//.size ~のサイズ
        cv::drawContours(dst_img,contours,i,CV_RGB(255,0,255),3);
        //cv::drawContours(出力画像,輪郭情報,輪郭番号,輪郭の色,描画用の線幅);
    }
    
    //9. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_BINARY, bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
        
    return 0;
}


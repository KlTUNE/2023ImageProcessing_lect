#include <iostream>
#include <opencv2/opencv.hpp>
#define BEFORE "./input_img4.png"
#define AFTER "./input_img5.png"
#define KING "./king1.png"
#define KING_R "./king2.png"
#define PAWN "./pawn1.png"
#define PAWN_R "./pawn2.png"
#define PROM "./prom_pawn1.png"
#define PROM_R "./prom_pawn2.png"

int main(int argc, const char *argv[]) {
    char template_file[6][20] = {KING, PAWN, PROM, KING_R, PAWN_R, PROM_R};
    char koma[6][20] = {"king(upper)", "pawn(upper)", "prom_pawn(upper)", "king(lower)", "pawn(lower)", "prom_pawn(lower)"};
    int before[9][9] = {0};
    int after[9][9] = {0};
    cv::Mat before_img = cv::imread(BEFORE);
    cv::Mat after_img = cv::imread(AFTER);
    cv::Mat template_img, compare_img, result_img;
    cv::Point min_loc, max_loc;
    double min_val, max_val;
    int flag = 0, horizon = before_img.cols/9, vertical = before_img.rows/9;

    if (before_img.empty() || after_img.empty()) return (-1);

    //画像を走査してテンプレートマッチングをする
    for (int i = 0; i < 6; i++) {
        template_img = cv::imread(template_file[i], cv::IMREAD_COLOR);
        compare_img = cv::Mat(cv::Size(after_img.rows - template_img.rows + 1, after_img.cols - template_img.cols + 1), CV_32F, 1);
        cv::matchTemplate(after_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
        cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

        for (int y = 0; y < compare_img.rows; y++){
            for (int x = 0; x < compare_img.cols; x++) {
                float s = compare_img.at<float>(y, x);
                //マッチ度が0.2以下ならx,y座標からマス目の座標を算出して二次元配列に格納
                //マッチングしたらxとyを5px飛ばす
                if (s < 0.2) {
                    after[(y+25)/vertical][(x+15)/horizon] = i+1;
                    x += 5;
                    flag = 1;
                }
            }
            if (flag == 1){
                y += 5;
                flag = 0;
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        template_img = cv::imread(template_file[i], cv::IMREAD_COLOR);
        compare_img = cv::Mat(cv::Size(before_img.rows - template_img.rows + 1, before_img.cols - template_img.cols + 1), CV_32F, 1);
        cv::matchTemplate(before_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
        cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

        for (int y = 0; y < compare_img.rows; y++){
            for (int x = 0; x < compare_img.cols; x++) {
                float s = compare_img.at<float>(y, x);
                //マッチ度が0.2以下ならx,y座標からマス目の座標を算出して二次元配列に格納
                //マッチングしたらxとyを5px飛ばす
                if (s < 0.2) {
                    before[(y+25)/vertical][(x+15)/horizon] = i+1;
                    x += 5;
                    flag = 1;
                }
            }
            if (flag == 1){
                y += 5;
                flag = 0;
            }
        }
    }

    //二つの二次元配列を比較して差分の表示
    printf("before\n");
    for (int y=0;y<9;y++){
        for (int x=0;x<9;x++){
            if (after[y][x] != before[y][x] && before[y][x] != 0){
                printf("%s:%d-%d\n", koma[before[y][x]-1], 8-x+1, y+1);
            }
        }
    }

    //二つの二次元配列を比較して差分の表示
    printf("after\n");
    for (int y=0;y<9;y++){
        for (int x=0;x<9;x++){
            if (before[y][x] != after[y][x] && after[y][x] != 0){
                printf("%s:%d-%d\n", koma[after[y][x]-1], 8-x+1, y+1);
            }
        }
    }

    cv::imshow("before", before_img);
    cv::imshow("after", after_img);
    cv::waitKey(0);

    return 0;
}